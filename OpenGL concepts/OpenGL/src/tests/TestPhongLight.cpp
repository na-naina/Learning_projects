#include "TestPhongLight.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "Camera.h"

extern Camera cam;
extern GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

tst::TestPhongLight::TestPhongLight()
	: lightSourceShader("resources/shaders/LightSource.shader"), cubeVB(cubeVerticies, 8 * 36 * sizeof(float)), objectShader("resources/shaders/Object.shader"),
	cubeIB(cubeIndicies, 36), box("resources/textures/box.png"), boxSpecMap("resources/textures/box_spec.png")
{
	
	cubeLayout.Push<float>(3);
	cubeLayout.Push<float>(2);
	cubeLayout.Push<float>(3);

	va.AddBuffer(cubeVB, cubeLayout);

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	glEnable(GL_DEPTH_TEST);



	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	objectShader.Bind();
	box.Bind();
	boxSpecMap.Bind(1);


	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	objectShader.SetUniformMat4f("u_Projection", proj);
	objectShader.SetUniform4f("u_PositionOffset", 1.0f, 0.0f, 0.0f, 0.0f);
	objectShader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	objectShader.SetUniform1i("u_Material.diffuse", 0);
	objectShader.SetUniform1i("u_Material.specular", 1);
	objectShader.Unbind();



	lightSourceShader.Bind();

	lightSourceShader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	lightSourceShader.SetUniformMat4f("u_Projection", proj);

	lightSourceShader.Unbind();
	va.Unbind();

	cubeVB.Unbind();
	cubeIB.Unbind();

}

tst::TestPhongLight::~TestPhongLight()
{
	GLCall(glDisable(GL_BLEND));
	glDisable(GL_DEPTH_TEST);
}

void tst::TestPhongLight::OnUpdate(float dt)
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

void tst::TestPhongLight::OnRender()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.4f, 0.4f, 0.8f, 1.0f));

	//lightSourcePos = glm::rotate(lightSourcePos, 0.01f, glm::vec3(0.0f, 0.5f, 0.0f));
	
	//lightColor = glm::rotate(lightColor, 0.01f, glm::vec3(0.1f, 0.2f, 0.3f));

	objectShader.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = cam.GetView();
	model = glm::translate(model, glm::vec3(0.0f));
	
	if (rotationFlag) {
		model = glm::rotate(model, (float)glfwGetTime()/2, glm::vec3(1.0, 0.0, 1.0));
	}
	


	objectShader.SetUniformMat4f("u_View", view);
	objectShader.SetUniformMat4f("u_Model", model);
	objectShader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	objectShader.SetUniform3f("u_lightPos", lightSourcePos.x, lightSourcePos.y, lightSourcePos.z);
	objectShader.SetUniform3f("u_camPos", cam.GetPos());
	objectShader.SetUniform1f("u_Material.shininess", 128);

	rendrr.Draw(va, cubeIB, objectShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 1.0f, -3.0f));
	view = cam.GetView();
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));


	objectShader.SetUniformMat4f("u_View", view);
	objectShader.SetUniformMat4f("u_Model", model);
	objectShader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);
	objectShader.SetUniform3f("u_lightPos", lightSourcePos.x, lightSourcePos.y, lightSourcePos.z);
	objectShader.SetUniform3f("u_camPos", cam.GetPos());
	objectShader.SetUniform1f("u_Material.shininess", 256);

	rendrr.Draw(va, cubeIB, objectShader);


	lightSourceShader.Bind();

	model = glm::mat4(1.0f);
	model = glm::translate(model, lightSourcePos);
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.0, 1.0));
	lightSourceShader.SetUniformMat4f("u_View", view);
	lightSourceShader.SetUniformMat4f("u_Model", model);

	lightSourceShader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);

	rendrr.Draw(va, cubeIB, lightSourceShader);


}

void tst::TestPhongLight::OnImguiRender()
{
	ImGui::SliderFloat("Light.r", &lightColor.r, 0, 1);
	ImGui::SliderFloat("Light.g", &lightColor.g, 0, 1);
	ImGui::SliderFloat("Light.b", &lightColor.b, 0, 1);

	ImGui::SliderFloat("LightPos.x", &lightSourcePos.x, -10, 10);
	ImGui::SliderFloat("LightPos.y", &lightSourcePos.y, -10, 10);
	ImGui::SliderFloat("LightPos.z", &lightSourcePos.z, -10, 10);

	if (ImGui::Button("Rotate object"))
	{
		rotationFlag = (rotationFlag) ? 0 : 1;
	}
}
