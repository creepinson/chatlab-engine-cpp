#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <stdexcept>
#include <stdint.h>
#include <vector>

class Transform {
public:
    Transform(Transform &other);
    Transform();
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 size);
    Transform(glm::vec3 position, glm::vec3 rotation);
    Transform(glm::vec3 position);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 size;

    glm::mat4 getMatrix();

    void translate(glm::vec3 translation);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 size);

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setSize(glm::vec3 size);
};