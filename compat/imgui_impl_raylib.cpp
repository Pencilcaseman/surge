#include "imgui_impl_raylib.h"
#include <raylib.h>
#include <rlgl.h>
#include <memory>

static double g_Time	  = 0.0;
static bool g_UnloadAtlas = false;
static int g_AtlasTexID	  = 0;

static const char *ImGui_ImplRaylib_GetClipboardText(void *) { return RL_GetClipboardText(); }

static void ImGui_ImplRaylib_SetClipboardText(void *, const char *text) {
	RL_SetClipboardText(text);
}

bool ImGui_ImplRaylib_Init() {
	ImGuiIO &io = ImGui::GetIO();

	io.BackendPlatformName = "imgui_impl_raylib";

	io.KeyMap[ImGuiKey_Tab]			= RL_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow]	= RL_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow]	= RL_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow]		= RL_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow]	= RL_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp]		= RL_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_PageDown]	= RL_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_Home]		= RL_KEY_HOME;
	io.KeyMap[ImGuiKey_End]			= RL_KEY_END;
	io.KeyMap[ImGuiKey_Insert]		= RL_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete]		= RL_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace]	= RL_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space]		= RL_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter]		= RL_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape]		= RL_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = RL_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A]			= RL_KEY_A;
	io.KeyMap[ImGuiKey_C]			= RL_KEY_C;
	io.KeyMap[ImGuiKey_V]			= RL_KEY_V;
	io.KeyMap[ImGuiKey_X]			= RL_KEY_X;
	io.KeyMap[ImGuiKey_Y]			= RL_KEY_Y;
	io.KeyMap[ImGuiKey_Z]			= RL_KEY_Z;

	io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

	io.SetClipboardTextFn = ImGui_ImplRaylib_SetClipboardText;
	io.GetClipboardTextFn = ImGui_ImplRaylib_GetClipboardText;
	io.ClipboardUserData  = NULL;

#ifdef AUTO_FONTATLAS
	ImGui_ImplRaylib_LoadDefaultFontAtlas();
#endif

	return true;
}

void ImGui_ImplRaylib_Shutdown() {
	if (g_UnloadAtlas) {
		ImGuiIO &io = ImGui::GetIO();
		io.Fonts->ClearTexData();
	}
	g_Time = 0.0;
}

static void ImGui_ImplRaylib_UpdateMousePosAndButtons() {
	ImGuiIO &io = ImGui::GetIO();

	// Set OS mouse position if requested (rarely used, only when
	// ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
	if (io.WantSetMousePos)
		RL_SetMousePosition(io.MousePos.x, io.MousePos.y);
	else
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

	io.MouseDown[0] = RL_IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	io.MouseDown[1] = RL_IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
	io.MouseDown[2] = RL_IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);

	if (!RL_IsWindowMinimized()) io.MousePos = ImVec2(RL_GetMouseX(), RL_GetMouseY());
}

static void ImGui_ImplRaylib_UpdateMouseCursor() {
	ImGuiIO &io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) return;

	ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
	if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None) {
		// Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
		RL_HideCursor();
	} else {
		// Show OS mouse cursor
		RL_ShowCursor();
	}
}

void ImGui_ImplRaylib_NewFrame() {
	ImGuiIO &io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)RL_GetScreenWidth(), (float)RL_GetScreenHeight());

	double current_time = RL_GetTime();
	io.DeltaTime		= g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
	g_Time				= current_time;

	io.KeyCtrl	= RL_IsKeyDown(RL_KEY_RIGHT_CONTROL) || RL_IsKeyDown(RL_KEY_LEFT_CONTROL);
	io.KeyShift = RL_IsKeyDown(RL_KEY_RIGHT_SHIFT) || RL_IsKeyDown(RL_KEY_LEFT_SHIFT);
	io.KeyAlt	= RL_IsKeyDown(RL_KEY_RIGHT_ALT) || RL_IsKeyDown(RL_KEY_LEFT_ALT);
	io.KeySuper = RL_IsKeyDown(RL_KEY_RIGHT_SUPER) || RL_IsKeyDown(RL_KEY_LEFT_SUPER);

	ImGui_ImplRaylib_UpdateMousePosAndButtons();
	ImGui_ImplRaylib_UpdateMouseCursor();

	if (RL_GetMouseWheelMove() > 0)
		io.MouseWheel += 1;
	else if (RL_GetMouseWheelMove() < 0)
		io.MouseWheel -= 1;
}

