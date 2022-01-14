#version 450

layout( location = 0 ) out vec4 aFrag;

in vec3 varc;

uniform float shade;
void main() {
	aFrag = shade + vec4(varc,1.f);
	
}
