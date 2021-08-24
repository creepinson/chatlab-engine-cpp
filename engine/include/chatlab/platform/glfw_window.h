#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chatlab/platform/window.h>
#include <string>

class GLFWWindow : public Window {
public:
    GLFWWindow();
    virtual void init() override;
    virtual bool update() override;
    virtual void postUpdate() override;
    virtual void setTitle(std::string title) override;
    virtual std::string getTitle() override;
    virtual void close() override;

private:
    GLFWwindow *window;
    // title
    std::string title;

    // error callback
    static void error_callback(int error, const char *description);
};