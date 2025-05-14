#pragma once

#include <glm/glm.hpp>

class TurnTableView {
  public:
    TurnTableView(
        float init_distance      = 1.f,
        float init_theta_radians = 0.f,
        float init_phi_radians   = 0.f,
        glm::vec3 init_target    = {0.f, 0.f, 0.f}
    );
    TurnTableView(glm::vec3 init_pos, glm::vec3 init_target = {0.f, 0.f, 0.f});

    glm::mat4 view() const;

    glm::vec3 getPos() const;
    void setPos(glm::vec3 new_pos);

    glm::vec3 getDirection() const;

    float getDistance() const;
    void setDistance(float new_distance);

    float getTheta() const;
    void setTheta(float new_theta_radians);

    float getPhi() const;
    void setPhi(float new_phi_radians);

    glm::vec3 getTarget() const;
    void setTarget(glm::vec3 new_target);

  protected:
    float distance;
    float theta_radians;
    float phi_radians;
    glm::vec3 target;
};
