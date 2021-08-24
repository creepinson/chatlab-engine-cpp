#pragma once
#include "transform.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <stdexcept>
#include <stdint.h>
#include <vector>

class Camera {
public:
    Camera();
    ~Camera();
    void update();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
    Transform *transform;
    glm::vec3 forward() const;
    glm::vec3 right() const;
    glm::vec3 up() const;
};