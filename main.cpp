#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <Windows.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "TestClearColor.h"

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -2;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	window = glfwCreateWindow(960, 540, "Hello world!", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glewInit();

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR\n";

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		test::TestClearColor test;

		while (!glfwWindowShouldClose(window))
		{
			if (GetAsyncKeyState((unsigned short)VK_ESCAPE) & 0x8000)
			{
				std::cout << "Ok, bye!" << std::endl;
				return 1;
			}

			renderer.Clear();

			test.OnUpdate(0.0f);
			test.OnRender();

			ImGui_ImplGlfwGL3_NewFrame();
			test.OnImguiRender();
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			//Swap front and back buffers
			glfwSwapBuffers(window);

			//Poll for and process events
			glfwPollEvents();
		}
	}


	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}