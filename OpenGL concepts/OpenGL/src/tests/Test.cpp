#include "Test.h"

namespace tst {





	TestList::TestList(Test*& currentTest)
		: m_CurrentTest(currentTest)
	{
	}

	

	void TestList::OnImguiRender()
	{
		for (auto& test : m_TestList)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}

}