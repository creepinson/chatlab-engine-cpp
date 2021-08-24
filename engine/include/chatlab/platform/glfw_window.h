#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class GLFWWindow {
public:
    GLFWWindow();
    virtual void init();
    virtual bool update();
    virtual void postUpdate();
    virtual void setTitle(std::string title);
    virtual std::string getTitle();
    virtual void close();
    GLFWwindow *window;
    virtual void setSize(int width, int height);
    // size
    int width;
    int height;

private:
    // title
    std::string title;

    // error callback
    static void error_callback(int error, const char *description);
    void windowSizeCallback(GLFWwindow *window, int width, int height);
};