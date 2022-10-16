

attribute vec2 a_Position;

attribute vec4 a_Color;

uniform vec2 u_Offset;

uniform vec2 u_Scale;

uniform float u_Rotation;

uniform float u_Aspect;

varying vec4 v_Color;



void main()
{
	vec2 pos = a_Position;
	vec2 scale = u_Scale;
	float angle = u_Rotation / 180.0 * 3.1415;
	vec4 color = a_Color;

	//Scale
	pos *= scale;

	//Rotate
	vec2 temp = pos;
	pos.x = (cos(angle) * temp.x) + (-sin(angle) * temp.y);
	pos.y = (sin(angle) * temp.x) + (cos(angle) * temp.y);

	//Translate
	pos = pos + vec2(u_Offset);
	gl_Position = vec4(pos / 10, 0, 1); //Remember to divide by 10 for Assignment

	gl_Position *= vec4(u_Aspect, 1, 1, 1);

	color /= vec4(255, 255, 255, 255);

	v_Color = color;
}