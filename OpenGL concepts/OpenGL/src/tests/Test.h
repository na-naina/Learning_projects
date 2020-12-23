#pragma once
#include "Renderer.h"
#include "ErrorHandler.h"
#include "imgui/imgui.h"
#include <functional>
#include "Camera.h"

namespace tst {


	class Test{
	public:
		Test() {};
		virtual ~Test() {};

		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}

	};


	class TestList : public Test
	{
	public:
		TestList(Test*& currentTest);

		
		void OnImguiRender() override;
		
		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_TestList.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_TestList;


	};


}