#version 150

in vec3 ie_pos;
in vec3 ie_tex;

smooth out vec3 ie_col;

void main() {
    gl_Position = vec4(ie_pos, 1.0f);
    ie_col = ie_tex;
}