#pragma once

namespace surge {
	class Ellipse {
	public:
		Ellipse() = default;
		Ellipse(const Ellipse &other) = default;
		Ellipse(Ellipse &&other) noexcept = default;
		Ellipse(const librapid::Vec2d &pos, const librapid::Vec2d &size, double theta = 0);

		Ellipse &operator=(const Ellipse &other) = default;
		Ellipse &operator=(Ellipse &&other) noexcept = default;

		const librapid::Vec2d &pos() const;
		const librapid::Vec2d &size() const;
		const double &theta() const;

		librapid::Vec2d &pos();
		librapid::Vec2d &size();
		double &theta();

		void draw(const Color &color = Color::white) const;

	private:
		librapid::Vec2d m_pos;
		librapid::Vec2d m_size;
		double m_theta;
	};
} // namespace surge
