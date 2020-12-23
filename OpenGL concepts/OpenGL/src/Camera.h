#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"





class Camera
{
public:
	glm::vec3 cam_Pos;
	glm::vec3 cam_Front;
	glm::vec3 cam_Up;
	glm::vec3 cam_Right;
	glm::vec3 cam_Direction;
	glm::mat4 cam_View;

	void UpdateCamView();
	void processKeyInput(GLFWwindow* window);
	

public:
	Camera();
	~Camera();


	void Rotate(const float radius);
	void SetCamFront(glm::vec3 front) { cam_Front = front; };

	void processMouseInput(double xpos, double ypos);

	glm::mat4 GetView() { return cam_View; }
	glm::vec3 GetPos() { return cam_Pos; }

	void ProcessInput(GLFWwindow* window);

	
};

