#version 450

in vec3 vert_coord;
in vec3 normal;
in vec2 texture_coord;
out vec2 frag_texture_coord;
out vec3 frag_normal;
out vec3 frag_vert_coord;

uniform float g;

void main()
{
	gl_Position = vec4(vert_coord/**g*/, 1.0);
	frag_normal = normal;
	frag_texture_coord = texture_coord;
	frag_vert_coord = vert_coord;
}