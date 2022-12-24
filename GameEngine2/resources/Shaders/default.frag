#version 460 core

in vec4 fColor;
in vec2 fTexCoord;
in float fTexId;

out vec4 color;

uniform sampler2D uTextures[8];

void main()
{
	if (fTexId > 0)
	{
		int id = int(fTexId);
		color = fColor * texture(uTextures[id], fTexCoord);
	}
	else
	{
		color = fColor;
	}
}