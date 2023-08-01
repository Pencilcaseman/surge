#include <surge/surge.hpp>

int main() {
	surge::Window window({800, 600}, "Surge Demo -- Simple Square", surge::defaultFlags);
	surge::Mouse mouse;

	librapid::Vec2d rectSize({100, 100});

	while (!window.shouldClose()) {
		window.beginDrawing();
		window.clear(surge::Color::veryDarkGray);

		surge::Rectangle rect(mouse.pos() - rectSize / 2, rectSize, librapid::now());
		rect.draw(surge::Color::orange);

		window.endDrawing();
	}

	return 0;
}

