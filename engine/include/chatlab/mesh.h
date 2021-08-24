#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <stdint.h>
#include <vector>

#include <chatlab/transform.h>

struct DrawDetails {
    DrawDetails(uint32_t v, uint32_t e) {
        vao = v;
        numElements = e;
    }

    uint32_t vao = 0;
    uint32_t numElements = 0;
};

DrawDetails uploadMesh(std::vector<glm::vec3> &vertices,
                       std::vector<uint32_t> &indices);

void unloadMesh(std::vector<DrawDetails> &drawDetails);

void drawMesh(const std::vector<DrawDetails> &drawDetails);

class Mesh {
public:
    Mesh();
    ~Mesh();
    std::vector<DrawDetails> details;
    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;
    Transform *transform;

    void draw();
};