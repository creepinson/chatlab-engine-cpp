#include <chatlab/camera.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

Camera::Camera() {
    Transform *tr = new Transform();
    tr->setPosition(glm::vec3(0, 0, -2));
    transform = tr;
}

void Camera::update() {
    // TODO: implement camera controls and movement
}

glm::mat4 Camera::getProjectionMatrix() {
    glm::mat4 perspective =
        glm::perspective(glm::radians(45.0f), 1.0f,
                         0.1f, // TODO: screen width and height
                         100.0f);
    return perspective * this->transform->getMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(this->transform->position,
                       this->transform->position + glm::vec3(0, 0, -1),
                       glm::vec3(0, 1, 0));
}