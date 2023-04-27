#pragma once

namespace surge {
	class Window {
	public:
		Window() = default;

		/// \breif Create a new window
		///
		/// Construct a window with a specified size and title
		///
		/// \param size The size of the window (librapid::Vec2i)
		/// \param title The title of the window (std::string)
		explicit Window(const librapid::Vec2i &size, const std::string &title = "RayLib");

		Window &init();

		~Window();

		/// \brief Close the window
		void close();

		/// \brief Check if the cursor is on the current window
		/// \return True if the cursor is on the window, false otherwise
		LIBRAPID_NODISCARD bool isCursorOnScreen() const;

		/// \brief Check if the window is fullscreen
		/// \return True if the window is fullscreen, false otherwise
		LIBRAPID_NODISCARD bool isFullscreen() const;

		/// \brief Check if the window is hidden
		/// \return True if the window is hidden, false otherwise
		LIBRAPID_NODISCARD bool isHidden() const;

		/// \brief Check if the window is minimized
		/// \return True if the window is minimized, false otherwise
		LIBRAPID_NODISCARD bool isMinimized() const;

		/// \brief Check if the window is maximized
		/// \return True if the window is maximized, false otherwise
		LIBRAPID_NODISCARD bool isMaximized() const;

		/// \brief Check if the window is focused
		/// \return True if the window is focused, false otherwise
		LIBRAPID_NODISCARD bool isFocused() const;

		/// \brief Check if the window is resized
		/// \return True if the window is resized, false otherwise
		LIBRAPID_NODISCARD bool isResized() const;

		/// \brief Check if the window is in a specific state
		/// \param flag The state to check for (uint64_t)
		/// \return True if the window is in the specified state, false otherwise
		LIBRAPID_NODISCARD bool isState(uint64_t flag) const;

		/// \brief Set a flag for the window to a specific state
		/// Set a flag for the window
		/// \param flag The flag to set (uint64_t)
		/// \return A reference to the window
		Window &setFlag(WindowFlag flag, bool state = true);

		/// \brief Clear the window with a specified color
		/// \param color The color to clear the window with (surge::Color)
		/// \return A reference to the window
		Window &clear(const Color &color = Color::black);

		/// \brief Toggle fullscreen
		/// \return A reference to the window
		Window &toggleFullscreen();

		/// \brief Enable or disable fullscreen mode
		/// \param fullscreen True to enable fullscreen, false to disable it
		/// \return A reference to the window
		Window &setFullscreen(bool fullscreen);

		/// \brief Maximize the window
		/// \return A reference to the window
		Window &maximize();

		/// \brief Minimize the window
		/// \return A reference to the window
		Window &minimize();

		/// \brief Restore the window
		///
		/// Restore the window to its previous state
		/// \return A reference to the window
		Window &restore();

		/// \brief Set the window icon
		/// \param image The image to use as the icon (surge::Image)
		/// \return A reference to the window
		Window &setIcon(const ::Image &image);

		/// \brief Set the window title
		/// \param title The title to set (std::string)
		/// \return A reference to the window
		Window &setTitle(const std::string &title);

		/// \brief Set the position of the window on the screen
		/// \param pos The position to set (librapid::Vec2i)
		/// \return A reference to the window
		Window &setPosition(const librapid::Vec2i &pos);

		/// \brief Set which monitor the window is on
		/// \param monitor The monitor to set (int64_t)
		/// \return A reference to the window
		Window &setMonitor(int64_t monitor);

		/// \brief Set the minimum size of the window
		/// \param size The minimum size to set (librapid::Vec2i)
		/// \return A reference to the window
		Window &setMinSize(const librapid::Vec2i &size);

		/// \brief Set the size of the window
		/// \param size The size to set (librapid::Vec2i)
		Window &setSize(const librapid::Vec2i &size);

		/// \brief Set the opacity of the window
		/// \param opacity The opacity to set (float)
		/// \return A reference to the window
		Window &setOpacity(float opacity);

		/// \brief Set the target FPS
		/// \param fps The target FPS to set (int64_t)
		/// \return A reference to the window
		Window &setTargetFPS(int64_t fps);

		/// \breif Get the text currently on the clipboard
		/// \return The text on the clipboard (std::string)
		LIBRAPID_NODISCARD std::string getClipboardText() const;

		/// \brief Set the text on the clipboard
		/// \param text The text to set (std::string)
		/// \return A reference to the window
		Window &setClipboardText(const std::string &text);

