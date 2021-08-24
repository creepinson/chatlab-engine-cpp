#include "chatlab/engine.h"
#include <chatlab/service_locator.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
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