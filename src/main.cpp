//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
#include "Model.h"
#include "Object.h"
#include "material.h"
#include "Light.h"

using namespace std;
using namespace glm;
const GLint WIDTH = 800, HEIGHT = 600;


bool WIDEFRAME = false;
bool PERSPECTIVE = true;

Camera *cam = new Camera(vec3(0.0f, 0.f, -5.f), vec3(0.f, 0.f, 1.f), 0.05f, 45.f);
Object *Movilecubo;
Light * Ldirec;

//Captation function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseMove(GLFWwindow* window, double xpos, double ypos);
void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);

int main() {
	if (!glfwInit()) {
		cout << "Error al cargar GLFW" << endl;
		exit(EXIT_FAILURE);
	}

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//create a window
	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Control de camara", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana GLFW" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << "Error al inicizar glew" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//set windows and viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenWidth);	

	//set function when callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, MouseMove);
	glfwSetScrollCallback(window, MouseScroll);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//fondo
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//cargamos los shader
	Shader *SimpleShader = new Shader("./src/Shader/VertexShaderEstandar.vs", 
		                              "./src/Shader/FragmentShaderEstandar.fs");

	Shader* PhongShader = new Shader("./src/Shader/VertexShaderPhongTexture.vs",
									"./src/Shader/FragmentShaderPhongTexture.fs");

	Shader* PhongShaderNoText = new Shader("./src/Shader/VertexShaderPhong.vs",
										   "./src/Shader/FragmentShaderPhong.fs");

	//objetos
	Movilecubo = new Object(vec3(2.0f), vec3(0.0f), vec3(0.0f), Object::CUBE);
	Object * BigCube = new Object(vec3(9.0f), vec3(0.0f), vec3(0.0f), Object::INVERSECUBE);
	Object * Lamp1 = new Object(vec3(0.1f), vec3(0.0f), vec3( 5.0f, 4.5f, 0.0f), Object::CUBE);
	Object * Lamp2 = new Object(vec3(0.1f), vec3(0.0f), vec3( 2.f, 4.5f, 0.0f), Object::CUBE);
	Object * Lamp3 = new Object(vec3(0.1f), vec3(0.0f), vec3( -2.0f, 4.5f, 0.0f), Object::CUBE);
	Object * Lamp4 = new Object(vec3(0.1f), vec3(0.0f), vec3( -5.0f, 4.5f, 0.0f), Object::CUBE);

	//materiales
	Material * wall = new Material("./src/Materials/difuso.png", "./src/Materials/especular.png", 320.0f);
	Material * white = new Material("./src/Materials/difusoWhite.png", "./src/Materials/difusoWhite.png", 200);

	//luces
	Ldirec = new Light(vec3(0.0f),vec3(0.0f, -1.0f, 0.0f), vec3(0.1f), vec3(0.1f), vec3(0.1f), Light::DIRECTIONAL,-1);

	Light * Plight1 = new Light(Lamp1->GetPosition(), vec3(0.0f), vec3(0.5f), vec3(0.4f), vec3(0.4f), Light::POINT, 0);
	Plight1->SetAtt(1.0f, 0.05f, 0.01f);

	Light * Plight2 = new Light(Lamp3->GetPosition(), vec3(0.0f), vec3(0.f,0.f,0.5f), vec3(0.f, 0.f, 0.4f), vec3(0.f, 0.f, 0.4f), Light::POINT, 1);
	Plight2->SetAtt(1.0f, 0.05f, 0.01f);

	Light * Slight1 = new Light(Lamp2->GetPosition(), vec3(0.0f, -1.0f, 0.0f), vec3(0.5f, 0.f,0.f), vec3(0.4f, 0.f, 0.f), vec3(0.3f, 0.f, 0.f), Light::SPOT, 0);
	Slight1->SetAtt(1.0f, 0.01f, 0.003f);
	Slight1->SetAperture(10.0f, 35.f);

	Light * Slight2 = new Light(Lamp4->GetPosition(), vec3(-1.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.f), vec3(0.4f, 0.4f, 0.f), vec3(0.3f, 0.3f, 0.f), Light::SPOT, 1);
	Slight2->SetAtt(1.0f, 0.001f, 0.0003f);
	Slight2->SetAperture(20.0f, 40.f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	while (!glfwWindowShouldClose(window)){
		cam->DoMovement(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);
		
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenWidth);	

		mat4 Mproject;
		if (screenWidth>screenHeight)
			Mproject = perspective(radians(cam->GetFOV()), (float) screenWidth / screenHeight, 0.3f, 100.0f);
		else
			Mproject = perspective(radians(cam->GetFOV()), (float) screenHeight / screenWidth, 0.3f, 100.0f);

		//big cube
		PhongShader->Use();
		PhongShader->SetMatrix(BigCube->GetModelMatrix(), cam->LookAt(), Mproject);
		white->ActivateTextures();
		white->SetMaterialTextured(PhongShader);

		//Ldirec->SetLight(PhongShaderNoText, cam->GetPosition());
		//Plight1->SetLight(PhongShader, cam->GetPosition());
		//Plight2->SetLight(PhongShader, cam->GetPosition());

		//Slight1->SetLight(PhongShader, cam->GetPosition());
		//Slight2->SetLight(PhongShader, cam->GetPosition());

		BigCube->Draw();

		//normal cube
		//PhongShader->Use();
		PhongShader->SetMatrix(Movilecubo->GetModelMatrix(), cam->LookAt(), Mproject);

		wall->ActivateTextures(); 
		wall->SetMaterialTextured(PhongShader);

		Ldirec->SetLight(PhongShader, cam->GetPosition());
		Plight1->SetLight(PhongShader, cam->GetPosition());
		Plight2->SetLight(PhongShader, cam->GetPosition());

		Slight1->SetLight(PhongShader, cam->GetPosition());
		Slight2->SetLight(PhongShader, cam->GetPosition());

		Movilecubo->Draw();

		//draw lamp
		SimpleShader->Use();

		SimpleShader->SetMatrix(Lamp1->GetModelMatrix(), cam->LookAt(), Mproject);
		SimpleShader->SetLightValues(Lamp1->GetPosition(), Plight1->GetColor(), cam->GetPosition(), vec3(1.0f));
		Lamp1->Draw();

		SimpleShader->SetMatrix(Lamp3->GetModelMatrix(), cam->LookAt(), Mproject);
		SimpleShader->SetLightValues(Lamp3->GetPosition(), Plight2->GetColor(), cam->GetPosition(), vec3(1.0f));
		Lamp3->Draw();

		SimpleShader->SetMatrix(Lamp2->GetModelMatrix(), cam->LookAt(), Mproject);
		SimpleShader->SetLightValues(Lamp2->GetPosition(), Slight1->GetColor(), cam->GetPosition(), vec3(1.0f));
		Lamp2->Draw();

		SimpleShader->SetMatrix(Lamp4->GetModelMatrix(), cam->LookAt(), Mproject);
		SimpleShader->SetLightValues(Lamp4->GetPosition(), Slight2->GetColor(), cam->GetPosition(), vec3(1.0f));
		Lamp4->Draw();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Terminate GLFW, clearing any resources allocated by GLFW.
	Movilecubo->Delete();
	Lamp1->Delete();
	glfwTerminate();
	return 0;
	exit(EXIT_SUCCESS);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	int state;
	state = glfwGetKey(window, GLFW_KEY_ESCAPE); 
	if (state == GLFW_PRESS) {
		cout << "Bye, bye" << endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
		exit(EXIT_SUCCESS);
	}
	state = glfwGetKey(window, GLFW_KEY_SPACE); 
	if (state == GLFW_PRESS) {
		WIDEFRAME = !WIDEFRAME;
	}
	state = glfwGetKey(window, GLFW_KEY_1); 
	if (state == GLFW_PRESS) {
		
	}
	state = glfwGetKey(window, GLFW_KEY_2); 
	if (state == GLFW_PRESS) {
		
	}
	state = glfwGetKey(window, GLFW_KEY_RIGHT); 
	if (state == GLFW_PRESS) {
		Movilecubo->Move(vec3(-0.05f, 0.f, 0.f));
	}
	state = glfwGetKey(window, GLFW_KEY_LEFT); 
	if (state == GLFW_PRESS) {
		Movilecubo->Move(vec3(0.05f, 0.f, 0.f));
	}
	state = glfwGetKey(window, GLFW_KEY_UP);
	if (state == GLFW_PRESS) {
		Movilecubo->Move(vec3(0.f, 0.05f, 0.f));
	}
	state = glfwGetKey(window, GLFW_KEY_DOWN); 
	if (state == GLFW_PRESS) {
		Movilecubo->Move(vec3(0.f, -0.05f, 0.f));
	}	
	state = glfwGetKey(window, GLFW_KEY_KP_6);
	if (state == GLFW_PRESS) {
		Movilecubo->Rotate(vec3(0.f, 0.f, 1.f));
	}
	state = glfwGetKey(window, GLFW_KEY_KP_4); 
	if (state == GLFW_PRESS) {
		Movilecubo->Rotate(vec3(0.f, 0.f, -1.f));
	}
	state = glfwGetKey(window, GLFW_KEY_KP_8);
	if (state == GLFW_PRESS) {
		Movilecubo->Rotate(vec3(1.f, 0.f, 0.f));
	}
	state = glfwGetKey(window, GLFW_KEY_KP_2);
	if (state == GLFW_PRESS) {
		Movilecubo->Rotate(vec3(-1.f, 0.f, 0.f));		
	}
	state = glfwGetKey(window, GLFW_KEY_P); 
	if (state == GLFW_PRESS) {
		PERSPECTIVE = true;
	}
	state = glfwGetKey(window, GLFW_KEY_O); 
	if (state == GLFW_PRESS) {
		PERSPECTIVE = false;
	}
}

void MouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (cam)
		cam->MouseMove(window, xpos, ypos);
}

void MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	if (cam)
		cam->MouseScroll(window, xScroll, yScroll);
}