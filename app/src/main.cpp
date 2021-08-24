#include <chatlab/camera.h>
#include <chatlab/engine.h>
#include <chatlab/mesh.h>
#include <chatlab/primitives.h>
#include <chatlab/service_locator.h>
#include <chatlab/shader.h>
#include <chatlab/transform.h>
#include <iostream>
#include <random>

// int main with args
int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    Engine::init();

    ServiceLocator::getWindow()->init();
    ServiceLocator::getWindow()->setSize(800, 600);
    ServiceLocator::getWindow()->setTitle("Chatlab");

    // Create the vertex and fragment shaders
    Shader *vertexShader =
        new Shader("shaders/default.vert.glsl", GL_VERTEX_SHADER);
    Shader *fragmentShader =
        new Shader("shaders/default.frag.glsl", GL_FRAGMENT_SHADER);

    // create shader program
    ShaderProgram *shaderProgram =
        new ShaderProgram(vertexShader, fragmentShader);

    // create a player camera
    Camera *camera = new Camera();

    std::vector<Mesh> meshes;

    for (int i = 0; i < 5; i++) {
        Mesh m = createCube();
        m.transform->setPosition(glm::vec3(i * 5, 0, 0));

        meshes.push_back(m);
    }

    while (!ServiceLocator::getWindow()->update()) {
        Engine::prevTime = glfwGetTime();

        // update the camera
        camera->update();

        shaderProgram->use();
        shaderProgram->uniform("u_proj", camera->getProjectionMatrix());

        // draw mesh
        for (auto &m : meshes) {
            shaderProgram->uniform("u_model", m.transform->getMatrix());
            shaderProgram->uniform("u_color", glm::vec3(1.0f, 0.0f, 0.0f));
            m.draw();
        }

        // post update
        ServiceLocator::getWindow()->postUpdate();
    }

    ServiceLocator::getWindow()->close();
}