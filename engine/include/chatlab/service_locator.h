#pragma once
#include <chatlab/platform/window.h>
#include <memory>

class ServiceLocator {
public:
    static inline const std::unique_ptr<Window> &getWindow() { return _window; }

    static inline void Provide(Window *window) {
        if (_window != nullptr) {
            throw std::runtime_error("Window already provided");
        }

        _window = std::unique_ptr<Window>(window);
    }

private:
    static inline std::unique_ptr<Window> _window = nullptr;
};