#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <vector>

class Shader {
public:
    Shader(std::string path, const GLuint type);
    ~Shader();
    void load();

    std::string path;
    std::string source;
    GLuint shader;
    GLuint type;
};

class ShaderProgram {
public:
    ShaderProgram(Shader *vertex, Shader *fragment);
    ~ShaderProgram();
    void uniform(const char *name, float value);
    void uniform(const char *name, glm::vec3 value);
    void uniform(const char *name, glm::vec4 value);
    void uniform(const char *name, glm::mat3 value);
    void uniform(const char *name, glm::mat4 value);
    void use();

private:
    Shader *vertex;
    Shader *fragment;
    GLuint program;
};

std::string readShaderFile(std::string shader_file);
