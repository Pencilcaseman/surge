#include <surge/surge.hpp>

namespace surge {
	Line::Line(const librapid::Vec2d &start, const librapid::Vec2d &end, float thickness) :
			m_start(start), m_end(end), m_thickness(thickness) {}

	librapid::Vec2d Line::start() const { return m_start; }
	librapid::Vec2d Line::end() const { return m_end; }

	void Line::draw(const Color &color) const {
		auto [r, g, b, a] = color.rgba();
		if (m_thickness == 1.0f)
			::DrawLine(static_cast<int>(m_start.x()),
					   static_cast<int>(m_start.y()),
					   static_cast<int>(m_end.x()),
					   static_cast<int>(m_end.y()),
					   {r, g, b, a});
		else
			::DrawLineEx({static_cast<float>(m_start.x()), static_cast<float>(m_start.y())},
						 {static_cast<float>(m_end.x()), static_cast<float>(m_end.y())},
						 m_thickness,
						 {r, g, b, a});
	}

} // namespace surge
