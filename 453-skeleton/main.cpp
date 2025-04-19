#include <glad/glad.h>

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "AssetPath.h"
#include "GLDebug.h"
#include "Geometry.h"
#include "Log.h"
#include "Panel.h"
#include "RayTracingBaselineScenes.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "TextureBuffer.h"
#include "TurnTableView.h"
#include "Window.h"
#include "ray-trace/Cameras.h"
#include "ray-trace/Scene.h"

// To swap to perspective camera, see these locations in this file (main.cpp) to modify. This commenet below will indicate:
// ********************************************** //

// Do not modify scenes A-F (0-5) as they will be used to grade your submission, doing so will lose you marks!!!!!
// If you want to make your own scenes use the context_user member in the renderer or add additional
// if you want to make more then one.

// Read the D2L page for pointers on where the code that needs to be modified. All that NEEDs to be done in this file is uncomment
//  and comment the perspective and orthographic stuff, the rest of the changes will be in files in the ray-trace sub folder

struct RayTracingContext {
    // ------------- Avoid modifying this class, unless you need to add new TraceParameters or do sub-sampling (more then one ray
    // per pixel) ------------- //
    RayTracingContext(Scene init_scene = Scene(), std::shared_ptr<Camera> init_camera = std::make_shared<PerspectiveCamera>())
        : scene(init_scene)
        , camera(init_camera)
    {
    }

    void renderTexture(int max_recursion_depth = 10)
    {
        std::vector<CameraRay> camera_rays = camera->generateRays();
        if (camera_rays.size() == 0) return;

        TraceParameters trace_params;
        trace_params.level = max_recursion_depth;
        std::vector<glm::vec3> pixel_colours(camera_rays.size());

        float last_percent = 0.f;
        for (size_t index = 0u; index < camera_rays.size(); index++) {
            const CameraRay &camera_ray = camera_rays[index];
            glm::vec3 &pixel_colour     = pixel_colours[index];

            TraceResult trace_result = scene.trace(camera_ray.ray, trace_params);
            pixel_colour             = trace_result.colour;

            float percent = static_cast<float>(index) / static_cast<float>(camera_rays.size()) * 100.f;
            if (percent > last_percent + 1.f) {
                Log::debug("Render {}% Complete", percent);
                last_percent = percent;
            }
        }
        render_to_texture_buffer.uploadData(GL_LINEAR, camera->dimensions.x, camera->dimensions.y, pixel_colours.data());
    }

    void bindTexture() { render_to_texture_buffer.bind(); }

    Scene scene;
    std::shared_ptr<Camera> camera;

  protected:
    TextureBuffer render_to_texture_buffer;
};

class MyCallback : public CallbackInterface {
  public:
    MyCallback(int init_width, int init_height) { windowSizeCallback(init_width, init_height); }

    virtual void windowSizeCallback(int width, int height)
    {
        current_window_dims = glm::uvec2(width, height);
        CallbackInterface::windowSizeCallback(width, height);
    }

    GLuint width() const { return current_window_dims.x; }
    GLuint height() const { return current_window_dims.y; }

    glm::uvec2 current_window_dims;
};

class MyPanelRenderer : public PanelRendererInterface {
    // ------------- You may modify this class but be sure you do not break functionality or scenes A-F (0-5) ------------- //
  public:
    MyPanelRenderer(std::shared_ptr<MyCallback> callback)
        : callback(callback)
        , view(20.f, glm::radians(30.f), glm::radians(-45.f))
        // ********************************************** //
        //, orthographic_camera(new OrthographicCamera())
        , perspective_camera(new PerspectiveCamera())
        // ********************************************** //
        , current_context_number(0)
        , context_A()
        , context_B()
        , context_C()
        , context_D()
        , context_E()
        , context_F()
        , context_user()
        , max_recursion_depth(8)
    {
        // ------------- DO NOT CHANGE THESE ------------- //
        context_A.scene = RayTracingBaselineScenes::A();
        context_B.scene = RayTracingBaselineScenes::B();
        context_C.scene = RayTracingBaselineScenes::C();
        context_D.scene = RayTracingBaselineScenes::D();
        context_E.scene = RayTracingBaselineScenes::E();
        context_F.scene = RayTracingBaselineScenes::F();

        // ------------- YOU MAY CHANGE THESE ------------- //
        context_user.scene = Scene();

        // ********************************************** //
        //context_A.camera    = orthographic_camera;
        //context_B.camera    = orthographic_camera;
        //context_C.camera    = orthographic_camera;
        //context_D.camera    = orthographic_camera;
        //context_E.camera    = orthographic_camera;
        //context_F.camera    = orthographic_camera;
        //context_user.camera = orthographic_camera;

        context_A.camera = perspective_camera;
        context_B.camera = perspective_camera;
        context_C.camera = perspective_camera;
        context_D.camera = perspective_camera;
        context_E.camera = perspective_camera;
        context_F.camera = perspective_camera;
        context_user.camera = perspective_camera;
        //  ********************************************** //
    }

