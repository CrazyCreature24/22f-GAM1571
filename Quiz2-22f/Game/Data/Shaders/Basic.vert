attribute vec2 a_Position;

uniform vec2 u_Scale;
uniform float u_Angle;
uniform vec2 u_Offset;

vec2 TransformIntoWorldSpace(vec2 pos);

void main()
{
	vec2 objectSpacePosition = a_Position;
	vec2 worldSpacePosition = TransformIntoWorldSpace( objectSpacePosition );
	vec2 viewSpacePosition = worldSpacePosition; //- u_CameraPosition;
	vec2 clipSpacePosition = viewSpacePosition; //* u_ProjectionScale;
	gl_Position = vec4( clipSpacePosition, 0, 1 );
}

vec2 TransformIntoWorldSpace(vec2 pos)
{
	// Scale.
	pos *= u_Scale;
	
	// Rotate.
	float newX = cos(u_Angle)*pos.x + -sin(u_Angle)*pos.y;
	float newY = sin(u_Angle)*pos.x + cos(u_Angle)*pos.y;
	pos = vec2(newX, newY);
	
	// Translate.
	pos += u_Offset;

	return pos;
}