#define FOR_ALL_KEYS(X)                                                                            \
	X(RL_KEY_APOSTROPHE);                                                                          \
	X(RL_KEY_COMMA);                                                                               \
	X(RL_KEY_MINUS);                                                                               \
	X(RL_KEY_PERIOD);                                                                              \
	X(RL_KEY_SLASH);                                                                               \
	X(RL_KEY_ZERO);                                                                                \
	X(RL_KEY_ONE);                                                                                 \
	X(RL_KEY_TWO);                                                                                 \
	X(RL_KEY_THREE);                                                                               \
	X(RL_KEY_FOUR);                                                                                \
	X(RL_KEY_FIVE);                                                                                \
	X(RL_KEY_SIX);                                                                                 \
	X(RL_KEY_SEVEN);                                                                               \
	X(RL_KEY_EIGHT);                                                                               \
	X(RL_KEY_NINE);                                                                                \
	X(RL_KEY_SEMICOLON);                                                                           \
	X(RL_KEY_EQUAL);                                                                               \
	X(RL_KEY_A);                                                                                   \
	X(RL_KEY_B);                                                                                   \
	X(RL_KEY_C);                                                                                   \
	X(RL_KEY_D);                                                                                   \
	X(RL_KEY_E);                                                                                   \
	X(RL_KEY_F);                                                                                   \
	X(RL_KEY_G);                                                                                   \
	X(RL_KEY_H);                                                                                   \
	X(RL_KEY_I);                                                                                   \
	X(RL_KEY_J);                                                                                   \
	X(RL_KEY_K);                                                                                   \
	X(RL_KEY_L);                                                                                   \
	X(RL_KEY_M);                                                                                   \
	X(RL_KEY_N);                                                                                   \
	X(RL_KEY_O);                                                                                   \
	X(RL_KEY_P);                                                                                   \
	X(RL_KEY_Q);                                                                                   \
	X(RL_KEY_R);                                                                                   \
	X(RL_KEY_S);                                                                                   \
	X(RL_KEY_T);                                                                                   \
	X(RL_KEY_U);                                                                                   \
	X(RL_KEY_V);                                                                                   \
	X(RL_KEY_W);                                                                                   \
	X(RL_KEY_X);                                                                                   \
	X(RL_KEY_Y);                                                                                   \
	X(RL_KEY_Z);                                                                                   \
	X(RL_KEY_SPACE);                                                                               \
	X(RL_KEY_ESCAPE);                                                                              \
	X(RL_KEY_ENTER);                                                                               \
	X(RL_KEY_TAB);                                                                                 \
	X(RL_KEY_BACKSPACE);                                                                           \
	X(RL_KEY_INSERT);                                                                              \
	X(RL_KEY_DELETE);                                                                              \
	X(RL_KEY_RIGHT);                                                                               \
	X(RL_KEY_LEFT);                                                                                \
	X(RL_KEY_DOWN);                                                                                \
	X(RL_KEY_UP);                                                                                  \
	X(RL_KEY_PAGE_UP);                                                                             \
	X(RL_KEY_PAGE_DOWN);                                                                           \
	X(RL_KEY_HOME);                                                                                \
	X(RL_KEY_END);                                                                                 \
	X(RL_KEY_CAPS_LOCK);                                                                           \
	X(RL_KEY_SCROLL_LOCK);                                                                         \
	X(RL_KEY_NUM_LOCK);                                                                            \
	X(RL_KEY_PRINT_SCREEN);                                                                        \
	X(RL_KEY_PAUSE);                                                                               \
	X(RL_KEY_F1);                                                                                  \
	X(RL_KEY_F2);                                                                                  \
	X(RL_KEY_F3);                                                                                  \
	X(RL_KEY_F4);                                                                                  \
	X(RL_KEY_F5);                                                                                  \
	X(RL_KEY_F6);                                                                                  \
	X(RL_KEY_F7);                                                                                  \
	X(RL_KEY_F8);                                                                                  \
	X(RL_KEY_F9);                                                                                  \
	X(RL_KEY_F10);                                                                                 \
	X(RL_KEY_F11);                                                                                 \
	X(RL_KEY_F12);                                                                                 \
	X(RL_KEY_LEFT_SHIFT);                                                                          \
	X(RL_KEY_LEFT_CONTROL);                                                                        \
	X(RL_KEY_LEFT_ALT);                                                                            \
	X(RL_KEY_LEFT_SUPER);                                                                          \
	X(RL_KEY_RIGHT_SHIFT);                                                                         \
	X(RL_KEY_RIGHT_CONTROL);                                                                       \
	X(RL_KEY_RIGHT_ALT);                                                                           \
	X(RL_KEY_RIGHT_SUPER);                                                                         \
	X(RL_KEY_KB_MENU);                                                                             \
	X(RL_KEY_LEFT_BRACKET);                                                                        \
	X(RL_KEY_BACKSLASH);                                                                           \
	X(RL_KEY_RIGHT_BRACKET);                                                                       \
	X(RL_KEY_GRAVE);                                                                               \
	X(RL_KEY_KP_0);                                                                                \
	X(RL_KEY_KP_1);                                                                                \
	X(RL_KEY_KP_2);                                                                                \
	X(RL_KEY_KP_3);                                                                                \
	X(RL_KEY_KP_4);                                                                                \
	X(RL_KEY_KP_5);                                                                                \
	X(RL_KEY_KP_6);                                                                                \
	X(RL_KEY_KP_7);                                                                                \
	X(RL_KEY_KP_8);                                                                                \
	X(RL_KEY_KP_9);                                                                                \
	X(RL_KEY_KP_DECIMAL);                                                                          \
	X(RL_KEY_KP_DIVIDE);                                                                           \
	X(RL_KEY_KP_MULTIPLY);                                                                         \
	X(RL_KEY_KP_SUBTRACT);                                                                         \
	X(RL_KEY_KP_ADD);                                                                              \
	X(RL_KEY_KP_ENTER);                                                                            \
	X(RL_KEY_KP_EQUAL);

