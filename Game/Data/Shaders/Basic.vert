

attribute vec2 a_position;

uniform vec2 u_offset;

uniform vec2 u_scale;

uniform float u_rotation;

void main()
{
	vec2 pos = a_position;
	vec2 scale = u_scale;
	float angle = u_rotation / 180.0 * 3.1415;

	//Scale
	pos *= scale;

	//Rotate
	vec2 temp = pos;
	pos.x = (cos(angle) * temp.x) + (-sin(angle) * temp.y);
	pos.y = (sin(angle) * temp.x) + (cos(angle) * temp.y);

	//Translate
	pos = pos + vec2(u_offset);
	gl_Position = vec4(pos, 0, 1);
}