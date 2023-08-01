#include <surge/surge.hpp>

int main() {
	surge::Window window({800, 600}, "Surge Demo -- Demo Window", surge::defaultFlags);
	surge::Text text(window.size() / 2, "Hello, world!", surge::Font("Arial", 72));

	while (!window.shouldClose()) {
		window.beginDrawing();
		window.clear(surge::Color::veryDarkGray);
		text.draw(surge::Color::lightGray, surge::TextAlign::Center);
		window.endDrawing();
	}

	return 0;
}

