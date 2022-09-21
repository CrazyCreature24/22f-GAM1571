

attribute vec2 a_position;

uniform vec2 u_offset;

void main()
{
	vec2 pos = a_position + vec2(u_offset);
	gl_Position = vec4(pos, 0, 1);
}