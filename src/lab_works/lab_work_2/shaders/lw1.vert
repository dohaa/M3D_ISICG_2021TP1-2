#version 450


layout( location = 0 ) in vec2 aVertexPosition;
layout( location = 1 ) in vec3 aVertexColor;

uniform float uTranslationX;

out vec3 varc;
void main() {
	varc = aVertexColor;
	gl_Position = vec4(aVertexPosition.x + uTranslationX,aVertexPosition.y,0.f,1.f);
	
}
