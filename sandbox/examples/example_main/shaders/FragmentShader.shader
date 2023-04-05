#version 450 core

layout(location = 0) out vec4 o_Color;

in vec4 v_uColor;
in vec4 v_Color;
in vec2 v_TexCords;
in float v_TexID;

void main()
{
    o_Color = v_Color;
}
