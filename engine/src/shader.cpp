#include <chatlab/shader.h>

std::string readShaderFile(std::string shader_file) {
    std::ifstream ifs;

    auto ex = ifs.exceptions();
    ex |= std::ios_base::badbit | std::ios_base::failbit;
    ifs.exceptions(ex);

    ifs.open(shader_file);
    ifs.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = ifs.gcount();

    if (size > 0x10000) // 64KiB sanity check:
        throw std::runtime_error("Shader file too large");

    ifs.clear();
    ifs.seekg(0, std::ios_base::beg);
    return std::string{ std::istreambuf_iterator<char>{ ifs }, {} };
}

Shader::Shader(std::string path, const GLuint type) {
    this->type = type;
    this->path = path;
    this->shader = glCreateShader(type);
    this->load();
}
Shader::~Shader() { glDeleteShader(this->shader); }
void Shader::load() {
    std::string shaderSource = readShaderFile(this->path);

    const char *shaderSourceCstr = shaderSource.c_str();
    glShaderSource(this->shader, 1, &shaderSourceCstr, nullptr);

    // print shader src for testing
    // printf("%s\n", shaderSourceCstr);

    glCompileShader(this->shader);
    GLint status;
    glGetShaderiv(this->shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(this->shader, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetShaderInfoLog(this->shader, length, &length, log);
        printf("Shader %s compilation failed:\n%s\n", this->path.c_str(), log);
        delete[] log;
    }
}

ShaderProgram::ShaderProgram(Shader *vertex, Shader *fragment) {
    this->program = glCreateProgram();

    glAttachShader(this->program, vertex->shader);
    glAttachShader(this->program, fragment->shader);
    glLinkProgram(this->program);
    GLint status;
    glGetProgramiv(this->program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetProgramInfoLog(this->program, length, &length, log);
        printf("Shader program link failed:\n%s\n", log);
        delete[] log;
    }
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(this->program); }

void ShaderProgram::uniform(const char *name, float value) {
    GLint location = glGetUniformLocation(this->program, name);
    glUniform1f(location, value);
}

void ShaderProgram::uniform(const char *name, glm::vec3 value) {
    GLint location = glGetUniformLocation(this->program, name);
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::uniform(const char *name, glm::vec4 value) {
    GLint location = glGetUniformLocation(this->program, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::uniform(const char *name, glm::mat3 value) {
    GLint location = glGetUniformLocation(this->program, name);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::uniform(const char *name, glm::mat4 value) {
    GLint location = glGetUniformLocation(this->program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::use() { glUseProgram(this->program); }
