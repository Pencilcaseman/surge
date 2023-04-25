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

		void draw(const Color &color = colors::white) const;
	private:
		librapid::Vec2d m_start;
		librapid::Vec2d m_end;
		float m_thickness = 1.0f;
	};
} // namespace surge
