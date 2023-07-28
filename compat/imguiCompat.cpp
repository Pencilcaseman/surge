#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <cstdio>

#define SURGE_IMGUI_COMPAT_NO_GLFW
#include "imguiCompat.h"

#if defined(__cplusplus)
extern "C" {
#endif

void imGuiInit(struct GLFWwindow *window) {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::GetStyle().WindowRounding			  = 0.0f;
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void imGuiRender() {
	auto &io = ImGui::GetIO();
	ImGui::Render();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();

	// Ensure the main viewport's data is rendered as well
	// if (ImGuiViewport *main_viewport = ImGui::GetMainViewport()) {
	// 	ImGui_ImplOpenGL3_RenderDrawData(main_viewport->DrawData);
	// }
	// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	for (const auto &viewport : ImGui::GetPlatformIO().Viewports) {
		glfwMakeContextCurrent((GLFWwindow *)viewport->PlatformHandle);
		ImGui_ImplOpenGL3_RenderDrawData(viewport->DrawData);
	}
}

#if defined(__cplusplus)
}
#endif
