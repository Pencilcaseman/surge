#include <surge/surge.hpp>

int main() {
	surge::Window window({800, 600}, "Surge Demo");

	constexpr uint64_t size = 256;
	char fontName[size]		= "Arial";
	int32_t fontSize		= 18;
	char text[size]			= "Hello, World!";
	float value				= 0.0;

	std::vector<float> xValues;
	std::vector<float> yValues;

	surge::Font font(fontName, fontSize);
	ImGui::SetFont(font);

	while (!window.shouldClose()) {
		window.beginDrawing();
		window.clear(surge::Color::veryDarkGray);

		if (ImGui::Begin("Surge Demo Window")) {
			ImGui::TextWrapped(
			  "Surge has full support for ImGui and ImPlot! We are also on the 'docking' branch of "
			  "ImGui, so you can dock windows and even drag them out of the main window!");
			ImGui::Separator();

			ImGui::Text("Font Name");
			if (ImGui::InputText("##name", fontName, size)) { font.name() = fontName; }

			ImGui::Text("Font Size");
			if (ImGui::InputInt("##fontSize", &fontSize)) {
				fontSize	= librapid::clamp(fontSize, 1, 256);
				font.size() = fontSize;
			}

			if (ImGui::Button("Set Font")) { ImGui::SetFont(font); }

			ImGui::Text("This is a text box.");
			ImGui::InputTextMultiline(
			  "##text", text, size, {0, 0}, ImGuiInputTextFlags_AllowTabInput);
			ImGui::Separator();

			ImGui::Text("This is a slider.");
			ImGui::SliderFloat("##value", &value, 0.0, 1.0);

			ImGui::End();
		}

		if (ImGui::Begin("Simple Plot")) {
			if (ImGui::Button("Add Random Points")) {
				for (int i = 0; i < 50; i++) {
					xValues.push_back(librapid::random(0.0f, 1.0f));
					yValues.push_back(librapid::random(0.0f, 1.0f));
				}
			}

			ImPlot::SetNextAxesLimits(0.0f, 1.0f, 0.0f, 1.0f);
			if (ImPlot::BeginPlot("Scatter Plot", {-1, -1})) {
				ImPlot::SetupAxes("x", "y");
				ImPlot::PlotScatter("Scatter", xValues.data(), yValues.data(), xValues.size());
				ImPlot::EndPlot();
			}
			ImGui::End();
		}

		// Draw the values to reflect the changes made in ImGui.
		surge::Text({10, 50}, text, font).draw();

		surge::Rectangle({0, 20}, {window.size().x() * value, 20.0f}, 0, 0, 4)
		  .draw(surge::Color::red);

		window.endDrawing();
	}

	return 0;
}
