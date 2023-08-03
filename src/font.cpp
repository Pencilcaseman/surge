#include <surge/surge.hpp>

namespace surge {
	namespace detail {
		struct FontPair {
			::RlFont rlFont;
			ImFont *imFont;
		};

		static std::queue<std::pair<std::string, int64_t>> imGuiFontQueue;
		static librapid::UnorderedMap<std::string, FontPair> fontCache;
		static bool shouldSetImGuiFont = false;
		static Font imGuiFontToSet;

		bool stringEndsWith(const std::string &str, const std::string &suffix) {
			return str.size() >= suffix.size() &&
				   str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
		}

		std::string findFontFile(const std::string &fontName, bool &found, bool retry) {
			LIBRAPID_STATUS("Searching for font file: " + fontName);

			// Add the standard extensions for font files to the font name, as well as
			// alternate capitalizations
			std::vector<std::string> possibleNames = {fontName,
													  fontName + ".ttf",
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
			  "",
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

		ImFont *loadFontIntoImGui(const std::string &fontName, float fontSize) {
			bool found;
			std::string filePath = findFontFile(fontName, found);
			if (!found) {
				LIBRAPID_WARN("Could not find font file: " + fontName);
				return nullptr;
			}

			ImGuiIO &io		   = ImGui::GetIO();
			ImFontAtlas *atlas = io.Fonts;
			ImFontConfig cfg;

			// Load the font
			ImFont *font = atlas->AddFontFromFileTTF(filePath.c_str(), fontSize, &cfg);

			if (font) {
				// Build a new texture with the new font
				atlas->Build();

				// Get the new texture data
				unsigned char *pixels;
				int width, height;
				atlas->GetTexDataAsRGBA32(&pixels, &width, &height);

				// Upload the new texture data to the GPU
				GLuint new_texture;
				glGenTextures(1, &new_texture);
				glBindTexture(GL_TEXTURE_2D, new_texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
				glTexImage2D(
				  GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

				// Delete the old texture and set the new one in the ImGui backend
				glDeleteTextures(1, reinterpret_cast<const GLuint *>(&io.Fonts->TexID));
				io.Fonts->TexID = (ImTextureID)(intptr_t)new_texture;
			} else {
				// Error loading font
				LIBRAPID_WARN("Could not load font '{}' into ImGui", filePath);
			}

			return font;
		}

		std::string fontHash(const std::string &fontName, int64_t fontSize) {
			return fmt::format("{}-{}", fontName, fontSize);
		}

		FontPair &loadFromFontCache(const std::string &fontName, int64_t fontSize) {
			std::string fontHash = detail::fontHash(fontName, fontSize);

			// If the font is cached, return it
			if (fontCache.contains(fontHash)) {
				return fontCache[fontHash];
			} else {
				// Otherwise, create it and cache it
				bool found;
				std::string filePath = detail::findFontFile(fontName, found);
				if (found) {
					FontPair pair {};

					// RayLib Font
					pair.rlFont =
					  ::RL_LoadFontEx(filePath.c_str(), static_cast<int>(fontSize), nullptr, 0);

					// ImGui Font
					pair.imFont = nullptr;
					imGuiFontQueue.emplace(fontName, fontSize);

					fontCache[fontHash] = pair;
				} else {
					SURGE_WARN_ONCE("Could not find font file for '{}'", fontName);
					fontCache[fontHash].rlFont = ::RL_GetFontDefault();
					fontCache[fontHash].imFont = nullptr;
				}

				return fontCache[fontHash];
			}
		}
	} // namespace detail

	Font::Font(const std::string &fontName, int64_t fontSize) {
		m_fontName					  = fontName;
		m_fontSize					  = fontSize;
		m_initialized				  = true;
		[[maybe_unused]] auto tmpFont = rlFont();
	}

	bool Font::initialized() const { return m_initialized; }
	const std::string &Font::fontName() const { return m_fontName; }
	int64_t Font::size() const { return m_fontSize; }

	std::string &Font::name() { return m_fontName; }
	int64_t &Font::size() { return m_fontSize; }

	::RlFont Font::rlFont() const {
		return detail::loadFromFontCache(m_fontName, m_fontSize).rlFont;
	}

	ImFont *Font::imFont() const {
		return detail::loadFromFontCache(m_fontName, m_fontSize).imFont;
	}

	void Font::setImGuiFont(ImFont *font) { m_imGuiFont = font; }

	Font operator|(const Font &lhs, Modifiers rhs) {
		Font result = lhs;
		if (rhs == Modifiers::Bold) result.name() += "b";
		if (rhs == Modifiers::Italic) result.name() += "i";
		return result;
	}

	void loadCachedImGuiFonts() {
		while (!detail::imGuiFontQueue.empty()) {
			auto &[fontName, fontSize]		   = detail::imGuiFontQueue.front();
			std::string fontHash			   = detail::fontHash(fontName, fontSize);
			detail::fontCache[fontHash].imFont = detail::loadFontIntoImGui(fontName, fontSize);
			detail::imGuiFontQueue.pop();
		}
	}

	void updateUncachedFont() {
		if (detail::shouldSetImGuiFont) {
			detail::shouldSetImGuiFont = false;
			ImGui::SetFont(detail::imGuiFontToSet);
		}
	}
} // namespace surge

namespace ImGui {
	void SetFont(const surge::Font &font) {
		if (!font.imFont()) {
			surge::detail::shouldSetImGuiFont = true;
			surge::detail::imGuiFontToSet	  = font;
		}
		ImGui::GetIO().FontDefault = font.imFont();
	}
} // namespace ImGui
