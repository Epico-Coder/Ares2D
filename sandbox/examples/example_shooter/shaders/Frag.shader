#version 450 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCords;
in float v_TexArrayID;

in float v_InstanceID;

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
        o_Color = tex_color;
    }
    
    /*
    o_Color = vec4(0.0, 0.0, 0.0, 1.0);
    if (v_InstanceID == 0.0)
    {
        o_Color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    if (v_InstanceID == 1.0)
    {
        o_Color = vec4(0.0, 1.0, 0.0, 1.0);
    }
    if (v_InstanceID == 2.0)
    {
        o_Color = vec4(0.0, 0.0, 1.0, 1.0);
    }
    if (v_InstanceID == 3.0)
    {
        o_Color = vec4(1.0, 1.0, 0.0, 1.0);
    }
    */
}