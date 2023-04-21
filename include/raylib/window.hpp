#pragma once

namespace raylib {
	class Window {
	public:
		Window() = default;

		Window(const librapid::Vec2i &size, const std::string &title = "RayLib");

		~Window();

		void init(const librapid::Vec2i &size = {800, 450}, const std::string &title = "RayLib");
		
		void close();
		
		LIBRAPID_NODISCARD bool isCursorOnScreen() const;
		LIBRAPID_NODISCARD bool isFullscreen() const;
		LIBRAPID_NODISCARD bool isHidden() const;
		LIBRAPID_NODISCARD bool isMinimized() const;
		LIBRAPID_NODISCARD bool isMaximized() const;
		LIBRAPID_NODISCARD bool isFocused() const;
		LIBRAPID_NODISCARD bool isResized() const;
		LIBRAPID_NODISCARD bool isState(unsigned int flag) const;
		
		Window &setState(unsigned int flag);
		Window &clearState(unsigned int flag);
		Window &clearBackground(const librapid::Vec4i &color = BLACK);
		Window &toggleFullscreen();
		Window &setFullscreen(bool fullscreen);
		Window &maximize();
		Window &minimize();
		Window &restore();
		
		Window &setIcon(const ::Image &image);
		Window &setTitle(const std::string &title);
		Window &setPosition(const librapid::Vec2i &pos);
		Window &setMonitor(int64_t monitor);
		Window &setMinSize(const librapid::Vec2i &size);
		Window &setSize(const librapid::Vec2i &size);
		Window &setOpacity(float opacity);
		Window &setTargetFPS(int64_t fps);

		LIBRAPID_NODISCARD std::string getClipboardText() const;
		Window &setClipboardText(const std::string &text);

		LIBRAPID_NODISCARD librapid::Vec2i getSize() const;
		LIBRAPID_NODISCARD librapid::Vec2i getPosition() const;
		LIBRAPID_NODISCARD int64_t getWidth() const;
		LIBRAPID_NODISCARD int64_t getHeight() const;
		LIBRAPID_NODISCARD int64_t getRenderWidth() const;
		LIBRAPID_NODISCARD int64_t getRenderHeight() const;
		LIBRAPID_NODISCARD librapid::Vec2i getScaleDPI() const;
		LIBRAPID_NODISCARD int64_t getMonitorCount() const;
		LIBRAPID_NODISCARD int64_t getFPS() const;
		LIBRAPID_NODISCARD int64_t getFrameTime() const;
		LIBRAPID_NODISCARD double getTime() const;
		LIBRAPID_NODISCARD bool isReady() const;
		LIBRAPID_NODISCARD bool shouldClose() const;
		LIBRAPID_NODISCARD void *getHandle() const;

		Window &beginDrawing();
		Window &endDrawing();

		Window &drawFPS(const librapid::Vec2i &pos);
		Window &showCursor();
		Window &hideCursor();
		Window &enableCursor();
		Window &disableCursor();
	};
}
