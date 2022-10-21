attribute vec2 a_Position;

attribute vec2 a_UV;

uniform vec2 u_Offset;

uniform vec2 u_Scale;

uniform float u_Rotation;

uniform float u_Aspect;

varying vec2 v_UV;



void main()
{
	vec2 pos = a_Position;
	vec2 scale = u_Scale;
	float angle = u_Rotation / 180.0 * 3.1415;
	vec2 uv = a_UV;

	//Scale
	pos *= scale;

	//Rotate
	vec2 temp = pos;
	pos.x = (cos(angle) * temp.x) + (-sin(angle) * temp.y);
	pos.y = (sin(angle) * temp.x) + (cos(angle) * temp.y);

	//Translate
	pos = pos + vec2(u_Offset);
	gl_Position = vec4(pos / 10, 0, 1); 

	gl_Position *= vec4(u_Aspect, 1, 1, 1);

	v_UV = uv;
}