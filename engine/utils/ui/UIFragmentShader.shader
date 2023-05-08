#version 450 core

out vec4 o_Color;

uniform sampler2D u_text;
uniform vec4 u_text_color;

in vec2 v_tex_cords;

void main()
{
	//vec4 sampled = texture(u_text, v_tex_cords);
	//o_Color = v_text_color * sampled;
	//o_Color *= sampled.r;
	//o_Color = sampled;

	vec4 sampled = texture(u_text, v_tex_cords);
	o_Color = vec4(sampled.rgb, 1.0) * u_text_color;
	o_Color = sampled;

	//vec4 sampled = vec4(0.0, 1.0, 0.0, texture(u_text, v_tex_cords).r);
	//o_Color = mix(v_bg_color, v_text_color, sampled.a);
	//o_Color = texture(u_text, v_tex_cords);
}
