#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCords;
layout(location = 3) in float a_TexArrayID;
layout(location = 4) in float a_inst;

layout(std430, binding = 0) buffer TransformBuffer
{
    mat4 Model[];
};

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_Color;
out vec2 v_TexCords;
out float v_TexArrayID;

out float v_InstanceID;

void main()
{
    v_Color = a_Color;
    v_TexCords = vec2(a_TexCords.x, 1 - a_TexCords.y);
    v_TexArrayID = a_TexArrayID;

    v_InstanceID = gl_InstanceID;
    v_InstanceID = a_inst;

    mat4 proj = mat4
    (
        vec4(0.0015625, 0, 0, -1),
        vec4(0, 0.00277778, 0, -1),
        vec4(0, 0, -1, 0),
        vec4(0, 0, 0, 1)
    );

    gl_Position = u_Projection * u_View * Model[int(a_inst)] * vec4(a_Position, 0.0, 1.0);
    //gl_Position = u_Projection * u_View * vec4(a_Position, 0.0, 1.0);
    //gl_Position = proj * vec4(a_Position, 0.0, 1.0);
    //gl_Position = vec4(a_Position, 0.0, 1.0);
}
