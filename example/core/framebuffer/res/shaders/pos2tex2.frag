#version 330 core

in vec2 m_texture_coord;

out vec4 FragColor;

uniform sampler2D u_screen_texture;

void main()
{
    FragColor = texture(u_screen_texture, m_texture_coord);
}