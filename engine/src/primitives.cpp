#include <chatlab/mesh.h>

Mesh createTriangle() {
    Mesh m = Mesh();

    // create a mesh
    m.vertices.push_back(glm::vec3(.5f, -.5f, 0.0f));
    m.vertices.push_back(glm::vec3(-.5f, -.5f, 0.0f));
    m.vertices.push_back(glm::vec3(0.0f, .5f, 0.0f));

    m.indices = { 0, 1, 2 };
    // upload the mesh to the GPU
    m.details.push_back(uploadMesh(m.vertices, m.indices));

    return m;
}

Mesh createCube() {
    Mesh m = Mesh();

    // Coordinates
    m.vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));  //        7--------6
    m.vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));   //       /|       /|
    m.vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));  //      4--------5 |
    m.vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)); //      | |      | |
    m.vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));   //      | 3------|-2
    m.vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));    //      |/       |/
    m.vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));   //      0--------1
    m.vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));

    m.indices = { // Right
                  1, 2, 6, 6, 5, 1,
                  // Left
                  0, 4, 7, 7, 3, 0,
                  // Top
                  4, 5, 6, 6, 7, 4,
                  // Bottom
                  0, 3, 2, 2, 1, 0,
                  // Back
                  0, 1, 5, 5, 4, 0,
                  // Front
                  3, 7, 6, 6, 2, 3
    };
    // upload the mesh to the GPU
    m.details.push_back(uploadMesh(m.vertices, m.indices));

    return m;
}
