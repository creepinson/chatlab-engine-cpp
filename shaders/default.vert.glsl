#version 330

layout (location = 0) in vec3 position;

uniform mat4 u_proj;
uniform mat4 u_model;

out vec3 v_position;

void main() {
    v_position = position;

    gl_Position = u_proj * u_model * vec4(position, 1.0);
}