#define SET_KEY_DOWN(KEY) io.KeysDown[KEY] = RL_IsKeyDown(KEY)

bool ImGui_ImplRaylib_ProcessEvent() {
	ImGuiIO &io = ImGui::GetIO();

	FOR_ALL_KEYS(SET_KEY_DOWN);

	// Uncomment the three lines below if using raylib earlier than version 3.
	// if (GetKeyPressed() != -1)
	//{
#ifdef ENABLE_SCODETOUTF8
	int length; //  Length was only ever created to be passed to CodepointToUtf8(), since it doesn't
				//  check for nullptrs.
	io.AddInputCharactersUTF8(RL_CodepointToUTF8(RL_GetCharPressed(), &length));
	(void)length; //  Silencing the compiler warnings.
#else
	io.AddInputCharacter(GetKeyPressed());
#endif
	//}

	return true;
}

#ifdef COMPATIBILITY_MODE
void ImGui_ImplRaylib_LoadDefaultFontAtlas() {
	if (!g_UnloadAtlas) {
		ImGuiIO &io			  = ImGui::GetIO();
		unsigned char *pixels = NULL;
		int width, height, bpp;
		Image image;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bpp);

		unsigned int size = GetPixelDataSize(width, height, 7);
		image.data		  = malloc(size);
		memcpy(image.data, pixels, size);
		image.width		= width;
		image.height	= height;
		image.mipmaps	= 1;
		image.format	= UNCOMPRESSED_R8G8B8A8;
		Texture2D tex	= LoadTextureFromImage(image);
		g_AtlasTexID	= tex.id;
		io.Fonts->TexID = (void *)&g_AtlasTexID;
		free(pixels);
		free(image.data);
		g_UnloadAtlas = true;
	}
};

//  Code originally provided by WEREMSOFT.
void ImGui_ImplRaylib_Render(ImDrawData *draw_data) {
	auto DrawTriangleVertex = [](ImDrawVert idx_vert) -> void {
		Color *c = (Color *)&idx_vert.col;
		rlColor4ub(c->r, c->g, c->b, c->a);
		rlTexCoord2f(idx_vert.uv.x, idx_vert.uv.y);
		rlVertex2f(idx_vert.pos.x, idx_vert.pos.y);
	};

	rlDisableBackfaceCulling();
	for (int n = 0; n < draw_data->CmdListsCount; n++) {
		const ImDrawList *cmd_list = draw_data->CmdLists[n];
		const ImDrawVert *vtx_buffer =
		  cmd_list->VtxBuffer.Data; // vertex buffer generated by Dear ImGui
		const ImDrawIdx *idx_buffer =
		  cmd_list->IdxBuffer.Data; // index buffer generated by Dear ImGui
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
			const ImDrawCmd *pcmd =
			  &(cmd_list->CmdBuffer.Data)[cmd_i]; // cmd_list->CmdBuffer->data[cmd_i];
			if (pcmd->UserCallback) {
				pcmd->UserCallback(cmd_list, pcmd);
			} else {
				ImVec2 pos = draw_data->DisplayPos;
				int rectX  = (int)(pcmd->ClipRect.x - pos.x);
				int rectY  = (int)(pcmd->ClipRect.y - pos.y);
				int rectW  = (int)(pcmd->ClipRect.z - rectX);
				int rectH  = (int)(pcmd->ClipRect.w - rectY);
				BeginScissorMode(rectX, rectY, rectW, rectH);
				{
					unsigned int *ti = (unsigned int *)pcmd->TextureId;
					for (unsigned int i = 0; i <= (pcmd->ElemCount - 3); i += 3) {
						rlPushMatrix();
						rlBegin(RL_TRIANGLES);
						rlEnableTexture(*ti);

						ImDrawIdx index;
						ImDrawVert vertex;

						index  = idx_buffer[i];
						vertex = vtx_buffer[index];
						DrawTriangleVertex(vertex);

						index  = idx_buffer[i + 2];
						vertex = vtx_buffer[index];
						DrawTriangleVertex(vertex);

						index  = idx_buffer[i + 1];
						vertex = vtx_buffer[index];
						DrawTriangleVertex(vertex);
						rlDisableTexture();
						rlEnd();
						rlPopMatrix();
					}
				}
			}
			idx_buffer += pcmd->ElemCount;
		}
	}
	EndScissorMode();
	rlEnableBackfaceCulling();
}
#endif
