#include <surge/surge.hpp>

namespace surge {
	namespace detail {
		std::string capitalizeFirstLetter(std::string str) {
			if (!str.empty()) { str[0] = std::toupper(str[0]); }
			return str;
		}

		std::string findFontFile(const std::string &fontName, bool &found, bool retry) {
			LIBRAPID_STATUS("Searching for font file: " + fontName);

			// Add the standard extensions for font files to the font name, as well as
			// alternate capitalizations
			std::vector<std::string> possibleNames = {fontName + ".ttf",
													  fontName + ".ttc",
													  fontName + ".otf",
													  fontName + ".TTF",
													  fontName + ".TTC",
													  fontName + ".OTF",
													  fontName + ".Ttf",
													  fontName + ".Ttc",
													  fontName + ".Otf"};

			// List the standard directories where fonts are stored on Windows, macOS, and Linux
			// plus a few extras
			std::vector<std::string> directories = {
			  ".",
			  "..",
			  "C:/Windows/Fonts",
			  "/Library/Fonts",
			  "/System/Library/Fonts",
			  "~/Library/Fonts",
			  "/usr/share/fonts",
			  "/usr/local/share/fonts",
			  "~/.fonts",
			  "~/.local/share/fonts",
			  "~/.local/fonts",
			  "~/.local/lib/fonts",
			  "~/.local/lib/share/fonts",
			  "~/.local/lib/x86_64-linux-gnu/fonts",
			};

			// Try each directory
			for (const auto &directory : directories) {
				// Check if the directory exists and is actually a directory
				if (std::filesystem::exists(directory) &&
					std::filesystem::is_directory(directory)) {
					// Try each possible file name
					for (const auto &name : possibleNames) {
						std::filesystem::path filePath = directory + "/" + name;

						// If the file exists and is a regular file, return its path
						if (std::filesystem::exists(filePath) &&
							std::filesystem::is_regular_file(filePath)) {
							LIBRAPID_STATUS("Found font file: " + filePath.string());
							found = true;
							return filePath.string();
						}
					}
				}
			}

			// If we get here, we didn't find the font file

			if (retry) {
				// Try appending " Regular" to the font name
				bool foundRegular = false;
				auto regular	  = findFontFile(fontName + " Regular", foundRegular, false);
				if (foundRegular) {
					found = true;
					return regular;
				}

				// Try appending " Nerd Font Complete Windows Compatible" to the font name
				bool foundNerd = false;
				auto nerd	   = findFontFile(
				   fontName + " Nerd Font Complete Windows Compatible", foundNerd, false);
				if (foundNerd) {
					found = true;
					return nerd;
				}

				// Try appending " Regular Nerd Font Complete Windows Compatible" to the font name
				bool foundRegularNerd = false;
				auto regularNerd =
				  findFontFile(fontName + " Regular Nerd Font Complete Windows Compatible",
							   foundRegularNerd,
							   false);
				if (foundRegularNerd) {
					found = true;
					return regularNerd;
				}

				// Try appending " Nerd Font Complete" to the font name
				bool foundNerdComplete = false;
				auto nerdComplete =
				  findFontFile(fontName + " Nerd Font Complete", foundNerdComplete, false);
				if (foundNerdComplete) {
					found = true;
					return nerdComplete;
				}

				// Try appending " Regular Nerd Font Complete" to the font name
				bool foundRegularNerdComplete = false;
				auto regularNerdComplete	  = findFontFile(
				   fontName + " Regular Nerd Font Complete", foundRegularNerdComplete, false);
				if (foundRegularNerdComplete) {
					found = true;
					return regularNerdComplete;
				}
			}

			found = false;
			return "";
		}

		std::string fontHash(const std::string &fontName, int64_t fontSize) {
			return fmt::format("{}-{}", fontName, fontSize);
		}

		::Font &fontCache(const std::string &fontName, int64_t fontSize) {
			static librapid::UnorderedMap<std::string, ::Font> cache;
			std::string fontHash = detail::fontHash(fontName, fontSize);

			// If the font is cached, return it
			if (cache.contains(fontHash)) {
				return cache[fontHash];
			} else {
				// Otherwise, create it and cache it
				bool found;
				std::string filePath = detail::findFontFile(fontName, found);
				if (found) {
					cache[fontHash] =
					  ::LoadFontEx(filePath.c_str(), static_cast<int>(fontSize), nullptr, 0);
				} else {
					SURGE_WARN_ONCE("Could not find font file for '{}'", fontName);
					cache[fontHash] = ::GetFontDefault();
				}

				return cache[fontHash];
			}
		}
	} // namespace detail

	Font::Font(const std::string &fontName, int64_t fontSize) {
		m_fontName	  = fontName;
		m_fontSize	  = fontSize;
		m_initialized = true;
	}

	bool Font::initialized() const { return m_initialized; }
	const std::string &Font::fontName() const { return m_fontName; }
	int64_t Font::fontSize() const { return m_fontSize; }

	std::string &Font::fontName() { return m_fontName; }
	int64_t &Font::fontSize() { return m_fontSize; }

	::Font Font::font() const { return detail::fontCache(m_fontName, m_fontSize); }

	Font operator|(const Font &lhs, Modifiers rhs) {
		Font result = lhs;
		if (rhs == Modifiers::Bold) result.fontName() += "b";
		if (rhs == Modifiers::Italic) result.fontName() += "i";
		return result;
	}
} // namespace surge
