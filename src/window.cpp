#include <surge/surge.hpp>
#include <raylibCoreData.h>
#include <GLFW/glfw3.h>

namespace surge {
	Window window;

	namespace detail {
		static int64_t windowsCreated = 0;
		static size_t frameCount	  = 0;
	} // namespace detail

	Window::Window() {
		// detail::windowsCreated++;
		// LIBRAPID_ASSERT(detail::windowsCreated == 1,
		// 				"Only one window can be created at a time!\nIf you are trying to get/set a "
		// 				"property of the window, use the surge::window variable.");

		// window = *this;
	}

	Window::Window(const librapid::Vec2i &size, const std::string &title,
				   const std::initializer_list<ConfigFlag> &flags) :
			m_initialSize(size),
			m_initialTitle(title) {
		detail::windowsCreated++;
		LIBRAPID_ASSERT(detail::windowsCreated == 1,
						"Only one window can be created at a time!\nIf you are trying to get/set a "
						"property of the window, use the surge::window variable.");

		for (const auto &flag : flags) { RL_SetConfigFlags(static_cast<uint32_t>(flag)); }

		init();
		window = *this;
	}

	Window &Window::init() {
		::RL_InitWindow(m_initialSize.x(), m_initialSize.y(), m_initialTitle.c_str());

		// Cause a new frame to be drawn (initializes the frame size)
		beginDrawing(false);
		endDrawing(false);

		return *this;
	}

	void Window::close() { ::RL_CloseWindow(); }

	bool Window::isCursorOnScreen() const { return ::RL_IsCursorOnScreen(); }
	bool Window::isFullscreen() const { return ::RL_IsWindowFullscreen(); }
	bool Window::isHidden() const { return ::RL_IsWindowHidden(); }
	bool Window::isMinimized() const { return ::RL_IsWindowMinimized(); }
	bool Window::isMaximized() const { return ::RL_IsWindowMaximized(); }
	bool Window::isFocused() const { return ::RL_IsWindowFocused(); }
	bool Window::isResized() const { return ::RL_IsWindowResized(); }

	bool Window::isState(StateFlag flag) const {
		return ::RL_IsWindowState(static_cast<unsigned int>(flag));
	}

	Window &Window::setFlag(StateFlag flag, bool state) {
		if (state) {
			::RL_SetWindowState(static_cast<unsigned int>(flag));
		} else {
			::RL_ClearWindowState(static_cast<unsigned int>(flag));
		}
		return *this;
	}

	Window &Window::clear(const Color &color) {
		auto [r, g, b, a] = color.rgba();
		::RL_ClearBackground({r, g, b, static_cast<uint8_t>(a * 255)});
		return *this;
	}

	Window &Window::toggleFullscreen() {
		::RL_ToggleFullscreen();
		return *this;
	}

	Window &Window::setFullscreen(bool fullscreen) {
		if (fullscreen ^ isFullscreen()) toggleFullscreen();
		return *this;
	}

	Window &Window::maximize() {
		::RL_MaximizeWindow();
		return *this;
	}

	Window &Window::minimize() {
		::RL_MinimizeWindow();
		return *this;
	}

	Window &Window::restore() {
		::RL_RestoreWindow();
		return *this;
	}

	Window &Window::setIcon(const ::RlImage &image) {
		::RL_SetWindowIcon(image);
		return *this;
	}

	Window &Window::setTitle(const std::string &title) {
		::RL_SetWindowTitle(title.c_str());
		return *this;
	}

	Window &Window::setPosition(const librapid::Vec2i &pos) {
		::RL_SetWindowPosition(pos.x(), pos.y());
		return *this;
	}

	Window &Window::setMonitor(int64_t monitor) {
		::RL_SetWindowMonitor(static_cast<int>(monitor));
		return *this;
	}

	Window &Window::setMinSize(const librapid::Vec2i &size) {
		::RL_SetWindowMinSize(size.x(), size.y());
		return *this;
	}

	Window &Window::setSize(const librapid::Vec2i &size) {
		::RL_SetWindowSize(size.x(), size.y());
		return *this;
	}

	Window &Window::setOpacity(float opacity) {
		::RL_SetWindowOpacity(opacity);
		return *this;
	}

	Window &Window::setTargetFPS(int64_t fps) {
		::RL_SetTargetFPS(static_cast<int>(fps));
		return *this;
	}

	std::string Window::getClipboardText() const { return ::RL_GetClipboardText(); }

