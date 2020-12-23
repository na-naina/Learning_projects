#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 col;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0f);
	v_TexCoord = texCoord;
	v_Color = col;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_Face;
uniform sampler2D u_Dots;
//uniform vec3 u_Color;
// texture(u_Face, v_TexCoord) + texture(u_Dots, v_TexCoord) * 0.3 +
void main()
{
	color = v_Color + texture(u_Face, v_TexCoord);
	color = texture(u_Face, v_TexCoord);
};