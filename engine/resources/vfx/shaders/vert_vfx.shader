#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCords;

out vec2 v_Position;
out vec2 v_TexCords;

void main()
{
    v_Position = a_Position;
    v_TexCords = a_TexCords;

    gl_Position = vec4(a_Position, 0.0, 1.0);
}