#include <surge/surge.hpp>

namespace surge {
	Window::Window(const librapid::Vec2i &size, const std::string &title) {
		::InitWindow(size.x(), size.y(), title.c_str());
	}

	Window::~Window() { close(); }

	void Window::close() { ::CloseWindow(); }

	bool Window::isCursorOnScreen() const { return ::IsCursorOnScreen(); }
	bool Window::isFullscreen() const { return ::IsWindowFullscreen(); }
	bool Window::isHidden() const { return ::IsWindowHidden(); }
	bool Window::isMinimized() const { return ::IsWindowMinimized(); }
	bool Window::isMaximized() const { return ::IsWindowMaximized(); }
	bool Window::isFocused() const { return ::IsWindowFocused(); }
	bool Window::isResized() const { return ::IsWindowResized(); }
	bool Window::isState(uint64_t flag) const {
		return ::IsWindowState(static_cast<unsigned int>(flag));
	}

	Window &Window::setFlag(uint64_t flag, bool state) {
		if (state)
			::SetWindowState(static_cast<unsigned int>(flag));
		else
			::ClearWindowState(static_cast<unsigned int>(flag));
		return *this;
	}

	Window &Window::clear(const Color &color) {
		auto [r, g, b, a] = color.rgba();
		::ClearBackground({r, g, b, a});
		return *this;
	}

	Window &Window::toggleFullscreen() {
		::ToggleFullscreen();
		return *this;
	}

	Window &Window::setFullscreen(bool fullscreen) {
		if (fullscreen ^ isFullscreen()) toggleFullscreen();
		return *this;
	}

	Window &Window::maximize() {
		::MaximizeWindow();
		return *this;
	}

	Window &Window::minimize() {
		::MinimizeWindow();
		return *this;
	}

	Window &Window::restore() {
		::RestoreWindow();
		return *this;
	}

	Window &Window::setIcon(const ::Image &image) {
		::SetWindowIcon(image);
		return *this;
	}

	Window &Window::setTitle(const std::string &title) {
		::SetWindowTitle(title.c_str());
		return *this;
	}

	Window &Window::setPosition(const librapid::Vec2i &pos) {
		::SetWindowPosition(pos.x(), pos.y());
		return *this;
	}

	Window &Window::setMonitor(int64_t monitor) {
		::SetWindowMonitor(static_cast<int>(monitor));
		return *this;
	}

	Window &Window::setMinSize(const librapid::Vec2i &size) {
		::SetWindowMinSize(size.x(), size.y());
		return *this;
	}

	Window &Window::setSize(const librapid::Vec2i &size) {
		::SetWindowSize(size.x(), size.y());
		return *this;
	}

	Window &Window::setOpacity(float opacity) {
		::SetWindowOpacity(opacity);
		return *this;
	}

	Window &Window::setTargetFPS(int64_t fps) {
		::SetTargetFPS(static_cast<int>(fps));
		return *this;
	}

	std::string Window::getClipboardText() const { return ::GetClipboardText(); }

	Window &Window::setClipboardText(const std::string &text) {
		::SetClipboardText(text.c_str());
		return *this;
	}

	librapid::Vec2i Window::getSize() const { return {getWidth(), getHeight()}; }
	int64_t Window::getWidth() const { return ::GetScreenWidth(); }
	int64_t Window::getHeight() const { return ::GetScreenHeight(); }
	int64_t Window::getRenderWidth() const { return ::GetRenderWidth(); }
	int64_t Window::getRenderHeight() const { return ::GetRenderHeight(); }

	librapid::Vec2i Window::getPosition() const {
		Vector2 ret = ::GetWindowPosition();
		return {ret.x, ret.y};
	}

	librapid::Vec2i Window::getMousePosition() const {
		Vector2 ret = ::GetMousePosition();
		return {ret.x, ret.y};
	}

	librapid::Vec2i Window::getScaleDPI() const {
		Vector2 ret = GetWindowScaleDPI();
		return {ret.x, ret.y};
	}

	int64_t Window::getMonitorCount() const { return ::GetMonitorCount(); }

	int64_t Window::getFPS() const { return ::GetFPS(); }

	float Window::getFrameTime() const { return ::GetFrameTime(); }

	double Window::getTime() const { return ::GetTime(); }

	int64_t Window::getFrameCount() const { return m_frameCount; }

	bool Window::isReady() const { return ::IsWindowReady(); }

	bool Window::shouldClose() const { return ::WindowShouldClose(); }

	void *Window::getHandle() const { return ::GetWindowHandle(); }

	Window &Window::beginDrawing() {
		::BeginDrawing();
		return *this;
	}

	Window &Window::endDrawing() {
		::EndDrawing();
		++m_frameCount;
		return *this;
	}

	Window &Window::drawFPS(const librapid::Vec2i &pos) {
		::DrawFPS(pos.x(), pos.y());
		return *this;
	}

	Window &Window::showCursor() {
		::ShowCursor();
		return *this;
	}

	Window &Window::hideCursor() {
		::HideCursor();
		return *this;
	}

	Window &Window::enableCursor() {
		::EnableCursor();
		return *this;
	}

	Window &Window::disableCursor() {
		::DisableCursor();
		return *this;
	}
} // namespace surge
