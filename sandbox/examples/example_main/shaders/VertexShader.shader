#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCords;
layout(location = 3) in float a_TexID;

uniform mat4 u_MVP;
uniform vec4 u_Color;

out vec4 v_uColor;
out vec4 v_Color;
out vec2 v_TexCords;
out float v_TexID;

void main()
{
    v_uColor = u_Color;
    v_Color = a_Color;
    v_TexCords = a_TexCords;
    v_TexID = a_TexID;
    gl_Position = u_MVP * vec4(a_Position, 1.0, 1.0);
}
