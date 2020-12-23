#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform vec4 u_PositionOffset;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
	gl_Position = u_Projection * u_View * u_Model * (position + u_PositionOffset);

};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_Light;

void main()
{
	color = vec4(u_Light, 1);
};