    virtual void render() override
    {
        float_t s_p_f = 1000.0f / ImGui::GetIO().Framerate;
        float_t f_p_s = ImGui::GetIO().Framerate;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", s_p_f, f_p_s);

        ImGui::SliderInt("Current Context", &current_context_number, 0, 6);
        RayTracingContext &context = getCurrentContext();

        if (ImGui::Button("Render")) renderCurrentContext();

        glm::vec3 target = view.getTarget();
        ImGui::InputFloat3("Camera Target", glm::value_ptr(target));
        view.setTarget(target);

        float distance = view.getDistance();
        ImGui::SliderFloat("Camera Distance", &distance, 0.01f, 100.f);
        view.setDistance(distance);

        float theta = view.getTheta();
        ImGui::SliderAngle("Camera Theta", &theta, -89.0f, 89.f);
        view.setTheta(theta);

        float phi = view.getPhi();
        ImGui::SliderAngle("Camera Phi", &phi, -180.0f, 180.f);
        view.setPhi(phi);

        // ********************************************** //
        //ImGui::SliderFloat("Orthographic Vertical Scale", &orthographic_camera->vertical_scale, 0.01f, 100.f);
        ImGui::SliderAngle("Perspective Vertical FOV", &perspective_camera->vertical_fov_radians, 20.f, 160.f);
        //  ********************************************** //

        ImGui::SliderInt("Recursion Depth", &max_recursion_depth, 0, 15);
    }

    RayTracingContext &getCurrentContext()
    {
        switch (current_context_number) {
            // ------------- DO NOT CHANGE THESE ------------- //
            case 0: return context_A;
            case 1: return context_B;
            case 2: return context_C;
            case 3: return context_D;
            case 4: return context_E;
            case 5: return context_F;
            // ------------- YOU MAY CHANGE THESE ------------- //
            case 6: return context_user;
        }
        throw std::runtime_error("Oh no.... there is not a context for this number, please fix me!");
    }

    void renderCurrentContext()
    {
        // ********************************************** //
        //orthographic_camera->position   = view.getPos();
        //orthographic_camera->direction  = view.getDirection();
        //orthographic_camera->approx_up  = glm::vec3(0.f, 1.f, 0.f);
        //orthographic_camera->dimensions = callback->current_window_dims;

        perspective_camera->position   = view.getPos();
        perspective_camera->direction  = view.getDirection();
        perspective_camera->approx_up  = glm::vec3(0.f, 1.f, 0.f);
        perspective_camera->dimensions = callback->current_window_dims;
        // ********************************************** //

        getCurrentContext().renderTexture(max_recursion_depth);
    }
    void bindCurrentContext() { getCurrentContext().bindTexture(); }

    std::shared_ptr<MyCallback> callback;
    TurnTableView view;

    // ********************************************** //
    //std::shared_ptr<OrthographicCamera> orthographic_camera;
    std::shared_ptr<PerspectiveCamera> perspective_camera;
    // ********************************************** //

    int current_context_number;
    RayTracingContext context_A;  // 0
    RayTracingContext context_B;  // 1
    RayTracingContext context_C;  // 2
    RayTracingContext context_D;  // 3
    RayTracingContext context_E;  // 4
    RayTracingContext context_F;  // 5

    RayTracingContext context_user;  // 6

    int max_recursion_depth;
};

// There is no need the change the main function
int main()
{
    Log::debug("Starting main");

    // WINDOW
    glfwInit();
    {
        int init_width  = 800;
        int init_height = 800;
        Window window(init_width, init_height, "Ray Tracing");
        Panel panel(window.getGLFWwindow());

        GLDebug::enable();

        std::shared_ptr<MyCallback> my_callback = std::make_shared<MyCallback>(init_width, init_height);
        window.setCallbacks(my_callback);

        std::shared_ptr<MyPanelRenderer> my_panel_renderer = std::make_shared<MyPanelRenderer>(my_callback);
        panel.setPanelRenderer(my_panel_renderer);

        ShaderProgram shader_program(
            AssetPath::Instance()->Get("shaders/basic.vert"), AssetPath::Instance()->Get("shaders/basic.frag")
        );

        const std::vector<glm::vec3> quad_verts
            = {glm::vec3(-1.f, -1.f, 0.f),
               glm::vec3(+1.f, -1.f, 0.f),
               glm::vec3(+1.f, +1.f, 0.f),
               glm::vec3(-1.f, -1.f, 0.f),
               glm::vec3(+1.f, +1.f, 0.f),
               glm::vec3(-1.f, +1.f, 0.f)};

        const std::vector<glm::vec2> quad_uvs
            = {glm::vec2(0.f, 0.f),
               glm::vec2(1.f, 0.f),
               glm::vec2(1.f, 1.f),
               glm::vec2(0.f, 0.f),
               glm::vec2(1.f, 1.f),
               glm::vec2(0.f, +1.f)};

        GPU_Geometry quad_geom;
        quad_geom.setVerts(quad_verts);
        quad_geom.setTexCoords(quad_uvs);

        // RENDER LOOP
        while (!window.shouldClose()) {
            glfwPollEvents();

            glEnable(GL_FRAMEBUFFER_SRGB);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader_program.use();
            my_panel_renderer->bindCurrentContext();
            quad_geom.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisable(GL_FRAMEBUFFER_SRGB);
            panel.render();

            window.swapBuffers();
        }
    }
    glfwTerminate();
    return 0;
}
