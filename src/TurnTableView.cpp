#include "TurnTableView.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

TurnTableView::TurnTableView(float init_distance, float init_theta_radians, float init_phi_radians, glm::vec3 init_target)
    : distance(init_distance)
    , theta_radians(init_theta_radians)
    , phi_radians(init_phi_radians)
    , target(init_target)
{
}
TurnTableView::TurnTableView(glm::vec3 init_pos, glm::vec3 init_target)
    : distance(10.f)
    , theta_radians(0.f)
    , phi_radians(0.f)
    , target(init_target)
{
    setPos(init_pos);
}

glm::mat4 TurnTableView::view() const
{
    glm::mat4 target_translation = glm::translate(glm::mat4(1.f), -target);
    glm::mat4 phi_rotation       = glm::rotate(glm::mat4(1.f), -phi_radians, glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 theta_rotation
        = glm::rotate(glm::mat4(1.f), -theta_radians, glm::vec3(-1.f, 0.f, 0.f));  // Anti x axis rotation
    glm::mat4 distance_translation = glm::translate(glm::mat4(1.f), -glm::vec3(0.f, 0.f, distance));
    return distance_translation * theta_rotation * phi_rotation * target_translation;
}

glm::vec3 TurnTableView::getPos() const { return glm::inverse(view()) * glm::vec4(0.f, 0.f, 0.f, 1.f); }

void TurnTableView::setPos(glm::vec3 new_pos)
{
    glm::vec3 offset = new_pos - target;
    distance         = glm::length(offset);

    // Special Case for when offset == 0
    if (distance < glm::epsilon<float>()) {
        theta_radians = 0.f;
        phi_radians   = 0.f;
        return;
    }

    glm::vec3 offset_direction = glm::normalize(offset);

    // Special case for when algined with zy axis
    if (glm::abs(offset_direction.x) < glm::epsilon<float>() && glm::abs(offset_direction.z) < glm::epsilon<float>()) {
        if (offset_direction.y > 0) theta_radians = glm::half_pi<float>();
        else theta_radians = -glm::half_pi<float>();
        phi_radians = 0.f;
        return;
    }

    theta_radians = std::asin(offset_direction.y);
    phi_radians   = std::atan2(offset_direction.x, offset_direction.z);
}
glm::vec3 TurnTableView::getDirection() const { return glm::normalize(target - getPos()); }
float TurnTableView::getDistance() const { return distance; }
void TurnTableView::setDistance(float new_distance) { distance = new_distance; }
float TurnTableView::getTheta() const { return theta_radians; }
void TurnTableView::setTheta(float new_theta_radians) { theta_radians = new_theta_radians; }
float TurnTableView::getPhi() const { return phi_radians; }
void TurnTableView::setPhi(float new_phi_radians) { phi_radians = new_phi_radians; }
glm::vec3 TurnTableView::getTarget() const { return target; }
void TurnTableView::setTarget(glm::vec3 new_target) { target = new_target; }
