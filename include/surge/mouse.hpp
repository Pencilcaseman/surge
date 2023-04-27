#pragma once

namespace surge {
	class Mouse {
	public:
		Mouse()						  = default;
		Mouse(const Mouse &other)	  = default;
		Mouse(Mouse &&other) noexcept = default;

		Mouse &operator=(const Mouse &other)	 = default;
		Mouse &operator=(Mouse &&other) noexcept = default;

		Mouse &show();
		Mouse &hide();
		Mouse &makeVisible(bool visible);
		LIBRAPID_NODISCARD bool isVisible() const;

		Mouse &enable();
		Mouse &disable();
		Mouse &makeEnabled(bool enabled);

		LIBRAPID_NODISCARD bool isOnWindow() const;
		LIBRAPID_NODISCARD bool isButtonPressed(MouseButton button) const;
		LIBRAPID_NODISCARD bool isButtonDown(MouseButton button) const;
		LIBRAPID_NODISCARD bool isButtonReleased(MouseButton button) const;
		LIBRAPID_NODISCARD bool isButtonUp(MouseButton button) const;

		LIBRAPID_NODISCARD librapid::Vec2f position() const;
		LIBRAPID_NODISCARD librapid::Vec2f screenSpacePosition() const;
		LIBRAPID_NODISCARD librapid::Vec2f delta() const;
		Mouse &setPosition(const librapid::Vec2f &position);
		Mouse &setOffset(const librapid::Vec2f &offset);
		Mouse &setScale(const librapid::Vec2f &scale);

		LIBRAPID_NODISCARD librapid::Vec2f wheel() const;
		LIBRAPID_NODISCARD float wheelMax() const;

		Mouse &setCursor(MouseCursor cursor);
	};
} // namespace surge
