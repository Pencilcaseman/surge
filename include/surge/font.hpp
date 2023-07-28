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

		LIBRAPID_NODISCARD bool initialized() const;
		LIBRAPID_NODISCARD const std::string &fontName() const;
		LIBRAPID_NODISCARD std::string &fontName();
		LIBRAPID_NODISCARD int64_t size() const;
		LIBRAPID_NODISCARD int64_t &size();
		LIBRAPID_NODISCARD ::RlFont rlFont() const;
		LIBRAPID_NODISCARD ImFont *imFont() const;

		void setImGuiFont(ImFont *font);

	private:
		bool m_initialized = false;
		std::string m_fontName;
		int64_t m_fontSize = 20;
		ImFont *m_imGuiFont = nullptr;
	};

	enum class Modifiers { Bold, Italic };

	Font operator|(const Font &lhs, Modifiers rhs);
	Font operator|(Modifiers lhs, const Font &rhs);

	void loadCachedImGuiFonts();
	void updateUncachedFont();
} // namespace surge

namespace ImGui {
	void SetFont(const surge::Font &font);
}
