#version 330 core

in vec3 m_color;

void main()
{
    gl_FragColor = vec4(m_color, 1.0);
}