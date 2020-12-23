#include "TestClearColor.h"


tst::TestClearColor::TestClearColor()
	: m_ClearColor {0.3f, 0.4f, 0.5f, 1.0f}
{
	
}

tst::TestClearColor::~TestClearColor()
{

}

void tst::TestClearColor::OnUpdate(float dt)
{

	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
}

void tst::TestClearColor::OnRender()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void tst::TestClearColor::OnImguiRender()
{
	ImGui::ColorEdit4("Clear color", m_ClearColor);
}
