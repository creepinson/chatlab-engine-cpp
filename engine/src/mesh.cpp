#include <chatlab/mesh.h>

DrawDetails uploadMesh(std::vector<glm::vec3> &vertices,
                       std::vector<uint32_t> &indices) {
    if (vertices.size() == 0 || indices.size() == 0) {
        throw std::runtime_error("Mesh has no vertices or indices");
    }

    uint32_t vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                 &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    return DrawDetails(vao, indices.size());
}

void unloadMesh(std::vector<DrawDetails> &drawDetails) {
    for (auto &details : drawDetails) {
        glDeleteBuffers(1, &details.vao);
    }

    drawDetails.clear();
}

void draw(const std::vector<DrawDetails> &drawDetails) {
    for (auto &details : drawDetails) {
        glBindVertexArray(details.vao);
        glDrawElements(GL_TRIANGLES, details.numElements, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}