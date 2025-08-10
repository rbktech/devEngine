#version 330 core

in vec3 m_color;

out vec4 color;

void main()
{
    color = vec4(m_color, 1.0f);
}