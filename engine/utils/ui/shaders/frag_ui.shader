#version 450 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCords;
in float v_TexArrayID;

uniform sampler2DArray u_TexArray;

void main()
{
    int id = int(v_TexArrayID);
    if (id == 0)
    {
        o_Color = v_Color;
    }
    else
    {
        vec4 tex_color = texture(u_TexArray, vec3(v_TexCords, id));
        o_Color = vec4(v_Color.rgb, tex_color.a * v_Color.a);
    }
}
