#pragma once

namespace surge {
	class Rectangle {
	public:
		enum class GradientDirection { Vertical, Horizontal };

		Rectangle() = default;
		Rectangle(double x, double y, double width, double height, float rotation = 0.0f,
				  float thickness = 1.0, float roundness = 0.0f);

		Rectangle(const librapid::Vec2d &position, const librapid::Vec2d &size,
				  float rotation = 0.0f, float thickness = 1.0, float roundness = 0.0f);

		Rectangle(const Rectangle &other)	  = default;
		Rectangle(Rectangle &&other) noexcept = default;

		Rectangle &operator=(const Rectangle &other)	 = default;
		Rectangle &operator=(Rectangle &&other) noexcept = default;

		LIBRAPID_NODISCARD librapid::Vec2d pos() const;
		LIBRAPID_NODISCARD librapid::Vec2d size() const;
		LIBRAPID_NODISCARD float rotation() const;
		LIBRAPID_NODISCARD float thickness() const;
		LIBRAPID_NODISCARD float roundness() const;

		Rectangle &setPos(const librapid::Vec2d &pos);
		Rectangle &setSize(const librapid::Vec2d &size);
		Rectangle &setRotation(float rotation);
		Rectangle &setThickness(float thickness);
		Rectangle &setRoundness(float roundness);

		void drawLines(const Color &color = Color::white) const;

		void draw(const Color &color = Color::white) const;
		void draw(const Color &v0, const Color &v1, const Color &v2, const Color &v3) const;
		void draw(const Color &first, const Color &second, GradientDirection direction) const;

		RlRectangle rlRectangle() const;

	private:
		librapid::Vec2d m_pos;
		librapid::Vec2d m_size;
		float m_rotation  = 0.0f;
		float m_thickness = 1.0f;
		float m_roundness = 0.0f;
	};
} // namespace surge
