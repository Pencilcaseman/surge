#include <surge/surge.hpp>

namespace surge {
	Image::Image(const Image &other) { m_image = ::RL_ImageCopy(other.m_image); }

	Image &Image::operator=(const Image &other) {
		if (this == &other) return *this;

		::RL_UnloadImage(m_image);
		m_image = ::RL_ImageCopy(other.m_image);
		return *this;
	}

	Image::Image(const std::string &filename) {
		m_image = ::RL_LoadImage(filename.c_str());
		LIBRAPID_ASSERT(m_image.data != nullptr, "Failed to load image: {}", filename);
	}

	Image::Image(const Window &window) { m_image = ::RL_LoadImageFromScreen(); }

	Image::Image(const Image &source, const Rectangle &rec) {
		m_image = ::RL_ImageFromImage(source.m_image, rec.rlRectangle());
	}

	Image Image::color(const Color &color, const librapid::Vec2i &size) {
		return {::RL_GenImageColor(size.x(), size.y(), color.rlColor())};
	}

	Image Image::linearGradient(const Color &first, const Color &second,
								const librapid::Vec2i &size, float theta) {
		return {::RL_GenImageGradientLinear(size.x(),
											size.y(),
											int(theta * librapid::constants::radToDeg),
											first.rlColor(),
											second.rlColor())};
	}

	Image Image::radialGradient(const Color &inner, const Color &outer, const librapid::Vec2i &size,
								float density) {
		return {::RL_GenImageGradientRadial(
		  size.x(), size.y(), density, inner.rlColor(), outer.rlColor())};
	}

	Image Image::squareGradient(const Color &inner, const Color &outer, const librapid::Vec2i &size,
								float density) {
		return {::RL_GenImageGradientRadial(
		  size.x(), size.y(), density, inner.rlColor(), outer.rlColor())};
	}

	Image Image::checked(const Color &first, const Color &second, const librapid::Vec2i &size,
						 int checksX, int checksY) {
		return {::RL_GenImageChecked(
		  size.x(), size.y(), checksX, checksY, first.rlColor(), second.rlColor())};
	}

	Image Image::whiteNoise(const librapid::Vec2i &size, float factor) {
		return {::RL_GenImageWhiteNoise(size.x(), size.y(), factor)};
	}

	Image Image::perlinNoise(const librapid::Vec2i &size, int offsetX, int offsetY, int scale) {
		return {::RL_GenImagePerlinNoise(size.x(), size.y(), offsetX, offsetY, scale)};
	}

	Image Image::cellular(const librapid::Vec2i &size, int tileSize) {
		return {::RL_GenImageCellular(size.x(), size.y(), tileSize)};
	}

	Image Image::text(const std::string &text, const Color &color, const Font &font,
					  float spacing) {
		return {RL_ImageTextEx(font.rlFont(), text.c_str(), font.size(), spacing, color.rlColor())};
	}

	Image::~Image() { ::RL_UnloadImage(m_image); }

	bool Image::save(const std::string &filename) const {
		return ::RL_ExportImage(m_image, filename.c_str());
	}

	bool Image::saveAsCode(const std::string &filename) const {
		return ::RL_ExportImageAsCode(m_image, filename.c_str());
	}

	Image &Image::toPower2(const Color &col) {
		::RL_ImageToPOT(&m_image, col.rlColor());
		return *this;
	}

	Image &Image::crop(const Rectangle &rec) {
		::RL_ImageCrop(&m_image, rec.rlRectangle());
		return *this;
	}

	Image &Image::alphaCrop(float threshold) {
		::RL_ImageAlphaCrop(&m_image, threshold);
		return *this;
	}

	Image &Image::alphaClear(const Color &color, float threshold) {
		::RL_ImageAlphaClear(&m_image, color.rlColor(), threshold);
		return *this;
	}

	Image &Image::alphaMask(const Image &alphaMask) {
		::RL_ImageAlphaMask(&m_image, alphaMask.m_image);
		return *this;
	}

	Image &Image::alphaPremultiply() {
		::RL_ImageAlphaPremultiply(&m_image);
		return *this;
	}

	Image &Image::gaussianBlur(int blurSize) {
		::RL_ImageBlurGaussian(&m_image, blurSize);
		return *this;
	}

	Image &Image::resize(const librapid::Vec2i &size) {
		::RL_ImageResize(&m_image, size.x(), size.y());
		return *this;
	}

	Image &Image::resizeNN(const librapid::Vec2i &size) {
		::RL_ImageResizeNN(&m_image, size.x(), size.y());
		return *this;
	}

	Image &Image::resizeCanvas(const librapid::Vec2i &size, int offsetX, int offsetY,
							   const Color &color) {
		::RL_ImageResizeCanvas(&m_image, size.x(), size.y(), offsetX, offsetY, color.rlColor());
		return *this;
	}

	Image &Image::computeMipmaps() {
		::RL_ImageMipmaps(&m_image);
		return *this;
	}

	Image &Image::dither(int rBpp, int gBpp, int bBpp, int aBpp) {
		rBpp = librapid::clamp(rBpp, 0, 16);
		gBpp = librapid::clamp(gBpp, 0, 16);
		bBpp = librapid::clamp(bBpp, 0, 16);
		aBpp = librapid::clamp(aBpp, 0, 16);
		::RL_ImageDither(&m_image, rBpp, gBpp, bBpp, aBpp);
		return *this;
	}

	Image &Image::flipVertical() {
		::RL_ImageFlipVertical(&m_image);
		return *this;
	}

	Image &Image::flipHorizontal() {
		::RL_ImageFlipHorizontal(&m_image);
		return *this;
	}

	Image &Image::rotate(float theta) {
		::RL_ImageRotate(&m_image, theta);
		return *this;
	}

	Image &Image::rotateCW() {
		::RL_ImageRotateCW(&m_image);
		return *this;
	}

	Image &Image::rotateCCW() {
		::RL_ImageRotateCCW(&m_image);
		return *this;
	}

	Image &Image::tint(const Color &color) {
		::RL_ImageColorTint(&m_image, color.rlColor());
		return *this;
	}

	Image &Image::invert() {
		::RL_ImageColorInvert(&m_image);
		return *this;
	}

	Image &Image::grayscale() {
		::RL_ImageColorGrayscale(&m_image);
		return *this;
	}

	Image &Image::adjustContrast(float contrast) {
		::RL_ImageColorContrast(&m_image, contrast);
		return *this;
	}

	Image &Image::adjustBrightness(int brightness) {
		::RL_ImageColorBrightness(&m_image, brightness);
		return *this;
	}

	Image &Image::replaceColor(const surge::Color &color, const surge::Color &replace) {
		::RL_ImageColorReplace(&m_image, color.rlColor(), replace.rlColor());
		return *this;
	}

	Image &Image::draw(const Rectangle &rec) {
		// To do: Remove this function
		::RlTexture2D texture = ::RL_LoadTextureFromImage(m_image);
		// Wait for the texture to load
		// while (!::RL_IsTextureReady(texture)) {}
		::RL_DrawTexture(texture, rec.pos().x(), rec.pos().y(), Color::white.rlColor());
		// ::RL_UnloadTexture(texture);
		return *this;
	}

	bool Image::isReady() const { return ::RL_IsImageReady(m_image); }
} // namespace surge
