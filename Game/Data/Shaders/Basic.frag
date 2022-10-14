uniform float iGlobalTime;
uniform vec4 iDate;
uniform vec3 iResolution;
varying vec4 v_Color;
uniform vec4 u_Color;

void main()
{
	
	gl_FragColor = v_Color + u_Color;
}