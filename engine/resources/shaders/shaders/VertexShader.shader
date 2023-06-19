#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCords;
layout(location = 3) in float a_TexArrayID;
layout(location = 4) in float a_inst;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_TexCords;
out float v_TexArrayID;

void main()
{
    v_Color = a_Color;
    v_TexCords = vec2(a_TexCords.x, 1 - a_TexCords.y);
    v_TexArrayID = a_TexArrayID;
    
    gl_Position = u_MVP * vec4(a_Position, 0.0, 1.0);
}