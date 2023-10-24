#pragma once

namespace surge {
	class Image {
	public:
		Image() = default;
		Image(const Image &other);
		Image(Image &&other) noexcept = default;

		Image(const std::string &fileName);
		Image(const Window &window);
		Image(const RlImage &image) : m_image(image) {}

		Image(const Image &source, const Rectangle &rec);

		Image &operator=(const Image &other);
		Image &operator=(Image &&other) noexcept = default;

		static Image color(const Color &color, const librapid::Vec2i &size = {1, 1});
		static Image linearGradient(const Color &first, const Color &second,
									const librapid::Vec2i &size, float theta = 0.0f);
		static Image radialGradient(const Color &inner, const Color &outer,
									const librapid::Vec2i &size, float density = 1.0f);
		static Image squareGradient(const Color &inner, const Color &outer,
									const librapid::Vec2i &size, float density = 1.0f);
		static Image checked(const Color &first, const Color &second, const librapid::Vec2i &size,
							 int checksX = 1, int checksY = 1);
		static Image whiteNoise(const librapid::Vec2i &size, float factor = 0.5f);
		static Image perlinNoise(const librapid::Vec2i &size, int offsetX = 0, int offsetY = 0,
								 int scale = 1);
		static Image cellular(const librapid::Vec2i &size, int tileSize = 1);
		static Image text(const std::string &text, const Color &color = Color::white,
						  const Font &font = Font(), float spacing = 0.0f);

		~Image();

		LIBRAPID_NODISCARD bool save(const std::string &fileName) const;
		LIBRAPID_NODISCARD bool saveAsCode(const std::string &fileName) const;

		Image &toPower2(const Color &col = Color::blank);
		Image &crop(const Rectangle &rec);
		Image &alphaCrop(float threshold = 0.0f);
		Image &alphaClear(const Color &color = Color::blank, float threshold = 0.0f);
		Image &alphaMask(const Image &alphaMask);
		Image &alphaPremultiply();
		Image &gaussianBlur(int blurSize = 1);
		Image &resize(const librapid::Vec2i &size);	  // Bicubic
		Image &resizeNN(const librapid::Vec2i &size); // Nearest-neighbor
		Image &resizeCanvas(const librapid::Vec2i &size, int offsetX = 0, int offsetY = 0,
							const Color &color = Color::blank);
		Image &computeMipmaps();
		Image &dither(int rBpp = 16, int gBpp = 16, int bBpp = 16, int aBpp = 16);
		Image &flipVertical();
		Image &flipHorizontal();
		Image &rotate(float theta = 0.0f);
		Image &rotateCW();
		Image &rotateCCW();
		Image &tint(const Color &color);
		Image &invert();
		Image &grayscale();
		Image &adjustContrast(float contrast);
		Image &adjustBrightness(int brightness);
		Image &replaceColor(const Color &color, const Color &replace);

		// TODO: Image drawing functions

		Image &draw(const Rectangle &rec);

	protected:
		LIBRAPID_NODISCARD bool isReady() const;

	private:
		::RlImage m_image;
	};
} // namespace surge
