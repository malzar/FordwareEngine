#version 330 core
in vec2 TextureCoord;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float selectionValue;

void main(){
	vec2 tex = vec2 (TextureCoord.x, 1.0f - TextureCoord.y);
	color = mix(texture(texture1,tex),texture(texture2,tex),selectionValue);
}