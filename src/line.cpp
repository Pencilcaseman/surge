#include <surge/surge.hpp>

namespace surge {
	Line::Line(const librapid::Vec2d &start, const librapid::Vec2d &end, float thickness) :
			m_start(start), m_end(end), m_thickness(thickness) {}

	librapid::Vec2d Line::start() const { return m_start; }
	librapid::Vec2d Line::end() const { return m_end; }

	Line &Line::addControl(const librapid::Vec2d &control) {
		LIBRAPID_ASSERT(m_numControls < 2, "Cannot add more than 2 controls to a line");
		if (m_numControls < 2) m_controls[m_numControls++] = control;
		return *this;
	}

	Line &Line::setThickness(float thickness) {
		m_thickness = thickness;
		return *this;
	}

	Line &Line::setStart(const librapid::Vec2d &start) {
		m_start = start;
		return *this;
	}

	Line &Line::setEnd(const librapid::Vec2d &end) {
		m_end = end;
		return *this;
	}

	Line &Line::set(const librapid::Vec2d &start, const librapid::Vec2d &end) {
		m_start = start;
		m_end	= end;
		return *this;
	}

	Line &Line::setControl(const librapid::Vec2d &control, int index) {
		LIBRAPID_ASSERT(index >= 0 && index < 2, "Index must be between 0 and 1");
		if (index >= 0 && index < 2) {
			m_controls[index] = control;
			m_numControls	  = librapid::max(m_numControls, index + 1);
		}
		return *this;
	}

	void Line::draw(const Color &color) const {
		auto [r, g, b, a] = color.rgba();

		switch (m_numControls) {
			case 0: {
				if (m_thickness == 1.0f)
					::DrawLine(static_cast<int>(m_start.x()),
							   static_cast<int>(m_start.y()),
							   static_cast<int>(m_end.x()),
							   static_cast<int>(m_end.y()),
							   {r, g, b, static_cast<uint8_t>(a * 255)});
				else
					::DrawLineEx({static_cast<float>(m_start.x()), static_cast<float>(m_start.y())},
								 {static_cast<float>(m_end.x()), static_cast<float>(m_end.y())},
								 m_thickness,
								 {r, g, b, static_cast<uint8_t>(a * 255)});
			} break;
			case 1: {
				::DrawLineBezierQuad(
				  {static_cast<float>(m_start.x()), static_cast<float>(m_start.y())},
				  {static_cast<float>(m_end.x()), static_cast<float>(m_end.y())},
				  {static_cast<float>(m_controls[0].x()), static_cast<float>(m_controls[0].y())},
				  m_thickness,
				  {r, g, b, static_cast<uint8_t>(a * 255)});
			} break;
			case 2: {
				::DrawLineBezierCubic(
				  {static_cast<float>(m_start.x()), static_cast<float>(m_start.y())},
				  {static_cast<float>(m_end.x()), static_cast<float>(m_end.y())},
				  {static_cast<float>(m_controls[0].x()), static_cast<float>(m_controls[0].y())},
				  {static_cast<float>(m_controls[1].x()), static_cast<float>(m_controls[1].y())},
				  m_thickness,
				  {r, g, b, static_cast<uint8_t>(a * 255)});
			} break;
		}
	}
} // namespace surge
