#version 330 core

#define NUM_MAX_PLIGHTS 2
#define NUM_MAX_SLIGHTS 2

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};  

struct PLight {
    vec3 position;
    float c1;
    float c2;
    float c3;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;   
};

struct DLight {
    vec3 direction;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;   
};

struct SLight {
    vec3 position;
    vec3 direction;
    float minAperture;
    float maxAperture;
  
    float c1;
    float c2;
    float c3;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;   
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform DLight dlight;
uniform PLight plight[NUM_MAX_PLIGHTS];
uniform SLight slight[NUM_MAX_SLIGHTS];

vec3 DirectionalLight(DLight light, vec3 Normal, vec3 viewDirection);
vec3 PointLight(PLight light, vec3 Normal, vec3 viewDirection);
vec3 SpotLight(SLight light, vec3 Normal, vec3 viewDirection);

void main(){
	color = vec4(0);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 Norm = normalize(Normal);

	color += vec4(DirectionalLight(dlight, Norm, viewDir),1.0f);

	for(int i = 0; i<NUM_MAX_PLIGHTS;i++){
		color += vec4(PointLight(plight[i], Norm, viewDir),1.0f);
	}
	for(int i = 0; i<NUM_MAX_SLIGHTS;i++){
		color += vec4(SpotLight(slight[i], Norm, viewDir),1.0f);
	}
} 

vec3 DirectionalLight(DLight light, vec3 Normal, vec3 viewDirection){
	vec3 color;
	vec3 Lamb = light.ambient * vec3(texture(material.diffuse, TexCoords));

	vec3 L = normalize(-light.direction);
	float diff = max(dot(Normal,L),0.0f);
	vec3 Ldiff = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	vec3 R = normalize(reflect (light.direction,Normal));
	float spe = pow(max(dot(viewDirection,R),0.0f), material.shininess);
	vec3 Lspe = light.specular * spe * vec3(texture(material.specular, TexCoords));

	color = Lamb+Ldiff+Lspe;
	return color;
}

vec3 PointLight(PLight light, vec3 Normal, vec3 viewDirection){

	vec3 color;
	float ambientStrength = 0.5f;
	vec3 Lamb = ambientStrength * light.ambient * vec3(texture(material.diffuse, TexCoords));

	vec3 L = normalize(light.position-FragPos);
	float diff = max(dot(Normal,L),0.0f);
	vec3 Ldiff = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	vec3 R = reflect (-L,Normal);
	float spe = pow(max(dot(viewDirection,R),0.0f), material.shininess);
	vec3 Lspe = 0.5*light.specular * spe * vec3(texture(material.specular, TexCoords));

	float dist=length(light.position-FragPos);
	float fatt = 1/(light.c1+light.c2*dist+light.c3*(dist*dist));
	color = fatt*(Lamb+Ldiff+Lspe);
	return color;
}

vec3 SpotLight(SLight light, vec3 Normal, vec3 viewDirection){
	vec3 color = vec3(0.0f);

	vec3 L = normalize(light.position-FragPos);
	float Theta = dot(L,normalize(-light.direction));

	if(Theta>light.maxAperture){
		float ambientStrength = 0.1f;
		vec3 Lamb = ambientStrength * light.ambient * vec3(texture(material.diffuse, TexCoords));

		float diff = max(dot(Normal,L),0.0f);
		vec3 Ldiff = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

		vec3 R = reflect (-L,Normal);
		float spe = pow(max(dot(viewDirection,R),0.0f), material.shininess);
		vec3 Lspe = 0.5*light.specular * spe * vec3(texture(material.specular, TexCoords));

		float dist=length(light.position-FragPos);
		float fatt = 1/(light.c1+light.c2*dist+light.c3*(dist*dist));

		float Epsilon = light.minAperture-light.maxAperture;
		float Inten = clamp ((Theta - light.maxAperture ) /Epsilon,0,1);

		color = Inten*fatt*(Lamb+Ldiff+Lspe);
	}
	return color;
}