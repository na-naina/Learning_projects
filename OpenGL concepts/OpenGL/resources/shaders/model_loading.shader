#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1);

	v_FragPos = vec3(u_Model * vec4(position, 1));

	v_TexCoord = texCoord;
	v_Normal = mat3(transpose(inverse(u_Model))) * aNormal;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D u_Texture;
uniform vec3 u_Light;
uniform vec3 u_lightPos;
uniform vec3 u_camPos;



uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;



void main()
{
	vec3 ambient = vec3(texture(texture_diffuse1, v_TexCoord)) * u_Light * 0.05f;

	vec3 norm = normalize(texture(texture_normal1, v_TexCoord).rgb * 2.0 - 1.0);

	norm = normalize(v_Normal);

	vec3 lightDir = normalize(u_lightPos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(texture_diffuse1, v_TexCoord))) * u_Light;

	vec3 viewDir = normalize(u_camPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
	vec3 specular = vec3(texture(texture_specular1, v_TexCoord)) * spec * u_Light;

	color = vec4((specular + ambient + diffuse), 1);
};