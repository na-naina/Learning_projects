#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 aNormal;


uniform vec4 u_PositionOffset;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * (position + u_PositionOffset);

	v_FragPos = vec3(u_Model * vec4(position + u_PositionOffset));

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

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material u_Material;

void main()
{
	vec3 ambient = vec3(texture(u_Material.diffuse, v_TexCoord)) * u_Light * 0.05f;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_lightPos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(u_Material.diffuse, v_TexCoord))) * u_Light;

	vec3 viewDir = normalize(u_camPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = vec3(texture(u_Material.specular, v_TexCoord)) * spec * u_Light;

	color = vec4((specular + ambient + diffuse), 1);
};