#include <surge/surge.hpp>

namespace surge {
	Mouse &Mouse::show() {
		ShowCursor();
		return *this;
	}

	Mouse &Mouse::hide() {
		HideCursor();
		return *this;
	}

	Mouse &Mouse::makeVisible(bool visible) {
		if (visible) {
			show();
		} else {
			hide();
		}
		return *this;
	}

	bool Mouse::isVisible() const { return !IsCursorHidden(); }

	Mouse &Mouse::enable() {
		EnableCursor();
		return *this;
	}

	Mouse &Mouse::disable() {
		DisableCursor();
		return *this;
	}

	Mouse &Mouse::makeEnabled(bool enabled) {
		if (enabled) {
			enable();
		} else {
			disable();
		}
		return *this;
	}

	bool Mouse::isOnWindow() const { return IsCursorOnScreen(); }

	bool Mouse::isButtonPressed(MouseButton button) const {
		return IsMouseButtonPressed((int)button);
	}

	bool Mouse::isButtonDown(MouseButton button) const { return IsMouseButtonDown((int)button); }

	bool Mouse::isButtonReleased(MouseButton button) const {
		return IsMouseButtonReleased((int)button);
	}

	bool Mouse::isButtonUp(MouseButton button) const { return IsMouseButtonUp((int)button); }

	librapid::Vec2f Mouse::pos() const {
		auto [x, y] = GetMousePosition();
		return {x, y};
	}

	librapid::Vec2f Mouse::screenSpacePos() const {
		auto [x, y] = GetWindowPosition();
		return librapid::Vec2f(x, y) + pos();
	}

	librapid::Vec2f Mouse::delta() const {
		auto [x, y] = GetMouseDelta();
		return {x, y};
	}

	Mouse &Mouse::setPosition(const librapid::Vec2f &position) {
		SetMousePosition(position.x(), position.y());
		return *this;
	}

	Mouse &Mouse::setOffset(const librapid::Vec2f &offset) {
		SetMouseOffset(offset.x(), offset.y());
		return *this;
	}

	Mouse &Mouse::setScale(const librapid::Vec2f &scale) {
		SetMouseScale(scale.x(), scale.y());
		return *this;
	}

	librapid::Vec2f Mouse::wheel() const {
		auto [x, y] = GetMouseWheelMoveV();
		return {x, y};
	}

	float Mouse::wheelMax() const { return GetMouseWheelMove(); }

	Mouse &Mouse::setCursor(MouseCursor cursor) {
		SetMouseCursor((int)cursor);
		return *this;
	}
} // namespace surge
