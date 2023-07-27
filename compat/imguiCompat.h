#pragma once

#include <GLFW/glfw3.h>

#if defined(__cplusplus)
extern "C" {
#endif

void imGuiInit(GLFWwindow *window);
void imGuiRender();

#if defined(__cplusplus)
}
#endif
