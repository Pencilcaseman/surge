#include <surge/surge.hpp>

namespace ImGui {
	void PushFont(const surge::Font &font) { ImGui::PushFont(font.imFont()); }
} // namespace ImGui
