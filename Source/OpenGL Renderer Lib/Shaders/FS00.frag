#version 450

out vec3 color;
in vec3 frag_vert_coord;
in vec3 frag_normal;
in vec2 frag_texture_coord;

uniform sampler2D tex2d;

void main()
{
	vec3 light = vec3(-2.0, 0.0, -2.0);
	color = texture(tex2d, frag_texture_coord).xyz * vec3(dot(normalize(frag_normal), normalize(frag_vert_coord - light)));
}