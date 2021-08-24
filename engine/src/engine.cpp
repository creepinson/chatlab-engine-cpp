#include "chatlab/engine.h"
#include <chatlab/service_locator.h>
#include <glm/ext.hpp>
#include <iostream>

#include <chatlab/platform/glfw_window.h>

void Engine::init() {
    std::cout << "Initializing window" << std::endl;

    ServiceLocator::Provide(new GLFWWindow());
    prevTime = glfwGetTime();
}

float Engine::getDeltaTime() {
    float currTime = glfwGetTime();
    prevTime = currTime;
    return currTime - prevTime;
}

bool Engine::isKeyDown(int key) {
    return glfwGetKey(ServiceLocator::getWindow()->window, key) == GLFW_PRESS;
}

bool Engine::isMouseDown(int button) {
    return glfwGetMouseButton(ServiceLocator::getWindow()->window, button) ==
           GLFW_PRESS;
}

glm::vec3 Engine::getMousePosition() { return Engine::mousePos; }

void Engine::cursorPositionCallback(GLFWwindow *window, double xpos,
                                    double ypos) {
    Engine::mousePos.x = xpos;
    Engine::mousePos.y = ypos;
    Engine::mousePos.z = 0;
}