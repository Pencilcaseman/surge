#include <surge/surge.hpp>

namespace surge {
	Mouse &Mouse::show() {
		::RL_ShowCursor();
		return *this;
	}

	Mouse &Mouse::hide() {
		::RL_HideCursor();
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

	bool Mouse::isVisible() const { return !::RL_IsCursorHidden(); }

	Mouse &Mouse::enable() {
		::RL_EnableCursor();
		return *this;
	}

	Mouse &Mouse::disable() {
		::RL_DisableCursor();
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

	bool Mouse::isOnWindow() const { return ::RL_IsCursorOnScreen(); }

	bool Mouse::isButtonPressed(MouseButton button) const {
		return ::RL_IsMouseButtonPressed((int)button);
	}

	bool Mouse::isButtonDown(MouseButton button) const { return ::RL_IsMouseButtonDown((int)button); }

	bool Mouse::isButtonReleased(MouseButton button) const {
		return ::RL_IsMouseButtonReleased((int)button);
	}

	bool Mouse::isButtonUp(MouseButton button) const { return ::RL_IsMouseButtonUp((int)button); }

	librapid::Vec2f Mouse::pos() const {
		auto [x, y] = ::RL_GetMousePosition();
		return {x, y};
	}

	librapid::Vec2f Mouse::screenSpacePos() const {
		auto [x, y] = ::RL_GetWindowPosition();
		return librapid::Vec2f(x, y) + pos();
	}

	librapid::Vec2f Mouse::delta() const {
		auto [x, y] = ::RL_GetMouseDelta();
		return {x, y};
	}

	Mouse &Mouse::setPosition(const librapid::Vec2f &position) {
		::RL_SetMousePosition(position.x(), position.y());
		return *this;
	}

	Mouse &Mouse::setOffset(const librapid::Vec2f &offset) {
		::RL_SetMouseOffset(offset.x(), offset.y());
		return *this;
	}

	Mouse &Mouse::setScale(const librapid::Vec2f &scale) {
		::RL_SetMouseScale(scale.x(), scale.y());
		return *this;
	}

	librapid::Vec2f Mouse::wheel() const {
		auto [x, y] = ::RL_GetMouseWheelMoveV();
		return {x, y};
	}

	float Mouse::wheelMax() const { return ::RL_GetMouseWheelMove(); }

	Mouse &Mouse::setCursor(MouseCursor cursor) {
		::RL_SetMouseCursor((int)cursor);
		return *this;
	}
} // namespace surge
