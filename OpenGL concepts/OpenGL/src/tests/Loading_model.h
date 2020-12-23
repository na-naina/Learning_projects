#pragma once
#include "Test.h"
#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace tst {

	class Loading_model : public Test
	{
	public:

		Loading_model();
		~Loading_model();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImguiRender() override;
	private:

		float cubeVerticies[72] = {
-0.5f, -0.5f, -0.5f,                       //0                          
 0.5f, -0.5f, -0.5f,                       //1
 0.5f,  0.5f, -0.5f,                       //2
-0.5f,  0.5f, -0.5f,                       //3

-0.5f, -0.5f,  0.5f,                       //4
 0.5f, -0.5f,  0.5f,                       //5
 0.5f,  0.5f,  0.5f,                       //6
-0.5f,  0.5f,  0.5f,                       //7

-0.5f,  0.5f,  0.5f,                       //8
-0.5f,  0.5f, -0.5f,                       //9
-0.5f, -0.5f, -0.5f,                       //10
-0.5f, -0.5f,  0.5f,                       //11

 0.5f,  0.5f,  0.5f,                       //12
 0.5f,  0.5f, -0.5f,                       //13
 0.5f, -0.5f, -0.5f,                       //14
 0.5f, -0.5f,  0.5f,                       //15

-0.5f, -0.5f, -0.5f,                       //16
 0.5f, -0.5f, -0.5f,                       //17
 0.5f, -0.5f,  0.5f,                       //18
-0.5f, -0.5f,  0.5f,                       //19

-0.5f,  0.5f, -0.5f,                       //20
 0.5f,  0.5f, -0.5f,                       //21
 0.5f,  0.5f,  0.5f,                       //22
-0.5f,  0.5f,  0.5f                       //23
		};


		unsigned int cubeIndicies[36]{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};


		VertexArray va;
		VertexBuffer cubeVB;
		IndexBuffer cubeIB;
		VertexBufferLayout cubeLayout;

		Renderer rendrr;

		Model ourModel;
		Shader shader;
		Shader lightSource;
		glm::vec3 lightSourcePos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

}

