#pragma once
#include <chatlab/platform/glfw_window.h>
#include <memory>

class ServiceLocator {
public:
    static inline const std::unique_ptr<GLFWWindow> &getWindow() {
        return _window;
    }

    static inline void Provide(GLFWWindow *window) {
        if (_window != nullptr) {
            throw std::runtime_error("Window already provided");
        }

        _window = std::unique_ptr<GLFWWindow>(window);
    }

private:
    static inline std::unique_ptr<GLFWWindow> _window = nullptr;
};