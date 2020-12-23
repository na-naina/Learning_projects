#include "DepthFunc.h"


extern Camera cam;
extern GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


tst::DepthFunc::DepthFunc()
	: tex("resources/textures/noise.png"), CubeShader("resources/shaders/BuffersTest.shader"), cubeVB(cubeVerticies, sizeof(float) * 5 * 24), cubeIB(cubeIndicies, 36),
	border("resources/shaders/LightSource.shader")
{
	GLCall(glClearColor(0.2, 0.2, 0.2, 0.2));

	
	glEnable(GL_MULTISAMPLE);

	cubeLayout.Push<float>(3);
	cubeLayout.Push<float>(2);
	va.AddBuffer(cubeVB, cubeLayout);

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	CubeShader.Bind();

	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	CubeShader.SetUniformMat4f("u_Projection", proj);
	glm::mat4 model(1.0f);
	CubeShader.SetUniformMat4f("u_Model", model);
	glm::mat4 view(1.0f);
	CubeShader.SetUniformMat4f("u_View", view);
	CubeShader.SetUniform3f("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));
	tex.Bind();
	CubeShader.SetUniform1i("u_Texture", 0);
	border.Bind();
	border.SetUniformMat4f("u_Projection", proj);
}

tst::DepthFunc::~DepthFunc()
{
	GLCall(glDisable(GL_BLEND));
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_MULTISAMPLE);
}

void tst::DepthFunc::OnUpdate(float dt)
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
	if(cam.cam_Pos.y < 0)
		cam.cam_Pos.y = 0;
}

void tst::DepthFunc::OnRender()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	

	glm::mat4 view = cam.GetView();
	glm::mat4 model = glm::mat4(1);

	glStencilMask(0x00);

	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(0, -5.5, 0));
	model = glm::scale(model, glm::vec3(20, 10, 20));

	CubeShader.Bind();
	CubeShader.SetUniformMat4f("u_View", view);
	CubeShader.SetUniformMat4f("u_Model", model);
	rendrr.Draw(va, cubeIB, CubeShader);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	view = cam.GetView();
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(1, 0, 4));
	CubeShader.Bind();
	CubeShader.SetUniformMat4f("u_View", view);
	CubeShader.SetUniformMat4f("u_Model", model);
	rendrr.Draw(va, cubeIB, CubeShader);
	
	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(3, 0, 7));
	CubeShader.Bind();
	CubeShader.SetUniformMat4f("u_View", view);
	CubeShader.SetUniformMat4f("u_Model", model);
	rendrr.Draw(va, cubeIB, CubeShader);


	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);

	glDisable(GL_DEPTH_TEST);
	view = cam.GetView();
	model = glm::mat4(1);
	
	model = glm::translate(model, glm::vec3(1, 0, 4));
	model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1));

	border.Bind();
	border.SetUniformMat4f("u_View", view);
	border.SetUniformMat4f("u_Model", model);
	border.SetUniform3f("u_Light", glm::vec3(0.4, 0.4, 0.8));
	rendrr.Draw(va, cubeIB, border);


	model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(3, 0, 7));
	model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1));
	border.Bind();
	border.SetUniformMat4f("u_View", view);
	border.SetUniformMat4f("u_Model", model);
	border.SetUniform3f("u_Light", glm::vec3(0.4, 0.4, 0.8));
	rendrr.Draw(va, cubeIB, border);

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);


	

	
}

void tst::DepthFunc::OnImguiRender()
{

}
