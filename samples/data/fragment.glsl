#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texSampler;
varying vec2 ftex;
void main() {
	gl_FragColor = texture2D(texSampler, ftex);
}