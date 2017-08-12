#version 330 core

//in vec2 TexCoords;

out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform float Near; 
uniform float Far;

float DepthLineal(float depth);
float DepthNonLineal(float depth);

void main(){    

    color = vec4(vec3(DepthNonLineal(gl_FragCoord.z)), 1.0f);
	
}

float DepthLineal(float depth){

	float value = ((depth-Near)/(Far-Near));

	return value;	
}

float DepthNonLineal(float depth){
	
	float z = depth * 2.0 - 1.0;
	return ((2.0 * Near * Far) / (Far + Near - z * (Far - Near))/Far);	
}