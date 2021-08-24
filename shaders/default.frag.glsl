#version 330

in vec3 v_position;

uniform vec3 u_color;

out vec4 fs_color;

void main() {
    fs_color = vec4(u_color, 1.0);
}