#include "Loading_model.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "Camera.h"

extern Camera cam;
extern GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

tst::Loading_model::Loading_model()
	: shader("resources/shaders/model_loading.shader"), ourModel("resources/models/backpack/backpack.obj"), lightSource("resources/shaders/LightSource.shader"),
	cubeIB(cubeIndicies, 36), cubeVB(cubeVerticies, 3 * 24 * sizeof(float))
{
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	shader.Bind();
	
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	glEnable(GL_DEPTH_TEST);

	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	shader.SetUniformMat4f("u_Projection", proj);
	shader.SetUniform4f("u_PositionOffset", 1.0f, 0.0f, 0.0f, 0.0f);
	shader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	shader.Unbind();

	cubeLayout.Push<float>(3);

	va.AddBuffer(cubeVB, cubeLayout);

	lightSource.Bind();

	lightSource.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	lightSource.SetUniformMat4f("u_Projection", proj);

	lightSource.Unbind();
}

tst::Loading_model::~Loading_model()
{
	GLCall(glDisable(GL_BLEND));
	glDisable(GL_DEPTH_TEST);
}

void tst::Loading_model::OnUpdate(float dt)
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

void tst::Loading_model::OnRender()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280.0f / (float)720.0f, 0.1f, 100.0f);
	glm::mat4 view = cam.GetView();
	shader.SetUniformMat4f("u_Projection", projection);
	shader.SetUniformMat4f("u_View", view);


	shader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	shader.SetUniform3f("u_lightPos", lightSourcePos.x, lightSourcePos.y, lightSourcePos.z);
	shader.SetUniform3f("u_camPos", cam.GetPos());



	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	
	shader.SetUniformMat4f("u_Model", model);
	ourModel.Draw(shader);




	lightSource.Bind();

	model = glm::mat4(1.0f);
	model = glm::translate(model, lightSourcePos);
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.0, 1.0));
	lightSource.SetUniformMat4f("u_View", view);
	lightSource.SetUniformMat4f("u_Model", model);

	lightSource.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);

	rendrr.Draw(va, cubeIB, lightSource);

}

void tst::Loading_model::OnImguiRender()
{
	ImGui::SliderFloat("Light.r", &lightColor.r, 0, 1);
	ImGui::SliderFloat("Light.g", &lightColor.g, 0, 1);
	ImGui::SliderFloat("Light.b", &lightColor.b, 0, 1);

	ImGui::SliderFloat("LightPos.x", &lightSourcePos.x, -10, 10);
	ImGui::SliderFloat("LightPos.y", &lightSourcePos.y, -10, 10);
	ImGui::SliderFloat("LightPos.z", &lightSourcePos.z, -10, 10);
}
