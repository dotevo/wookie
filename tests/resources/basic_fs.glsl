#version 150

smooth in vec3 ie_col;

out vec4 ie_color;

void main() {
    ie_color = vec4(ie_col, 1.0f);
}