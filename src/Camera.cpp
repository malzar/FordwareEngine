#include "Camera.h"
#include <iostream>

Camera::Camera(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov){
	cameraPos = position;
	cameraFront = direction;
	cameraUp = vec3(0.0f, 1.0f, 0.0f);
	Deltatime = 0;
	Lastframe = 0;
	//LastMx = 0;
	//LastMy = 0;
	Sensitivity = sensitivity;
	firstMouse = true;
	PITCH = 90 - degrees(acos(dot(vec3(0.f, cameraFront.y, cameraFront.z), vec3(0.f, 1.f, 0.f))));;
	YAW = 90-degrees(acos(dot(vec3(cameraFront.x, 0.0, cameraFront.z), vec3(0.f, 0.f, 1.f))));
	FOV = fov;
}


Camera::~Camera()
{
}

mat4 Camera::LookAt() {
	mat4 cLookAt;
	vec3 position = cameraPos;
	vec3 target = cameraPos + cameraFront;
	vec3 up = cameraUp;

	vec3 cDirection = normalize(position - target);
	vec3 cRigth = normalize(cross(up, cDirection));
	vec3 cUp = normalize(cross(cDirection, cRigth));

	mat4 rotation, translation;

	rotation[0][0] = cRigth.x; 
	rotation[1][0] = cRigth.y;
	rotation[2][0] = cRigth.z;
	rotation[0][1] = cUp.x; 
	rotation[1][1] = cUp.y;
	rotation[2][1] = cUp.z;
	rotation[0][2] = cDirection.x;
	rotation[1][2] = cDirection.y;
	rotation[2][2] = cDirection.z;

	translation[3][0] = -position.x; 
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;

	cLookAt = rotation* translation;
	return cLookAt;
}

void Camera::DoMovement(GLFWwindow * window) {
	GLfloat currentFrame = glfwGetTime();
	Deltatime = currentFrame - Lastframe;
	Lastframe = currentFrame;

	float cameraSpeed = Deltatime*4;
	float cameraSpeedRotation = cameraSpeed*0.75;

	int state;
	state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
	if (state == GLFW_PRESS) {
		cameraSpeed *= 10.f;
	}

	state = glfwGetKey(window, GLFW_KEY_W);
	if (state == GLFW_PRESS) {
		cameraPos += cameraFront*cameraSpeed;
	}
	state = glfwGetKey(window, GLFW_KEY_S);
	if (state == GLFW_PRESS) {
		cameraPos -= cameraFront*cameraSpeed;
	}
	state = glfwGetKey(window, GLFW_KEY_A);
	if (state == GLFW_PRESS) {
		cameraPos += normalize(cross(cameraUp, cameraFront))*cameraSpeed;
	}
	state = glfwGetKey(window, GLFW_KEY_D);
	if (state == GLFW_PRESS) {
		cameraPos -= normalize(cross(cameraUp, cameraFront))*cameraSpeed;
	}
	state = glfwGetKey(window, GLFW_KEY_Q);
	if (state == GLFW_PRESS) {
		cameraFront += normalize(cross(cameraUp, cameraFront))*cameraSpeedRotation;
	}
	state = glfwGetKey(window, GLFW_KEY_E);
	if (state == GLFW_PRESS) {
		cameraFront -= normalize(cross(cameraUp, cameraFront))*cameraSpeedRotation;
	}
}
void Camera::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - LastMx;
	GLfloat yoffset = LastMy - ypos;
	LastMx = xpos;
	LastMy = ypos;

	PITCH += yoffset *Sensitivity;
	PITCH = clamp(PITCH, -89.f, 89.f);
	YAW += xoffset *Sensitivity;
	YAW = mod(YAW, 360.f);
	vec3 look;
	look.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
	look.y = sin(glm::radians(PITCH));
	look.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
	cameraFront = normalize(look);
}


void Camera::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	FOV = clamp((float)(FOV - yScroll), 1.0f, 120.0f);
}

GLfloat Camera::GetFOV() {
	return FOV;
}

vec3 Camera::GetPosition() {
	return cameraPos;
}

vec3 Camera::GetDirection() {
	return cameraFront;
}