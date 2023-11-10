#include <surge/surge.hpp>

namespace surge {
	Rectangle::Rectangle(double x, double y, double width, double height, float rotation,
						 float thickness, float roundness) :
			m_pos(x, y),
			m_size(width, height), m_thickness(thickness), m_roundness(roundness),
			m_rotation(rotation) {}

	Rectangle::Rectangle(const librapid::Vec2d &position, const librapid::Vec2d &size,
						 float rotation, float thickness, float roundness) :
			m_pos(position),
			m_size(size), m_rotation(rotation), m_thickness(thickness),
			m_roundness(librapid::clamp(roundness, 0.0f, 1.0f)) {}

	librapid::Vec2d Rectangle::pos() const { return m_pos; }
	librapid::Vec2d Rectangle::size() const { return m_size; }
	float Rectangle::rotation() const { return m_rotation; }
	float Rectangle::thickness() const { return m_thickness; }
	float Rectangle::roundness() const { return m_roundness; }

	Rectangle &Rectangle::setPos(const librapid::Vec2d &pos) {
		m_pos = pos;
		return *this;
	}

	Rectangle &Rectangle::setSize(const librapid::Vec2d &size) {
		m_size = size;
		return *this;
	}

	Rectangle &Rectangle::setRotation(float rotation) {
		m_rotation = rotation;
		return *this;
	}

	Rectangle &Rectangle::setThickness(float thickness) {
		m_thickness = thickness;
		return *this;
	}

	Rectangle &Rectangle::setRoundness(float roundness) {
		m_roundness = roundness;
		return *this;
	}

	void Rectangle::drawLines(const Color &color) const {
		auto [r, g, b, a] = color.rgba();

		if (m_rotation != 0.0f) {
			SURGE_WARN_ONCE("Rotated rectangles cannot be drawn with lines.");
		}

		if (m_roundness == 0) {
			::RL_DrawRectangleLinesEx(
			  {
				static_cast<float>(m_pos.x()),
				static_cast<float>(m_pos.y()),
				static_cast<float>(m_size.x()),
				static_cast<float>(m_size.y()),
			  },
			  m_thickness,
			  {r, g, b, static_cast<uint8_t>(a * 255)});
		} else {
			::RL_DrawRectangleRoundedLines(
			  {
				static_cast<float>(m_pos.x()),
				static_cast<float>(m_pos.y()),
				static_cast<float>(m_size.x()),
				static_cast<float>(m_size.y()),
			  },
			  m_roundness,
			  surge::global::roundedRectSegments,
			  m_thickness,
			  {r, g, b, static_cast<uint8_t>(a * 255)});
		}
	}

	void Rectangle::draw(const Color &color) const {
		auto [r, g, b, a] = color.rgba();

		if (m_rotation != 0) {
			if (m_rotation != 0.0f) {
				SURGE_WARN_ONCE("Rotated rectangles cannot be drawn with a rotation.");
			}

			auto halfSize = m_size * 0.5f;
			auto drawPos  = m_pos + halfSize;

			::RL_DrawRectanglePro(
			  {static_cast<float>(drawPos.x()),
			   static_cast<float>(drawPos.y()),
			   static_cast<float>(m_size.x()),
			   static_cast<float>(m_size.y())},
			  {static_cast<float>(halfSize.x()), static_cast<float>(halfSize.y())},
			  m_rotation * static_cast<float>(librapid::constants::radToDeg),
			  {r, g, b, static_cast<uint8_t>(a * 255)});
		} else if (m_roundness == 0) {
			::RL_DrawRectangle(static_cast<int>(m_pos.x()),
							   static_cast<int>(m_pos.y()),
							   static_cast<int>(m_size.x()),
							   static_cast<int>(m_size.y()),
							   {r, g, b, static_cast<uint8_t>(a * 255)});
		} else {
			::RL_DrawRectangleRounded(
			  {
				static_cast<float>(m_pos.x()),
				static_cast<float>(m_pos.y()),
				static_cast<float>(m_size.x()),
				static_cast<float>(m_size.y()),
			  },
			  m_roundness,
			  surge::global::roundedRectSegments,
			  {r, g, b, static_cast<uint8_t>(a * 255)});
		}
	}

	void Rectangle::draw(const Color &v0, const Color &v1, const Color &v2, const Color &v3) const {
		auto [r0, g0, b0, a0] = v0.rgba();
		auto [r1, g1, b1, a1] = v1.rgba();
		auto [r2, g2, b2, a2] = v2.rgba();
		auto [r3, g3, b3, a3] = v3.rgba();

		if (m_rotation != 0.0f) {
			SURGE_WARN_ONCE("Rotated rectangles cannot be drawn with a gradient.");
		}

		if (m_roundness != 0.0f) {
			SURGE_WARN_ONCE("Rounded rectangles cannot be drawn with a gradient.");
		}

		::RL_DrawRectangleGradientEx(
		  {
			static_cast<float>(m_pos.x()),
			static_cast<float>(m_pos.y()),
			static_cast<float>(m_size.x()),
			static_cast<float>(m_size.y()),
		  },
		  {r0, g0, b0, static_cast<uint8_t>(a0 * 255)},
		  {r3, g3, b3, static_cast<uint8_t>(a3 * 255)},
		  {r2, g2, b2, static_cast<uint8_t>(a2 * 255)},
		  {r1, g1, b1, static_cast<uint8_t>(a1 * 255)});
	}

	RlRectangle Rectangle::rlRectangle() const {
		return {
			static_cast<float>(m_pos.x()),
			static_cast<float>(m_pos.y()),
			static_cast<float>(m_size.x()),
			static_cast<float>(m_size.y()),
		};
	}
} // namespace surge
