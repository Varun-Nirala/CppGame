#version 460 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    color = textColor * vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
}  