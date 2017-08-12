#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <SOIL.h>
#include "Shader.h"

class Material{

public:
	Material(char *DiffPath, char*SpectPath, float Shini);
	Material(vec3 Diffuse, vec3 Specular, float Shini);
	~Material();
	void SetMaterialTextured(Shader *shad);
	void SetMaterialNoTextured(Shader *shad);
	void ActivateTextures();
	void SetShininess(Shader *shad);
private:
	GLuint TextDiff, TextSpec;
	float Shininess;
	vec3 DiffColor, SpeColor;
};

