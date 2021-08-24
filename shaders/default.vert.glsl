#version 330

layout (location = 0) in vec3 position;

uniform mat4 matrices;

out vec3 v_position;

void main() {
    v_position = position;

    gl_Position = matrices * vec4(position, 1.0);
}