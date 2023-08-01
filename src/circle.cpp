#include <surge/surge.hpp>

namespace surge {
	Circle::Circle(const librapid::Vec2d &pos, double radius) : m_pos(pos), m_radius(radius) {}

	const librapid::Vec2d &Circle::pos() const { return m_pos; }
	const double &Circle::radius() const { return m_radius; }

	librapid::Vec2d &Circle::pos() { return m_pos; }
	double &Circle::radius() { return m_radius; }

	void Circle::draw(const Color &color) const {
		auto [r, g, b, a] = color.rgba();

		RL_DrawCircle(static_cast<int>(m_pos.x()),
					  static_cast<int>(m_pos.y()),
					  static_cast<float>(m_radius),
					  {r, g, b, static_cast<uint8_t>(a * 255)});
	}
} // namespace surge
