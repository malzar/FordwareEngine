#include "Object.h"

Object::Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef){
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	GLfloat *VertexBufferObject;
	int numVertex;
	switch (typef){
	case Object::CUBE:
		numVertex = 288;
		VertexBufferObject = new GLfloat[numVertex]{
			//front
			1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			1.0f , -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			//back
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			1.0f , -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			1.0f ,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			1.0f ,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			//left	
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			//right
			1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			1.0f ,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			1.0f , -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			//down
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			1.0f , -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			//up
			1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			1.0f ,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
		};
		break;
	case Object::SPHERE:
		break;
	case Object::INVERSECUBE:
		numVertex = 288;
		VertexBufferObject = new GLfloat[numVertex]{
			//front
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
			1.0f , -1.0f, -1.0f,  0.0f,  0.0f, 1.0f,  1.0f,  0.0f,
			1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,

			1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
			//back
			1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			1.0f , -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			//left	
			-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			//right
			1.0f ,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			1.0f ,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			1.0f , -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,

			1.0f , -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			1.0f , -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			1.0f ,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			//down
			1.0f , -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			1.0f , -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,

			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			1.0f , -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			//up
			-1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			1.0f ,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			1.0f ,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,

			1.0f ,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f
		};
		break;
	default:
		break;
	}

	this->scale = scale;
	this->rotation = rotation;
	this->position = position;
	glBindVertexArray(VAO); {
		//Declarar el tipo de buuffer
		//Enlazar el buffer con openGL
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, numVertex * sizeof(VertexBufferObject), &VertexBufferObject[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

		//Establecer las propiedades de los vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		//Establecer las propiedades de los vertices
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
		//Establecer las propiedades de los vertices
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);

		//liberar el buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}glBindVertexArray(0);
}


Object::~Object()
{
}
void Object::Draw() {
	glBindVertexArray(VAO); {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}glBindVertexArray(0);
}
void Object::Move(vec3 translation) {
	position += translation;
}
void Object::Rotate(vec3 rota) {
	rotation += rota;
}
void Object::Scale(vec3 scal){
}

mat4 Object::GetModelMatrix() {
	mat4 ModelMatrix;
	if (position.x != 0 || position.y != 0 || position.z != 0)
		ModelMatrix = glm::translate(ModelMatrix, position);
	if (rotation.z != 0)
		ModelMatrix = glm::rotate(ModelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));
	if (rotation.y != 0)
		ModelMatrix = glm::rotate(ModelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));
	if (rotation.x != 0)
		ModelMatrix = glm::rotate(ModelMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));
	if (scale.x != 0 || scale.y != 0 || scale.z != 0)
		ModelMatrix = glm::scale(ModelMatrix, scale);

	return ModelMatrix;
}

vec3 Object::GetPosition() {
	return vec3 (position.x, position.y,position.z);
}

void Object::Delete() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}