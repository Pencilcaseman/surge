#include <surge/surge.hpp>

namespace surge {
	Text::Text(const std::string &text, const Font &font, double lineHeight) :
			m_text(text), m_font(font), m_lineHeight(lineHeight) {
		if (m_lineHeight < 0) {
			auto [width, height] =
			  ::MeasureTextEx(font.font(), "dummy text", static_cast<float>(font.fontSize()), 0);
			m_lineHeight = height;
		}
	}

	Text &Text::operator=(const std::string &text) {
		m_text = text;
		return *this;
	}

	const std::string &Text::text() const { return m_text; }
	void Text::setText(const std::string &text) { m_text = text; }

	const Font &Text::font() const { return m_font; }
	void Text::setFont(const Font &font) { m_font = font; }

	librapid::Vec2d Text::size() const {
		auto [width, height] =
		  ::MeasureTextEx(m_font.font(), m_text.c_str(), static_cast<float>(m_font.fontSize()), 0);

		return {static_cast<double>(width), static_cast<double>(height)};
	}

	void Text::draw(const librapid::Vec2d &position, const Color &color,
					TextAlign alignment) const {
		auto [r, g, b, a]		= color.rgba();
		librapid::Vec2d drawPos = position;
		int horizontalAlignment = static_cast<int>(alignment) & 0b0011;
		int verticalAlignment	= static_cast<int>(alignment) & 0b1100;

		switch (horizontalAlignment) {
			case 0: // Left
				break;
			case 1: // Center
				drawPos.x() = drawPos.x() - size().x() / 2;
				break;
			case 2: // Right
				drawPos.x() = drawPos.x() - size().x();
				break;
			default: break;
		}

		switch (verticalAlignment) {
			case 0: // Top
				break;
			case 4: // Middle
				drawPos.y() = drawPos.y() - size().y() / 2;
				break;
			case 8: // Bottom
				drawPos.y() = drawPos.y() - size().y();
				break;
			default: break;
		}

		SetTextLineSpacing(static_cast<int>(m_lineHeight));

		if (m_font.initialized()) {
			::DrawTextEx(m_font.font(),
						 m_text.c_str(),
						 {static_cast<float>(drawPos.x()), static_cast<float>(drawPos.y())},
						 static_cast<float>(m_font.fontSize()),
						 0,
						 {
						   r,
						   g,
						   b,
						   static_cast<uint8_t>(a * 255),
						 });
		} else {
			::DrawText(m_text.c_str(),
					   static_cast<int>(drawPos.x()),
					   static_cast<int>(drawPos.y()),
					   static_cast<int>(m_font.fontSize()),
					   {
						 r,
						 g,
						 b,
						 static_cast<uint8_t>(a * 255),
					   });
		}
	}
} // namespace surge
