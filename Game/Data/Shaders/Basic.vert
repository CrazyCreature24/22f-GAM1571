

attribute vec2 a_position;

uniform vec2 u_offset;

uniform vec2 u_scale;

void main()
{
	vec2 pos = a_position + vec2(u_offset);
	vec2 scale = vec2(u_scale);
	gl_Position = vec4(pos * scale, 0, 1);
}