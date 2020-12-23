#shader vertex
#version 330 core

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
    );

//u_Projection u_Model * u_View *
void main()
{
   
    gl_Position = vec4(gridPlane[gl_VertexID].xyz, 1.0) * u_Model * u_View * u_Projection;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
