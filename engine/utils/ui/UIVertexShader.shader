#version 450 core

layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_tex;

uniform mat4 u_projection;

out vec2 v_tex_cords;

void main()
{
	v_tex_cords = a_tex;
	gl_Position = u_projection * vec4(a_pos, 0.0, 1.0);
}