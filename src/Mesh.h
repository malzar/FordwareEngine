#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
//OpenGLPart
#include <GL\glew.h>
#include<glm.hpp>
#include <gtc\matrix_transform.hpp>
using namespace glm;
#include "Shader.h"
#include <assimp\types.h>

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh{
public:

	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vert, vector<GLuint> ind, vector<Texture> text);
	void Draw(Shader MeshShader, GLint DrawMode);

private:

	GLuint VAO, VBO, EBO;
	void setupMesh();
};

