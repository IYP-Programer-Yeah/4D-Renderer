#version 450

in vec2 vert_coord;
out vec3 frag_color;	

uniform float g;								

void main()
{
	gl_Position = vec4(vert_coord*g, 1.0, 1.0);
	vec2 normalized_ver_coord = (vert_coord + vec2(1.0,1.0))/2.0;
	frag_color = vec3(normalized_ver_coord, length(normalized_ver_coord)/3);
}