#include "Camera.h"


static double yaw = -90.0f;
static double pitch = 0.0f;
static bool firstMouse = true;
static double lastX = 640.0f;
static double lastY = 360.0f;

extern Camera cam;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;


	cam.processMouseInput(xoffset, yoffset);
}


Camera::Camera()
	:cam_View(glm::mat4(1.0f)), cam_Direction(glm::vec3(1.0f)), cam_Pos(glm::vec3(0.0f))
{

	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 3.0f);
	cam_Front = glm::normalize(cam_Pos - cameraTarget);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	cam_Right = glm::normalize(glm::cross(up, cam_Front));
	cam_Up = glm::cross(cam_Front, cam_Right);

	cam_View = glm::lookAt(cam_Pos, cam_Pos + cam_Front, cam_Up);

}

Camera::~Camera()
{

}

void Camera::Rotate(const float radius)
{
	double camX = sin(glfwGetTime()) * radius;
	double camZ = cos(glfwGetTime()) * radius;
	cam_View = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::UpdateCamView() {
	cam_View = glm::lookAt(cam_Pos, cam_Pos + cam_Front, cam_Up);
}

void Camera::processKeyInput(GLFWwindow* window)
{
	const float cameraSpeed = 0.1f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam_Pos += cameraSpeed * cam_Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam_Pos -= cameraSpeed * cam_Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam_Pos -= glm::normalize(glm::cross(cam_Front, cam_Up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam_Pos += glm::normalize(glm::cross(cam_Front, cam_Up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam_Pos += glm::vec3(0.0f, 0.5f, 0.0f) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cam_Pos -= glm::vec3(0.0f, 0.5f, 0.0f) * cameraSpeed;

}


void Camera::processMouseInput(double xoffset, double yoffset)
{

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	SetCamFront(glm::normalize(front));
}

void Camera::ProcessInput(GLFWwindow* window)
{
	processKeyInput(window);
	UpdateCamView();
}


