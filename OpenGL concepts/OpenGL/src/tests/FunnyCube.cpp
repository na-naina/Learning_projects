#include "FunnyCube.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "Camera.h"

extern Camera cam;
extern GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

tst::FunnyCube::FunnyCube()
	: vb(cubeVerticies, sizeof(float) * 8 * 24), ib(cubeIndicies, 36), funnycube("resources/shaders/funnycube.shader"),
	dottedbg("resources/textures/funnycube/dotts.png"), faces("resources/textures/funnycube/wtf.png"), grid("resources/shaders/grid.shader")
{
	GLCall(glClearColor(0.2, 0.2, 0.2, 0.2));
	
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	glEnable(GL_DEPTH_TEST);


	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	faces.Bind();
	dottedbg.Bind(1);
	funnycube.Bind();
	funnycube.SetUniform1i("u_Face", 0);
	funnycube.SetUniform1i("u_Dots", 1);

	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	funnycube.SetUniformMat4f("u_Projection", proj);
	glm::mat4 model(1.0f);
	funnycube.SetUniformMat4f("u_Model", model);
	glm::mat4 view(1.0f);
	funnycube.SetUniformMat4f("u_View", view);
	funnycube.SetUniform3f("u_Color", glm::vec3(0.8f, 0.0f, 0.0f));

	grid.Bind();
	model = glm::translate(model, glm::vec3(0, 0, 1));
	grid.SetUniformMat4f("u_Model", model);
	grid.SetUniformMat4f("u_View", view);
	grid.SetUniformMat4f("u_Projection", proj);
	

}

tst::FunnyCube::~FunnyCube()
{
	GLCall(glDisable(GL_BLEND));
	glDisable(GL_DEPTH_TEST);
}

void tst::FunnyCube::OnUpdate(float dt)
{
	cam.ProcessInput(window);
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {});
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void tst::FunnyCube::OnRender()
{
	rend.Clear();
	glm::mat4 view = cam.GetView();
	funnycube.Bind();
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.2, 0.2, 0.2, 0.2));
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
	funnycube.SetUniformMat4f("u_Model", model);
	funnycube.SetUniformMat4f("u_View", model);
	rend.Draw(va, ib, funnycube);
	va.Bind();
	ib.Bind();
	grid.Bind();
	grid.SetUniformMat4f("u_View", view);
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void tst::FunnyCube::OnImguiRender()
{

}
