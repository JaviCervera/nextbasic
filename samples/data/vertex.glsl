uniform mat4 MVP;
attribute vec3 vpos;
attribute vec2 vtex;
varying vec2 ftex;
	
void main() {
	gl_Position = MVP * vec4(vpos, 1);
	ftex = vtex;
}