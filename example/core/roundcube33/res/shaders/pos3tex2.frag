#version 330 core

layout(location = 0) out vec4 fragColor;

in vec2 m_texture_coord;

uniform sampler2D u_texture_0;

// out vec4 fragColor;

void main()
{
	fragColor = texture(u_texture_0, m_texture_coord);
}