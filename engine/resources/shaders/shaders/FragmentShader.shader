#version 450 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCords;
in float v_TexArrayID;
in float v_TexArrayIdx;

uniform sampler2DArray u_TexArray[8];

void main()
{
    int id = int(v_TexArrayID);
    if (id == 0)
    {
        o_Color = v_Color;
    }
    else
    {
        int idx = int(v_TexArrayIdx);
        o_Color = texture(u_TexArray[id], vec3(v_TexCords, idx));
    }
}
