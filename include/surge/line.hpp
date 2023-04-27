#pragma once

namespace surge {
	class Line {
	public:
		Line() = default;
		Line(const librapid::Vec2d &start, const librapid::Vec2d &end, float thickness = 1.0f);
		Line(const Line &other)		= default;
		Line(Line &&other) noexcept = default;

		Line &operator=(const Line &other)	   = default;
		Line &operator=(Line &&other) noexcept = default;

		LIBRAPID_NODISCARD librapid::Vec2d start() const;
		LIBRAPID_NODISCARD librapid::Vec2d end() const;

		Line &addControl(const librapid::Vec2d &control);
		Line &setThickness(float thickness);
		Line &setStart(const librapid::Vec2d &start);
		Line &setEnd(const librapid::Vec2d &end);
		Line &set(const librapid::Vec2d &start, const librapid::Vec2d &end);
		Line &setControl(const librapid::Vec2d &control, int index = 0);

		void draw(const Color &color = Color::white) const;

	private:
		librapid::Vec2d m_start;
		librapid::Vec2d m_end;
		librapid::Vec2d m_controls[2];
		int m_numControls = 0;
		float m_thickness = 1.0f;
	};
} // namespace surge
