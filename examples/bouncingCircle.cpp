#include <surge/surge.hpp>

int main() {
	surge::Window window({800, 600}, "Surge Demo -- Bouncing Circle", surge::defaultFlags);

	surge::Mouse mouse;

	const double gravity  = 3000;
	const double friction = 0.98;
	auto size			  = librapid::random<double>(10, 60);
	auto velocity		  = librapid::Vec2d::random(-1000, 1000);
	auto position		  = librapid::Vec2d::random({size, size}, window.size() - size);

	while (!window.shouldClose()) {
		window.beginDrawing();
		window.clear(surge::Color::veryDarkGray);

		// If the mouse is pressed, apply a force to the circle
		if (mouse.isButtonDown(surge::MouseButton::left)) {
			auto force = librapid::norm(mouse.pos() - position) * 8000;
			velocity += force * window.frameTime();
		}

		velocity += librapid::Vec2d(0, gravity) * window.frameTime();
		position += velocity * window.frameTime();

		// Bounce off the walls
		if (position.x() < size || position.x() > window.size().x() - size) {
			velocity.x() *= -friction;
			position.x() = librapid::clamp(position.x(), size, window.size().x() - size);
		}

		if (position.y() < size || position.y() > window.size().y() - size) {
			velocity.y() *= -friction;
			position.y() = librapid::clamp(position.y(), size, window.size().y() - size);
		}

		surge::Circle(position, size).draw(surge::Color::purple);

		surge::Text({10, 10},
					"Press and hold the left mouse button to apply a force to the circle")
		  .draw();

		surge::Text({10, 30}, fmt::format("Radius: {:.2f}", size)).draw();
		surge::Text({10, 50}, fmt::format("Gravity: {:.2f}", gravity)).draw();
		surge::Text({10, 70}, fmt::format("Friction: {:.2f}", friction)).draw();
		surge::Text({10, 90}, fmt::format("Velocity: {:.2f}", velocity)).draw();
		surge::Text({10, 110}, fmt::format("Position: {:.2f}", position)).draw();

		window.endDrawing();
	}

	return 0;
}
