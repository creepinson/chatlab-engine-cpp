#include <chatlab/camera.h>
#include <chatlab/engine.h>
#include <chatlab/mesh.h>
#include <chatlab/service_locator.h>
#include <chatlab/shader.h>
#include <chatlab/transform.h>
#include <iostream>

// int main with args
int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    Engine::init();

    ServiceLocator::getWindow()->init();
    ServiceLocator::getWindow()->setTitle("Chatlab");

    // Create the vertex and fragment shaders
    Shader *vertexShader =
        new Shader("shaders/default.vert.glsl", GL_VERTEX_SHADER);
    Shader *fragmentShader =
        new Shader("shaders/default.frag.glsl", GL_FRAGMENT_SHADER);

    // create shader program
    ShaderProgram *shaderProgram =
        new ShaderProgram(vertexShader, fragmentShader);

    std::vector<DrawDetails> details;

    // create a mesh
    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(.5f, -.5f, 0.0f));
    vertices.push_back(glm::vec3(-.5f, -.5f, 0.0f));
    vertices.push_back(glm::vec3(0.0f, .5f, 0.0f));

    std::vector<uint32_t> indices = { 0, 1, 2 };
    // upload the mesh to the GPU
    details.push_back(uploadMesh(vertices, indices));

    // create a transform for the mesh
    Transform *transform = new Transform();

    // create a player camera
    Camera *camera = new Camera();

    while (!ServiceLocator::getWindow()->update()) {
        Engine::prevTime = glfwGetTime();

        // draw mesh
        shaderProgram->use();
        shaderProgram->uniform("u_color", glm::vec3(1.0f, 0.0f, 0.0f));
        shaderProgram->uniform("matrices", camera->getProjectionMatrix() *
                                               transform->getMatrix());
        draw(details);

        // update the rotation
        transform->translate(glm::vec3(0.0f, 0.0f, -0.01f));

        // post update
        ServiceLocator::getWindow()->postUpdate();
    }

    unloadMesh(details);

    ServiceLocator::getWindow()->close();
}