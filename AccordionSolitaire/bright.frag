uniform sampler2D texture;

void main()
{
	// lookup the pixel from the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0]);

	// set color
	gl_FragColor = gl_Color * pixel;
}