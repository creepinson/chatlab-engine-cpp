#include <chatlab/camera.h>
#include <chatlab/engine.h>
#include <chatlab/service_locator.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>

Camera::Camera() {
    Transform *tr = new Transform();
    tr->setPosition(glm::vec3(0, 0, -2));
    transform = tr;
}

void Camera::update() {
    // TODO: player input class

    GLFWwindow *window = ServiceLocator::getWindow()->window;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * 0.01f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        transform->position -= cameraSpeed * this->forward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        transform->position += cameraSpeed * this->forward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        transform->position +=
            glm::normalize(glm::cross(this->forward(), glm::vec3(0, 1, 0))) *
            cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        transform->position -=
            glm::normalize(glm::cross(this->forward(), glm::vec3(0, 1, 0))) *
            cameraSpeed;

    float xoffset = Engine::getMousePosition().x;
    float yoffset = Engine::getMousePosition().y;

    float sensitivity = 0.001f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // stdout test
    std::cout << "xoffset: " << xoffset << std::endl;
    std::cout << "yoffset: " << yoffset << std::endl;

    transform->rotation.x = yoffset;
    transform->rotation.y = xoffset;
}

glm::mat4 Camera::getProjectionMatrix() {
    glm::mat4 perspective = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(ServiceLocator::getWindow()->width) /
            static_cast<float>(ServiceLocator::getWindow()->height),
        0.1f, // TODO: screen width and height
        100.0f);
    return perspective * this->transform->getMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(this->transform->position,
                       this->transform->position + this->forward(), this->up());
}

glm::vec3 Camera::forward() const {
    glm::fquat q = glm::fquat(glm::radians(transform->rotation));
    glm::vec4 forward = glm::inverse(q) * glm::vec4(0, 0, -1, 1);
    return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
    glm::fquat q = glm::fquat(glm::radians(transform->rotation));
    glm::vec4 right = glm::inverse(q) * glm::vec4(1, 0, 0, 1);
    return glm::vec3(right);
}

glm::vec3 Camera::up() const {
    glm::fquat q = glm::fquat(glm::radians(transform->rotation));

    glm::vec4 up = glm::inverse(q) * glm::vec4(0, 1, 0, 1);
    return glm::vec3(up);
}