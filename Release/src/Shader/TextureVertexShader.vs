#version 330 core
layout (location = 0) in vec3 Position; // The position variable has attribute position 0
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec2 TextureCoord;
out vec3 VertexColor;

//uniform mat4 Mtransf;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	TextureCoord = TexCoord;
	VertexColor = Color;
	gl_Position = projection * view * model * vec4(Position, 1.0f);
}