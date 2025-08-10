#version 330 core

in vec3 m_color;

out vec4 color;

void main()
{
    color.r = m_color.r;
    color.g = m_color.g;
    color.b = m_color.b;
    color.a = 1.0f;
    // color = vec4(m_color, 1.0f);
}