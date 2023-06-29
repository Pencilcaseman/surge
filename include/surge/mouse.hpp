#pragma once

namespace surge {
	class Mouse {
	public:
		/// Default constructor
		Mouse()						  = default;

		/// \brief Copy a mouse object
		/// \param other Object to copy
		Mouse(const Mouse &other)	  = default;

		/// \brief Move a mouse object
		/// \param other Object to move
		Mouse(Mouse &&other) noexcept = default;

		/// \brief Copy assignment operator
		/// \param other Object to copy
		/// \return ``*this``
		Mouse &operator=(const Mouse &other)	 = default;

		/// \brief Move assignment operator
		/// \param other Object to move
		/// \return ``*this``
		Mouse &operator=(Mouse &&other) noexcept = default;

		/// \brief Show the mouse cursor on the window
		/// \return ``*this``
		Mouse &show();

		/// \brief Hide the mouse cursor on the window
		/// \return ``*this``
		Mouse &hide();

		/// \brief Make the mouse cursor visible or not
		/// \param visible ``true`` to show the cursor, ``false`` to hide it
		/// \return ``*this``
		Mouse &makeVisible(bool visible);

		/// \brief Check if the mouse cursor is visible
		/// \return ``true`` if the cursor is visible, ``false`` otherwise
		LIBRAPID_NODISCARD bool isVisible() const;

		/// \brief Enable the mouse cursor
		/// \return ``*this``
		Mouse &enable();

		/// \brief Disable the mouse cursor
		/// \return ``*this``
		Mouse &disable();

		/// \brief Make the mouse cursor enabled or not
		/// \param enabled ``true`` to enable the cursor, ``false`` to disable it
		/// \return ``*this``
		Mouse &makeEnabled(bool enabled);

		/// \brief Return true if the cursor is over the window
		/// \return ``true`` if the cursor is over the window, ``false`` otherwise
		LIBRAPID_NODISCARD bool isOnWindow() const;

		/// \brief Check if a button is pressed (triggered only on first mouse down)
		/// \param button Button to check
		/// \return ``true`` if the button is pressed, ``false`` otherwise
		LIBRAPID_NODISCARD bool isButtonPressed(MouseButton button) const;

		/// \brief Check if a button is down (triggered on every mouse down)
		/// \param button Button to check
		/// \return ``true`` if the button is down, ``false`` otherwise
		LIBRAPID_NODISCARD bool isButtonDown(MouseButton button) const;

		/// \brief Check if a button is released (triggered only on first mouse up)
		/// \param button Button to check
		/// \return ``true`` if the button is released, ``false`` otherwise
		LIBRAPID_NODISCARD bool isButtonReleased(MouseButton button) const;

		/// \brief Check if a button is up (triggered on every mouse up)
		/// \param button Button to check
		/// \return ``true`` if the button is up, ``false`` otherwise
		LIBRAPID_NODISCARD bool isButtonUp(MouseButton button) const;

		/// \brief Get the mouse position in the window
		/// \return Mouse position
		LIBRAPID_NODISCARD librapid::Vec2f pos() const;

		/// \brief Get the mouse position within the whole screen
		/// \return Mouse position
		LIBRAPID_NODISCARD librapid::Vec2f screenSpacePos() const;

		/// \brief Get the mouse position change since the last frame
		/// \return Mouse position change
		LIBRAPID_NODISCARD librapid::Vec2f delta() const;

		/// \brief Set the mouse position in the window
		/// \param position New mouse position
		/// \return ``*this``
		Mouse &setPosition(const librapid::Vec2f &position);

		/// \brief Set the mouse offset
		/// \param offset New mouse offset
		/// \return ``*this``
		Mouse &setOffset(const librapid::Vec2f &offset);

		/// \brief Set the mouse movement scale
		/// \param scale New mouse movement scale
		/// \return ``*this``
		Mouse &setScale(const librapid::Vec2f &scale);

		/// \brief Get the mouse wheel movement
		/// \return Mouse wheel movement
		LIBRAPID_NODISCARD librapid::Vec2f wheel() const;

		/// \brief Get the greatest mouse wheel movement in the last frame
		/// \return Greatest mouse wheel movement
		LIBRAPID_NODISCARD float wheelMax() const;

		/// \brief Set the mouse cursor type
		/// \param cursor New mouse cursor type
		/// \return ``*this``
		Mouse &setCursor(MouseCursor cursor);
	};
} // namespace surge
