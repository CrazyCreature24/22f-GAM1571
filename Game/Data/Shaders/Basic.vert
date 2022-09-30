

attribute vec2 a_Position;

uniform vec2 u_Offset;

uniform vec2 u_Scale;

uniform float u_Rotation;

void main()
{
	vec2 pos = a_Position;
	vec2 scale = u_Scale;
	float angle = u_Rotation / 180.0 * 3.1415;

	//Scale
	pos *= scale;

	//Rotate
	vec2 temp = pos;
	pos.x = (cos(angle) * temp.x) + (-sin(angle) * temp.y);
	pos.y = (sin(angle) * temp.x) + (cos(angle) * temp.y);

	//Translate
	pos = pos + vec2(u_Offset);
	gl_Position = vec4(pos, 0, 1);
}