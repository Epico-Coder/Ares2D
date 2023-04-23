#version 450 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

uniform mat4 u_MVP;
out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}
