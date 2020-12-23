#pragma once
#include "Test.h"



namespace tst {

	class DepthFunc : public Test
	{
	public:
		DepthFunc();
		~DepthFunc();


		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImguiRender() override;
	private:

		float cubeVerticies[120] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,              //0                          
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,              //1
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,              //2
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,              //3

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,              //4
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,              //5
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,              //6
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,              //7

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,              //8
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,              //9
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,              //10
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,              //11

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,              //12
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,              //13
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,              //14
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,              //15

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,              //16
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,              //17
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,              //18
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,              //19

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,              //20
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,              //21
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,              //22
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f             //23
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

		Texture tex;

		Shader CubeShader;
		Shader border;
		Renderer rendrr;
		bool rotationFlag = false;



	};


}
