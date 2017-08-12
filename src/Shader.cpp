#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader(){
}

void Shader::Use() {
	glUseProgram(this->Program);
}

void Shader::SetMatrix(mat4 ModelView, mat4 CameraView, mat4 ProjectionView) {
	glUniformMatrix4fv(glGetUniformLocation(Program, "model"), 1, GL_FALSE, value_ptr(ModelView));
	glUniformMatrix4fv(glGetUniformLocation(Program, "view"), 1, GL_FALSE, value_ptr(CameraView));
	glUniformMatrix4fv(glGetUniformLocation(Program, "projection"), 1, GL_FALSE, value_ptr(ProjectionView));
}

void Shader::SetLightValues(vec3 LightPos, vec3 LightColor, vec3 CamPos, vec3 ObjectColor) {
	glUniform3f(glGetUniformLocation(Program, "lightPos"), LightPos.x, LightPos.y, LightPos.z);
	glUniform3f(glGetUniformLocation(Program, "lightColor"), LightColor.x, LightColor.y, LightColor.z);
	glUniform3f(glGetUniformLocation(Program, "viewPos"), CamPos.x, CamPos.y, CamPos.z);
	glUniform3f(glGetUniformLocation(Program, "objectColor"), ObjectColor.x, ObjectColor.y, ObjectColor.z);
}

void Shader::SetDepth(float NearPlane, float FarPlane) {
	glUniform1f(glGetUniformLocation(Program, "Near"), NearPlane);
	glUniform1f(glGetUniformLocation(Program, "Far"), FarPlane);
}