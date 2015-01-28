#version 150

in vec3 ie_pos;

void main() {
    gl_Position = vec4(ie_pos, 1.0f);
}