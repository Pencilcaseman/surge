#include <surge/surge.hpp>

namespace surge {
	Text::Text(const librapid::Vec2d &pos, const std::string &text, const Font &font,
			   double lineHeight) :
			m_pos(pos),
			m_text(text), m_font(font), m_lineHeight(lineHeight) {
		if (m_lineHeight < 0) {
			auto [width, height] =
			  ::RL_MeasureTextEx(font.rlFont(), "dummy text", static_cast<float>(font.size()), 0);
			m_lineHeight = height;
		}
	}

	Text &Text::operator=(const std::string &text) {
		m_text = text;
		return *this;
	}

	const librapid::Vec2d &Text::pos() const { return m_pos; }
	const std::string &Text::text() const { return m_text; }
	void Text::setText(const std::string &text) { m_text = text; }

	librapid::Vec2d &Text::pos() { return m_pos; }
	const Font &Text::font() const { return m_font; }
	void Text::setFont(const Font &font) { m_font = font; }

	librapid::Vec2d Text::size() const {
		auto [width, height] =
		  ::RL_MeasureTextEx(m_font.rlFont(), m_text.c_str(), static_cast<float>(m_font.size()), 0);

		return {static_cast<double>(width), static_cast<double>(height)};
	}

	void Text::draw(const Color &color, TextAlign alignment) const {
		auto [r, g, b, a]		= color.rgba();
		librapid::Vec2d drawPos = m_pos;
		int horizontalAlignment = static_cast<int>(alignment) & 0b0011;
		int verticalAlignment	= static_cast<int>(alignment) & 0b1100;

		switch (horizontalAlignment) {
			case 0: // Left
				break;
			case 1: // Center
				drawPos.x() = float(drawPos.x() - size().x()) / 2;
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
				drawPos.y() = float(drawPos.y() - size().y()) / 2;
				break;
			case 8: // Bottom
				drawPos.y() = drawPos.y() - size().y();
				break;
			default: break;
		}

		::RL_SetTextLineSpacing(static_cast<int>(m_lineHeight));

		if (m_font.initialized()) {
			::RL_DrawTextEx(m_font.rlFont(),
							m_text.c_str(),
							{static_cast<float>(drawPos.x()), static_cast<float>(drawPos.y())},
							static_cast<float>(m_font.size()),
							0,
							{
							  r,
							  g,
							  b,
							  static_cast<uint8_t>(a * 255),
							});
		} else {
			::RL_DrawText(m_text.c_str(),
						  static_cast<int>(drawPos.x()),
						  static_cast<int>(drawPos.y()),
						  static_cast<int>(m_font.size()),
						  {
							r,
							g,
							b,
							static_cast<uint8_t>(a * 255),
						  });
		}
	}
} // namespace surge
