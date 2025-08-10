#version 330 core

in vec2 m_texture_coord;

uniform sampler2D u_texture_window;

void main()
{
    gl_FragColor = texture(u_texture_window, m_texture_coord);
}