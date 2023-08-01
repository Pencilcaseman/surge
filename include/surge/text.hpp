#pragma once

namespace surge {
	enum class TextAlign {
		// Bits 0 and 1 are for horizontal alignment.
		// Bits 2 and 3 are for vertical alignment.
		TopLeft		 = 0b0000,
		TopCenter	 = 0b0001,
		TopRight	 = 0b0010,
		MiddleLeft	 = 0b0100,
		MiddleCenter = 0b0101,
		MiddleRight	 = 0b0110,
		BottomLeft	 = 0b1000,
		BottomCenter = 0b1001,
		BottomRight	 = 0b1010,
		Center		 = 0b0101,
		Left		 = 0b0100,
		Right		 = 0b0110,
		Top			 = 0b0001,
		Bottom		 = 0b1001,
	};

	class Text {
	public:
		Text()						= default;
		Text(const Text &other)		= default;
		Text(Text &&other) noexcept = default;
		explicit Text(const librapid::Vec2d &pos, const std::string &text,
					  const Font &font = Font(), double lineHeight = -1);

		Text &operator=(const Text &other)	   = default;
		Text &operator=(Text &&other) noexcept = default;
		Text &operator=(const std::string &text);

		const librapid::Vec2d &pos() const;
		const std::string &text() const;
		void setText(const std::string &text);

		librapid::Vec2d &pos();
		const Font &font() const;
		void setFont(const Font &font);

		librapid::Vec2d size() const;

		void draw(const Color &color  = Color::white,
				  TextAlign alignment = TextAlign::TopLeft) const;

	private:
		librapid::Vec2d m_pos;
		std::string m_text;
		Font m_font;
		double m_lineHeight;
	};
} // namespace surge
