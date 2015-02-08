#version 150

in vec3 ie_pos;
in vec3 ie_tex;

uniform mat4 ie_trans;

smooth out vec3 ie_col;

void main() {
    gl_Position = ie_trans * vec4(ie_pos, 1.0);
    ie_col = ie_tex;
}