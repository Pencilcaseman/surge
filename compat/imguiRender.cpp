#include <imgui.h>
#include <imgui_impl_raylib.h>
#include <imgui_impl_opengl3.h>

#include "imguiRender.h"

#if defined(__cplusplus)
extern "C" {
#endif

void imGuiRender() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#if defined(__cplusplus)
}
#endif
