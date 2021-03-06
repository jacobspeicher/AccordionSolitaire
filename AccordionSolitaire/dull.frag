uniform sampler2D texture;
uniform float alpha;

void main()
{
	// lookup the pixel color in the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	// multiply by the color
	vec4 color = vec4((gl_Color * pixel).rgb, alpha);

	gl_FragColor = color;
}