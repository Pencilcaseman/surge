#pragma once

namespace surge {
	namespace detail {
		std::string findFontFile(const std::string &fontName, bool &found, bool retry = true);
	}

	class Font {
	public:
		Font()						= default;
		Font(const Font &other)		= default;
		Font(Font &&other) noexcept = default;
		Font(const std::string &fontName, int64_t fontSize = 12);

		Font &operator=(const Font &other)	   = default;
		Font &operator=(Font &&other) noexcept = default;

		bool initialized() const;
		const std::string &fontName() const;
		int64_t fontSize() const;
		::Font font() const;

		std::string &fontName();
		int64_t &fontSize();

	private:
		bool m_initialized = false;
		std::string m_fontName;
		int64_t m_fontSize = 20;
	};

	enum class Modifiers { Bold, Italic };

	Font operator|(const Font &lhs, Modifiers rhs);
	Font operator|(Modifiers lhs, const Font &rhs);
} // namespace surge
