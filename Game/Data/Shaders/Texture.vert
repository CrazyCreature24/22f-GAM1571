attribute vec2 a_Position;

uniform vec2 u_Offset;
uniform vec2 u_Scale;
uniform float u_Rotation;
uniform vec2 u_CameraPosition;
uniform vec2 u_ProjectionScale;

attribute vec2 a_UV;
varying vec2 v_UV;
uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;


vec2 TransformIntoWorldSpace(vec2 pos);


void main()
{
	vec2 objectSpacePosition = a_Position; //Also called model or local space position
	vec2 worldSpacePosition = TransformIntoWorldSpace( objectSpacePosition );
	vec2 viewSpacePosition = worldSpacePosition - u_CameraPosition; 
	vec2 clipSpacePosition = viewSpacePosition * u_ProjectionScale;

	gl_Position = vec4(clipSpacePosition, 0, 1); 

	v_UV = a_UV * u_UVScale + u_UVOffset;
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