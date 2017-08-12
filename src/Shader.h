#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include<glm.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

class Shader{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void Use();
	void SetMatrix(mat4 ModelView, mat4 CameraView, mat4 ProjectionView);
	void SetLightValues(vec3 LightPos, vec3 LightColor, vec3 CamPos, vec3 ObjectColor);
	void SetDepth(float NearPlane, float FarPlane);
};

#endif
