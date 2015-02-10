#version 150

in vec3 ie_pos;
in vec2 ie_tex;

uniform mat4 ie_mvp;

out vec2 Tex;

void main() {
    gl_Position = ie_mvp * vec4(ie_pos, 1.0);
    Tex = ie_tex;
}