//Fix this to be like Texture vert

attribute vec2 a_Position;
attribute vec4 a_Color;

uniform vec2 u_Offset;
uniform vec2 u_Scale;
uniform float u_Rotation;
uniform float u_Aspect;

varying vec4 v_Color;

vec2 TransformIntoWorldSpace(vec2 pos);

void main()
{
	vec2 objectSpacePosition = a_Position; //Also called model or local space position
	vec2 worldSpacePosition = TransformIntoWorldSpace( objectSpacePosition );
	vec2 viewSpacePosition = worldSpacePosition; //- u_CameraPosition //Camera should handle the u_Aspect
	vec2 clipSpacePosition = viewSpacePosition * 0.1; //* u_ProjectionScale

	gl_Position = vec4(clipSpacePosition, 0, 1); 
	gl_Position *= vec4(u_Aspect, 1, 1, 1);

	v_Color = a_Color;
}

vec2 TransformIntoWorldSpace(vec2 pos)
{
	//Scale
	pos *= u_Scale;

	//Rotate
	vec2 temp = pos;
	pos.x = (cos(u_Rotation / 180.0 * 3.1415) * temp.x) + (-sin(u_Rotation / 180.0 * 3.1415) * temp.y);
	pos.y = (sin(u_Rotation / 180.0 * 3.1415) * temp.x) + (cos(u_Rotation / 180.0 * 3.1415) * temp.y);

	//Translate
	pos = pos + vec2(u_Offset);

	return pos;
}