#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture_coord;

out vec3 m_color;
out vec2 m_texture_coord;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	gl_Position = u_projection * vec4(position, 1.0);

	// Отвечает за масштабирование если изменять после применение матрицы
	// Так же отрисовывает вершины у которого координата z = 0
	// При w == 1 получается ортографическая проекция
	gl_Position.w = 1.0f;

	// Не влияет на отрисовку, так как w == 1
	gl_Position.z = 0.6f;

	m_color = color;

	m_texture_coord = texture_coord;
}