#pragma once

#include <chatlab/platform/glfw_window.h>
#include <glm/glm.hpp>

struct Engine {
public:
    static void init();
    static float getDeltaTime();
    inline static float prevTime = 0.0f;

    // TODO: input class
    // keyboard input def
    static bool isKeyDown(int key);

    // mouse input def
    static bool isMouseDown(int button);

    static glm::vec3 getMousePosition();

    static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                       double ypos);

private:
    inline static glm::vec3 mousePos = glm::vec3(0.0f);
};
