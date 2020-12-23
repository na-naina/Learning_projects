

#include "Camera.h"
#include "ErrorHandler.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestPhongLight.h"
#include "tests/FunnyCube.h"
#include "tests/CompleteBasicLight.h"
#include "tests/Loading_model.h"
#include "tests/DepthFunc.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "Timer.h"



Camera cam;
GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


int main(void)
{
   
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 720, "Testing", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!!" << std::endl;
    
    std::cout << glGetString(GL_VERSION) << std::endl;

   
    glfwSetCursorPosCallback(window,  mouse_callback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

    Renderer rendrr;
    
    

    tst::Test* currtst = nullptr;
    tst::TestList* menu = new tst::TestList(currtst);
    currtst = new tst::DepthFunc;

    menu->RegisterTest<tst::TestClearColor>("Clear Color");
    menu->RegisterTest<tst::TestPhongLight>("Phong light model");
    menu->RegisterTest<tst::FunnyCube>("Funny cube");
    menu->RegisterTest<tst::CompleteBasicLight>("LightB");
    menu->RegisterTest<tst::Loading_model>("Model loading");
    menu->RegisterTest<tst::DepthFunc>("Buffers test");

    while (!glfwWindowShouldClose(window)) {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        rendrr.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame(); 
        ImGui::NewFrame();
        if (currtst)
        {
            currtst->OnUpdate(0.0f);
            currtst->OnRender();
            ImGui::Begin("Test");
            if (currtst != menu && ImGui::Button("<-"))
            {
                
                delete currtst;
                currtst = menu;
            }
            currtst->OnImguiRender();
            ImGui::End();
        }
        
		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
    }
 
 	ImGui_ImplOpenGL3_Shutdown();
 	ImGui_ImplGlfw_Shutdown();
 	ImGui::DestroyContext();
 
     glfwTerminate();


    return 0;
}