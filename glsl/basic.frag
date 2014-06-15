uniform sampler2D texture;
varying vec2 vTex;
void main(void)
{
	gl_FragColor = texture2D(texture, vTex);
}