	Window &Window::setClipboardText(const std::string &text) {
		::RL_SetClipboardText(text.c_str());
		return *this;
	}

	librapid::Vec2i Window::size() const { return {width(), height()}; }
	int64_t Window::width() const { return ::RL_GetScreenWidth(); }
	int64_t Window::height() const { return ::RL_GetScreenHeight(); }
	int64_t Window::renderWidth() const { return ::RL_GetRenderWidth(); }
	int64_t Window::renderHeight() const { return ::RL_GetRenderHeight(); }

	librapid::Vec2i Window::position() const {
		::RlVector2 ret = ::RL_GetWindowPosition();
		return {ret.x, ret.y};
	}

	//	librapid::Vec2i Window::getMousePosition() const {
	//		Vector2 ret = ::GetMousePosition();
	//		return {ret.x, ret.y};
	//	}
	//
	//	librapid::Vec2i Window::getMouseScreenPosition() const {
	//		Vector2 ret = ::GetMousePosition();
	//		return librapid::Vec2i {ret.x, ret.y} + getPosition();
	//	}

	librapid::Vec2i Window::scaleDPI() const {
		::RlVector2 ret = ::RL_GetWindowScaleDPI();
		return {ret.x, ret.y};
	}

	int64_t Window::monitorCount() const { return ::RL_GetMonitorCount(); }

	int64_t Window::fps() const { return ::RL_GetFPS(); }

	float Window::frameTime() const { return ::RL_GetFrameTime(); }

	double Window::time() const { return ::RL_GetTime(); }

	int64_t Window::frameCount() const { return detail::frameCount; }

	bool Window::isReady() const { return ::RL_IsWindowReady(); }

	bool Window::shouldClose() const { return ::RL_WindowShouldClose(); }

	void *Window::getHandle() const { return ::RL_GetWindowHandle(); }

	Window &Window::beginDrawing(bool withImGui) {
		LIBRAPID_ASSERT(
		  isReady(),
		  "Window is not ready to be drawn on. Make sure you have called Window::init()");

		::RL_BeginDrawing();

		// ImGui_ImplOpenGL3_NewFrame();
		// ImGui_ImplRaylib_NewFrame();

		if (withImGui) {
			glfwMakeContextCurrent(surgeGetGLFWwindow());
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		return *this;
	}

	Window &Window::endDrawing(bool withImGui) {
		// Now handled in my fork of RayLib
		// ImGui::Render();
		// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		::RL_EndDrawing(withImGui);

		if (withImGui) {
			loadCachedImGuiFonts();
			updateUncachedFont();
		}

		++detail::frameCount;
		return *this;
	}

	Window &Window::drawFPS(const librapid::Vec2i &pos) {
		::RL_DrawFPS(pos.x(), pos.y());
		return *this;
	}

	Window &Window::drawFrameTime(const librapid::Vec2i &pos) {
		static int64_t prevFrame = 0;
		static float frameTime	 = 0.0f;
		float newFrameTime		 = ::RL_GetFrameTime();

		if (this->frameCount() - prevFrame > 30 || newFrameTime > 0.05) {
			prevFrame = this->frameCount();
			frameTime = newFrameTime;
		}

		Color color = Color::lime;						 // Good FPS
		if (frameTime >= 16.666f) color = Color::yellow; // Average FPS
		if (frameTime >= 33.333f) color = Color::orange; // Bad FPS
		auto [r, g, b, a] = color.rgba();
		::RL_DrawText(
		  fmt::format("{:.3f}", librapid::formatTime<librapid::time::second>(frameTime)).c_str(),
		  pos.x(),
		  pos.y(),
		  20,
		  {r, g, b, static_cast<uint8_t>(a * 255)});

		return *this;
	}

	Window &Window::drawTime(const librapid::Vec2i &pos) {
		auto [r, g, b, a] = Color::magenta.rgba();
		::RL_DrawText(
		  fmt::format("{}", librapid::formatTime<librapid::time::second>(time())).c_str(),
		  pos.x(),
		  pos.y(),
		  20,
		  {r, g, b, static_cast<uint8_t>(a * 255)});
		return *this;
	}

	Mouse &Window::mouse() { return m_mouse; }
	const Mouse &Window::mouse() const { return m_mouse; }

	// Keyboard &Window::keyboard() { return m_keyboard; }
	// const Keyboard &Window::keyboard() const { return m_keyboard; }
} // namespace surge
