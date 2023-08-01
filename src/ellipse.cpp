#include <surge/surge.hpp>

namespace surge {
	Ellipse::Ellipse(const librapid::Vec2d &pos, const librapid::Vec2d &size, double theta) :
			m_pos(pos), m_size(size), m_theta(theta) {}

	const librapid::Vec2d &Ellipse::pos() const { return m_pos; }

	const librapid::Vec2d &Ellipse::size() const { return m_size; }

	const double &Ellipse::theta() const { return m_theta; }

	librapid::Vec2d &Ellipse::pos() { return m_pos; }

	librapid::Vec2d &Ellipse::size() { return m_size; }

	double &Ellipse::theta() { return m_theta; }

	void Ellipse::draw(const Color &color) const {
		auto [r, g, b, a] = color.rgba();

		if (m_theta != 0) {
			pushMatrix();
			translate(m_pos);
			rotate(m_theta);

			RL_DrawEllipse(static_cast<int>(m_pos.x()),
						   static_cast<int>(m_pos.y()),
						   static_cast<int>(m_size.x()),
						   static_cast<int>(m_size.y()),
						   {r, g, b, static_cast<uint8_t>(a * 255)});

			popMatrix();
		} else {
			RL_DrawEllipse(static_cast<int>(m_pos.x()),
						   static_cast<int>(m_pos.y()),
						   static_cast<int>(m_size.x()),
						   static_cast<int>(m_size.y()),
						   {r, g, b, static_cast<uint8_t>(a * 255)});
		}
	}
} // namespace surge
