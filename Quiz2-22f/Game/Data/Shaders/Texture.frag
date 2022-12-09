uniform sampler2D u_ColorTexture;

varying vec2 v_UV;

void main()
{
	vec4 color = texture2D( u_ColorTexture, v_UV );
	gl_FragColor = color;
}
