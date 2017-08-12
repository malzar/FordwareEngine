#version 330 core

//in vec2 TexCoords;

out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main(){    

    color = vec4(lightColor, 1.0f);
}
