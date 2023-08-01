#pragma once

namespace surge {
	class Circle {
	public:
		Circle()						= default;
		Circle(const Circle &other)		= default;
		Circle(Circle &&other) noexcept = default;
		Circle(const librapid::Vec2d &pos, double radius);

		Circle &operator=(const Circle &other)	   = default;
		Circle &operator=(Circle &&other) noexcept = default;

		const librapid::Vec2d &pos() const;
		const double &radius() const;

		librapid::Vec2d &pos();
		double &radius();

		void draw(const Color &color = Color::white) const;

	private:
		librapid::Vec2d m_pos;
		double m_radius;
	};
} // namespace surge
