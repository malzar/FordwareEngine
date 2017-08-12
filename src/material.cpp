#include "material.h"

Material::Material(char *DiffPath, char*SpectPath, float Shini){
	glGenTextures(1, &TextDiff);
	glGenTextures(2, &TextSpec);

	int width, height;
	unsigned char* image;
	glBindTexture(GL_TEXTURE_2D, TextDiff); {
		image = SOIL_load_image(DiffPath, &width, &height, 0, SOIL_LOAD_RGB);
		glBindTexture(GL_TEXTURE_2D, TextDiff);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	}glBindTexture(GL_TEXTURE_2D, TextSpec); {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		image = SOIL_load_image(SpectPath, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}glBindTexture(GL_TEXTURE_2D, 0);

	Shininess = Shini;
}

Material::Material(vec3 Diffuse, vec3 Specular, float Shini) {
	DiffColor = Diffuse;
	SpeColor = Specular;
}

Material::~Material(){
}

void Material::SetMaterialTextured(Shader *shad) {
	glUniform1i(glGetUniformLocation(shad->Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(shad->Program, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(shad->Program, "material.shininess"), Shininess);
}

void Material::SetMaterialNoTextured(Shader *shad) {
	glUniform3f(glGetUniformLocation(shad->Program, "material.diffuse"), DiffColor.x, DiffColor.y, DiffColor.z);
	glUniform3f(glGetUniformLocation(shad->Program, "material.specular"), SpeColor.x, SpeColor.y, SpeColor.z);
	glUniform1f(glGetUniformLocation(shad->Program, "material.shininess"), Shininess);
}

void Material::SetShininess(Shader *shad) {
	glUniform1f(glGetUniformLocation(shad->Program, "material.shininess"), Shininess);
}

void Material::ActivateTextures() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextDiff);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextSpec);
}