		/// \brief Get the size of the window in pixels
		/// \return The size of the window (librapid::Vec2i)
		LIBRAPID_NODISCARD librapid::Vec2i getSize() const;

		/// \brief Get the width of the window in pixels
		/// \return The width of the window (int64_t)
		LIBRAPID_NODISCARD int64_t getWidth() const;

		/// \brief Get the height of the window in pixels
		/// \return The height of the window (int64_t)
		LIBRAPID_NODISCARD int64_t getHeight() const;

		/// \brief Get the width of the window, taking into account the DPI scale
		/// \return The width of the window (int64_t)
		/// \see getScaleDPI()
		LIBRAPID_NODISCARD int64_t getRenderWidth() const;

		/// \brief Get the height of the window, taking into account the DPI scale
		/// \return The height of the window (int64_t)
		/// \see getScaleDPI()
		LIBRAPID_NODISCARD int64_t getRenderHeight() const;

		/// \brief Get the current position of the window on the screen in pixels
		/// \return The position of the window (librapid::Vec2i)
		LIBRAPID_NODISCARD librapid::Vec2i getPosition() const;

		//		/// \brief Get the current position of the mouse relative to the window in pixels
		//		/// \return The position of the mouse (librapid::Vec2i)
		//		LIBRAPID_NODISCARD librapid::Vec2i getMousePosition() const;
		//
		//		/// \brief Get the current position of the mouse relative to the screen in pixels
		//		/// \return The position of the mouse (librapid::Vec2i)
		//		LIBRAPID_NODISCARD librapid::Vec2i getMouseScreenPosition() const;

		/// \brief Get the scale DPI of the window
		/// \return The scale DPI of the window (librapid::Vec2i)
		LIBRAPID_NODISCARD librapid::Vec2i getScaleDPI() const;

		/// \brief Get the number of monitors attached to the system
		/// \return The number of monitors (int64_t)
		LIBRAPID_NODISCARD int64_t getMonitorCount() const;

		/// \brief Get the current frame rate
		/// \return The current frame rate (int64_t)
		LIBRAPID_NODISCARD int64_t getFPS() const;

		/// \brief Get the current frame time
		/// \return The current frame time (float)
		LIBRAPID_NODISCARD float getFrameTime() const;

		/// \brief Get the time elapsed since the window was created
		/// \return The time elapsed (double)
		LIBRAPID_NODISCARD double getTime() const;

		/// \brief Return the number of frames that have been drawn
		/// \return The number of frames (int64_t)
		LIBRAPID_NODISCARD int64_t getFrameCount() const;

		/// \brief Check if the window is ready to be drawn to
		/// \return True if the window is ready, false otherwise
		LIBRAPID_NODISCARD bool isReady() const;

		/// \brief Check if the window should close
		/// \return True if the window should close, false otherwise
		LIBRAPID_NODISCARD bool shouldClose() const;

		/// \brief Get the raw handle of the window
		/// \return The raw handle of the window (void *)
		LIBRAPID_NODISCARD void *getHandle() const;

		/// \brief Begin drawing to the window
		/// This function must be called before any drawing can be done. It triggers a frame to be
		/// created.
		/// \return A reference to the window
		Window &beginDrawing();

		/// \brief End drawing to the window
		/// This function must be called after all drawing has been done. It triggers the frame to
		/// be displayed.
		/// \return A reference to the window
		Window &endDrawing();

		/// \breif Draw the current FPS to the window at the given position
		/// The text is drawn using the default font and automatically changes colour based on the
		/// FPS (green for 30+, yellow for 20+, red for 10+).
		/// \param pos The position to draw the FPS at (librapid::Vec2i)
		/// \return A reference to the window
		Window &drawFPS(const librapid::Vec2i &pos);

		Window &drawFrameTime(const librapid::Vec2i &pos);

		Window &drawTime(const librapid::Vec2i &pos);

		LIBRAPID_NODISCARD Mouse &mouse();
		LIBRAPID_NODISCARD const Mouse &mouse() const;

		// LIBRAPID_NODISCARD Keyboard &keyboard();
		// LIBRAPID_NODISCARD const Keyboard &keyboard() const;
	private:
		int64_t m_frameCount = 0;
		librapid::Vec2i m_initialSize;
		std::string m_initialTitle;
		Mouse m_mouse;
	};
} // namespace surge
