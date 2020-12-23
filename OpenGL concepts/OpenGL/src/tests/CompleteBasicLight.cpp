#include "CompleteBasicLight.h"


#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "Camera.h"

extern Camera cam;
extern GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

tst::CompleteBasicLight::CompleteBasicLight()
	: lightSourceShader("resources/shaders/LightSource.shader"), cubeVB(cubeVerticies, 8 * 36 * sizeof(float)), objectShader("resources/shaders/basicLightCasters.shader"),
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

tst::CompleteBasicLight::~CompleteBasicLight()
{

}

void tst::CompleteBasicLight::OnUpdate(float dt)
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

void tst::CompleteBasicLight::OnRender()
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
		model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(1.0, 0.0, 1.0));
	}

	objectShader.SetUniformMat4f("u_Model", model);
	objectShader.SetUniformMat4f("u_View", view);


	objectShader.SetUniform3f("u_Light[0].position", lightSourcePos);
	objectShader.SetUniform3f("u_Light[0].direction", glm::vec3(1.0f, 0.0f, 1.0f));
	objectShader.SetUniform1f("u_Light[0].cutOff", 2.0f);
	objectShader.SetUniform1f("u_Light[0].outerCutOff", glm::cos(glm::radians(0.0f)));
	objectShader.SetUniform3f("u_ViewPos", cam.GetPos());


	objectShader.SetUniform3f("u_Light[0].ambient", lightColor.r * 0.1f, lightColor.g * 0.1f, lightColor.b * 0.1f);
	objectShader.SetUniform3f("u_Light[0].diffuse", lightColor.r * 0.8f, lightColor.g * 0.8f, lightColor.b * 0.8f);
	objectShader.SetUniform3f("u_Light[0].specular", 1.0f, 1.0f, 1.0f);
	objectShader.SetUniform1f("u_Light[0].constant", 1.0f);
	objectShader.SetUniform1f("u_Light[0].linear", 0.09f);
 	objectShader.SetUniform1f("u_Light[0].quadratic", 0.032f);
 
  	for (int i = 1; i < 3; i++)
  	{
  		objectShader.SetUniform3f("u_Light[" + std::to_string(i) + "].position", extraLightsPos[i - 1]);
  		objectShader.SetUniform3f("u_Light[" + std::to_string(i) + "].direction", glm::vec3(1.0f, 0.0f, 1.0f));
  		objectShader.SetUniform1f("u_Light[" + std::to_string(i) + "].cutOff", 2.0f);
  		objectShader.SetUniform1f("u_Light[" + std::to_string(i) + "].outerCutOff", glm::cos(glm::radians(0.0f)));
  		objectShader.SetUniform3f("u_ViewPos", cam.GetPos());
  
  
  		objectShader.SetUniform3f("u_Light[" + std::to_string(i) + "].ambient", 0.1f, 0.0f, 0.05f);
 		objectShader.SetUniform3f("u_Light[" + std::to_string(i) + "].diffuse", 0.8f, i % 2 ? 0.05 : 0.5 , 0.4f);
  		objectShader.SetUniform3f("u_Light[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
  		objectShader.SetUniform1f("u_Light[" + std::to_string(i) + "].constant", 1.0f);
  		objectShader.SetUniform1f("u_Light[" + std::to_string(i) + "].linear", i * 0.12f);
  		objectShader.SetUniform1f("u_Light[" + std::to_string(i) + "].quadratic", i * 0.04f);
  	}
 
	{
			objectShader.SetUniform3f("u_Light[3].position", glm::vec3(100.0f, 100.0f, 100.0f));
			objectShader.SetUniform3f("u_Light[3].direction", glm::vec3(-0.5f, -1.0f, 0.0f));
			objectShader.SetUniform1f("u_Light[3].cutOff", 2.0f);
			objectShader.SetUniform1f("u_Light[3].outerCutOff", glm::cos(glm::radians(0.0f)));
			objectShader.SetUniform3f("u_ViewPos", cam.GetPos());

			objectShader.SetUniform3f("u_Light[3].ambient", 0.05f, 0.05f, 0.05f);
			objectShader.SetUniform3f("u_Light[3].diffuse", 0.2f, 0.2f, 0.2f);
			objectShader.SetUniform3f("u_Light[3].specular", 1.0f, 1.0f, 1.0f);
			objectShader.SetUniform1f("u_Light[3].constant", 1.0f);
			objectShader.SetUniform1f("u_Light[3].linear", 0.00f);
			objectShader.SetUniform1f("u_Light[3].quadratic", 0.00f);
		
	}
 
 	{
 		objectShader.SetUniform3f("u_Light[4].position", cam.GetPos());
 		objectShader.SetUniform3f("u_Light[4].direction", cam.cam_Front);
 		objectShader.SetUniform1f("u_Light[4].cutOff", glm::cos(glm::radians(12.5f)));
 		objectShader.SetUniform1f("u_Light[4].outerCutOff", glm::cos(glm::radians(15.0f)));
 		objectShader.SetUniform3f("u_ViewPos", cam.GetPos());
 
 		objectShader.SetUniform3f("u_Light[4].ambient", 0.1f, 0.1f, 0.1f);
 		objectShader.SetUniform3f("u_Light[4].diffuse", 0.8f, 0.8f, 0.8f);
 		objectShader.SetUniform3f("u_Light[4].specular", 1.0f, 1.0f, 1.0f);
 		objectShader.SetUniform1f("u_Light[4].constant", 1.0f);
 		objectShader.SetUniform1f("u_Light[4].linear", 0.09f);
 		objectShader.SetUniform1f("u_Light[4].quadratic", 0.032f);
 
 	}

	objectShader.SetUniform1f("u_Material.shininess", 32.0f);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		objectShader.SetUniformMat4f("u_Model", model);

		rendrr.Draw(va, cubeIB, objectShader);
	}

	


	lightSourceShader.Bind();
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightSourcePos);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.0, 1.0));
		lightSourceShader.SetUniformMat4f("u_View", view);
		lightSourceShader.SetUniformMat4f("u_Model", model);

		lightSourceShader.SetUniform3f("u_Light", lightColor.r, lightColor.g, lightColor.b);

		rendrr.Draw(va, cubeIB, lightSourceShader);
	}
	for (int i = 0; i < 2; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, extraLightsPos[i]);
		model = glm::rotate(model, i * 20.0f, glm::vec3(1.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		lightSourceShader.SetUniformMat4f("u_Model", model);

		lightSourceShader.SetUniform3f("u_Light", 1.0f, i ? 0.7f : 0.08f, 1.0f);
		rendrr.Draw(va, cubeIB, lightSourceShader);
	}


}

void tst::CompleteBasicLight::OnImguiRender()
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