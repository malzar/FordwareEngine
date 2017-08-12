#include "Light.h"

Light::Light(vec3 pos, vec3 dir, vec3 ambient, vec3 diffuse, vec3 specular, LType lType, int number) {
	switch (lType) {
	case DIRECTIONAL:
		Ldirection = dir;
		break;
	case POINT:
		Lpos = pos;
		break;
	case SPOT:
		Lpos = pos;
		Ldirection = dir;
		break;
	default:
		break;
	}
	LightType = lType;
	Lambient = ambient;
	Ldiffuse = diffuse;
	Lspecular = specular;
	lightNumber = number;
}


void Light::SetAtt(float constant, float lineal, float quadratic) {
	c1 = constant;
	c2 = lineal;
	c3 = quadratic;
}

void Light::SetAperture(float min, float max) {
	MinAperture = cos(radians(min));
	MaxAperture = cos(radians(max));
}

void Light::SetLight(Shader *shad, vec3 CamPos) {
	std::string variable;

	glUniform3f(glGetUniformLocation(shad->Program, "viewPos"), CamPos.x, CamPos.y, CamPos.z);
	switch (LightType){
	case DIRECTIONAL:
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.direction"), Ldirection.x, Ldirection.y, Ldirection.z);
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.ambient"), Lambient.x, Lambient.y, Lambient.z);
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.diffuse"), Ldiffuse.x, Ldiffuse.y, Ldiffuse.z);
		glUniform3f(glGetUniformLocation(shad->Program, "dlight.specular"), Lspecular.x, Lspecular.y, Lspecular.z);
		break;
	case POINT:		
		variable = "plight[" + std::to_string(lightNumber) + "]";		
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".position").c_str()), Lpos.x, Lpos.y, Lpos.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".ambient").c_str()), Lambient.x, Lambient.y, Lambient.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".diffuse").c_str()), Ldiffuse.x, Ldiffuse.y, Ldiffuse.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".specular").c_str()), Lspecular.x, Lspecular.y, Lspecular.z);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".c1").c_str()), c1);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".c2").c_str()), c2);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".c3").c_str()), c3);
		break;
	case SPOT:
		variable = "slight[" + std::to_string(lightNumber) + "]";
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".direction").c_str()), Ldirection.x, Ldirection.y, Ldirection.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".position").c_str()), Lpos.x, Lpos.y, Lpos.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".ambient").c_str()), Lambient.x, Lambient.y, Lambient.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".diffuse").c_str()), Ldiffuse.x, Ldiffuse.y, Ldiffuse.z);
		glUniform3f(glGetUniformLocation(shad->Program, (variable + ".specular").c_str()), Lspecular.x, Lspecular.y, Lspecular.z);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".c1").c_str()), c1);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".c2").c_str()), c2);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".c3").c_str()), c3);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".minAperture").c_str()), MinAperture);
		glUniform1f(glGetUniformLocation(shad->Program, (variable + ".maxAperture").c_str()), MaxAperture);
		break;
	default:
		break;
	}	
}

void Light::Rotate(vec3 rotation) {	
	glm::mat4 matR;
	matR = rotate(matR, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	matR = rotate(matR, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	matR = rotate(matR, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
	vec3 dtemp = Ldirection;
	vec4 aux = matR*vec4(dtemp,1.0f);

	Ldirection.x += aux.x;
	Ldirection.y += aux.y;
	Ldirection.z += aux.z;
}

void Light::SetDirection(vec3 dir) {
	Ldirection = dir;
}

void Light::SetPosition(vec3 pos) {
	Lpos = pos;
}

vec3 Light::GetColor() {
	return ((Lambient+Ldiffuse+Lspecular+vec3(1.f))/4.0f);
}