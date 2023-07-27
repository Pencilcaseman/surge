#include <imgui.h>
// #include <imgui_impl_raylib.h>
#include <imgui_impl_opengl3.h>
#include <cstdio>

#include "imguiCompat.h"

#if defined(__cplusplus)
extern "C" {
#endif

void imGuiInit(GLFWwindow *window) {

}

void imGuiRender() {
	auto &io = ImGui::GetIO();
	ImGui::Render();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		printf("Viewports enabled\n");
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#if defined(__cplusplus)
}
#endif
