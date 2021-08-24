#include <chatlab/platform/glfw_window.h>
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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // convert title to c string
    const char *titleCStr = title.c_str();

    window = glfwCreateWindow(800, 600, titleCStr, nullptr, nullptr);

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

    glViewport(0, 0, 800, 600);
}

bool GLFWWindow::update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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