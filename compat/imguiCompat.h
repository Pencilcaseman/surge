#pragma once

#ifndef SURGE_IMGUI_COMPAT_NO_GLFW
#include <GLFW/glfw3.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

void imGuiInit(struct GLFWwindow *window);
void imGuiRender();

#if defined(__cplusplus)
}
#endif
