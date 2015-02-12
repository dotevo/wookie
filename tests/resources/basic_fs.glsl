#version 150

in vec3 Tex;

out vec4 ie_color;

void main() {
    ie_color = vec4(Tex, 1.0);
}