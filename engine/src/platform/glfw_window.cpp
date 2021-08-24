#include <chatlab/engine.h>
#include <chatlab/platform/glfw_window.h>
#include <functional>
#include <stdexcept>

GLFWWindow::GLFWWindow() { window = nullptr; }

// title implementation
void GLFWWindow::setTitle(const std::string newTitle) {
    title = newTitle;
    glfwSetWindowTitle(window, title.c_str());
}

std::string GLFWWindow::getTitle() { return title; }

void GLFWWindow::error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void GLFWWindow::init() {
    glfwSetErrorCallback(GLFWWindow::error_callback);

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // convert title to c string
    const char *titleCStr = title.c_str();

    window = glfwCreateWindow(600, 600, titleCStr, nullptr, nullptr);

    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
        close();
    }

    glfwMakeContextCurrent(window);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
        close();
    }

    glfwSetCursorPosCallback(window, Engine::cursorPositionCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
}

bool GLFWWindow::update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    this->setSize(width, height);

    return glfwWindowShouldClose(window);
}

void GLFWWindow::close() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GLFWWindow::postUpdate() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void GLFWWindow::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    glfwGetWindowSize(this->window, &width, &height);
    glViewport(0, 0, width, height);
}
