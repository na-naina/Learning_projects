#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0f);
	v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec3 u_Color;
uniform sampler2D u_Texture;


float near = 0.1;
float far = 5.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; 
	return (2.0 * near * far) / (far + near - z * (far - near));
}


void main()
{

	float depth = LinearizeDepth(gl_FragCoord.z) / far;

	color = (vec4(u_Color, 1) + texture(u_Texture, v_TexCoord)) * 0.5;
	color = vec4(vec3(depth), 1.0);
};