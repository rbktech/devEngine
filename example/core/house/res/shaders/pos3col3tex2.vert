#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture_coord;

out vec3 m_color;
out vec2 m_texture_coord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    m_color = color;
    m_texture_coord = texture_coord;
}