varying vec4 v_Color;
uniform vec4 u_Color;
varying vec2 v_UV;

void main()
{
	
	gl_FragColor = vec4(v_UV, 0, 1);
	
}