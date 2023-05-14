#version 450 core

layout(location = 0) out vec4 o_Color;

in vec2 v_Position;
in vec2 v_TexCords;

uniform int u_screen_width;
uniform int u_screen_height;

uniform int u_torque;
uniform int u_wavy;
uniform int u_grayscale;
uniform int u_sharpen;
uniform int u_edges;
uniform int u_blur;

uniform sampler2D texFrameBuffer;

uniform float u_RegionX;
uniform float u_RegionY;
uniform float u_RegionWidth;
uniform float u_RegionHeight;

uniform float u_time;

const float offset = 1.0 / 300.0;

vec2 offsets[9] = vec2[](
    vec2(-offset, offset),  // top-left
    vec2(0.0f, offset),     // top-center
    vec2(offset, offset),   // top-right
    vec2(-offset, 0.0f),    // center-left
    vec2(0.0f, 0.0f),       // center-center
    vec2(offset, 0.0f),     // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f, -offset),    // bottom-center
    vec2(offset, -offset)   // bottom-right    
    );


vec4 applyNormal()
{
    return texture(texFrameBuffer, v_TexCords);
}

vec4 applyTorque(vec4 color, float strength)
{
    vec2 pos = vec2(v_TexCords.x + sin(u_time) * strength / 100, v_TexCords.y + cos(u_time) * strength / 100);
    return texture(texFrameBuffer, pos);
}

vec4 applyWavy(vec4 color, bool x, bool y)
{
    vec2 f_TexCords = v_TexCords;
    if (x)                 // f_TexCords.y * 4 * 2 * pi  // u_time * 2 * pi * 0.75 
        f_TexCords.x += sin((f_TexCords.y * 25.13274123) + (u_time * 4.71238898)) / 100;
    if (y)
        f_TexCords.y += sin((f_TexCords.x * 25.13274123) + (u_time * 4.71238898)) / 100;

    return texture(texFrameBuffer, f_TexCords);
}

vec4 applyGrayscale(vec4 color)
{
    vec4 Color = texture(texFrameBuffer, v_TexCords);
    float average = 0.2126 * Color.r + 0.7152 * Color.g + 0.0722 * Color.b;
    return vec4(average, average, average, 1.0);
}

vec4 applySharpen(vec4 color)
{
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
        );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texFrameBuffer, v_TexCords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col, 1.0);
}

vec4 applyEdges(vec4 color)
{
    float kernel[9] = float[](
        1,  1, 1,
        1, -8, 1,
        1,  1, 1
        );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texFrameBuffer, v_TexCords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col, 1.0);
}

vec4 applyBlur(vec4 color)
{
    float kernel[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
        );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texFrameBuffer, v_TexCords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return vec4(col, 1.0);
}

void main()
{
    float screenX = (v_Position.x + 1.0) * u_screen_width / 2;
    float screenY = (1.0 - v_Position.y) * u_screen_height / 2;

    // Check if the fragment falls within the specified region
    if (screenX >= u_RegionX && screenX < u_RegionX + u_RegionWidth &&
        screenY >= u_RegionY && screenY < u_RegionY + u_RegionHeight)
    {
        vec4 color = applyNormal();

        if (u_torque == 1)
        {
            color = applyTorque(color, 5);
        }
        if (u_wavy == 1)
        {
            color = applyWavy(color, true, true);
        }
        if (u_grayscale == 1)
        {
            color = applyGrayscale(color);
        }
        if (u_sharpen == 1)
        {
            color = applySharpen(color);
        }
        if (u_edges == 1)
        {
            color = applyEdges(color);
        }
        if (u_blur == 1)
        {
            color = applyBlur(color);
        }

        o_Color = color;
    }
    else
    {
        vec4 color = applyNormal();
        o_Color = color;
    }
}
