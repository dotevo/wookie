#version 150

in vec2 Tex;

out vec4 ie_color;

uniform sampler2D ie_sampler2D;

void main() {
    ie_color = texture(ie_sampler2D, Tex);
}