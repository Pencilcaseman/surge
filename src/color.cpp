#include <surge/surge.hpp>

namespace surge {
	namespace detail {
		static RGB hsvToRgb(float h, float s, float v) {
			float r, g, b;

			int i	= static_cast<int>(h * 6.0f);
			float f = h * 6.0f - static_cast<float>(i);
			float p = v * (1.0f - s);
			float q = v * (1.0f - f * s);
			float t = v * (1.0f - (1.0f - f) * s);

			switch (i % 6) {
				case 0: r = v, g = t, b = p; break;
				case 1: r = q, g = v, b = p; break;
				case 2: r = p, g = v, b = t; break;
				case 3: r = p, g = q, b = v; break;
				case 4: r = t, g = p, b = v; break;
				case 5: r = v, g = p, b = q; break;
			}

			return {static_cast<uint8_t>(r * 255),
					static_cast<uint8_t>(g * 255),
					static_cast<uint8_t>(b * 255)};
		}

		float hueToRgb(float p, float q, float t) {
			if (t < 0.0f) t += 1.0f;
			if (t > 1.0f) t -= 1.0f;
			if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
			if (t < 1.0f / 2.0f) return q;
			if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
			return p;
		}

		RGB hslToRgb(float h, float s, float l) {
			float r, g, b;

			if (s == 0.0f) {
				r = g = b = l; // achromatic
			} else {
				float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
				float p = 2.0f * l - q;
				r		= hueToRgb(p, q, h + 1.0f / 3.0f);
				g		= hueToRgb(p, q, h);
				b		= hueToRgb(p, q, h - 1.0f / 3.0f);
			}

			return {static_cast<uint8_t>(r * 255),
					static_cast<uint8_t>(g * 255),
					static_cast<uint8_t>(b * 255)};
		}
	} // namespace detail

	Color::Color(uint8_t g) : m_color(g, g, g, 255) {}
	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
			m_color(librapid::Vec4d(r, g, b, a) / 255.0f) {}

	Color::Color(const librapid::Vec4f &color) : m_color(color) {}

	Color Color::fromRGBA(const RGBA &rgba) {
		return librapid::Vec4f{static_cast<float>(rgba.r) / 255.0f,
								static_cast<float>(rgba.g) / 255.0f,
								static_cast<float>(rgba.b) / 255.0f,
								static_cast<float>(rgba.a) / 255.0f};
	}

	Color Color::fromHSVA(const HSVA &hsva) {
		auto [r, g, b] = detail::hsvToRgb(hsva.h, hsva.s, hsva.v);
		return librapid::Vec4f {static_cast<float>(r),
								static_cast<float>(g),
								static_cast<float>(b),
								static_cast<float>(hsva.a)};
	};

	Color Color::fromHSLA(const HSLA &hsla) {
		auto [r, g, b] = detail::hslToRgb(hsla.h, hsla.s, hsla.l);
		return librapid::Vec4f {static_cast<uint8_t>(r * 255),
								static_cast<uint8_t>(g * 255),
								static_cast<uint8_t>(b * 255),
								static_cast<uint8_t>(hsla.a * 255)};
	}

	RGB Color::rgb() const {
		return {static_cast<uint8_t>(m_color.x() * 255),
				static_cast<uint8_t>(m_color.y() * 255),
				static_cast<uint8_t>(m_color.z() * 255)};
	}

	RGBA Color::rgba() const {
		return {static_cast<uint8_t>(m_color.x() * 255),
				static_cast<uint8_t>(m_color.y() * 255),
				static_cast<uint8_t>(m_color.z() * 255),
				static_cast<uint8_t>(m_color.w() * 255)};
	}

	uint8_t Color::red() const { return static_cast<uint8_t>(m_color.x() * 255); }
	uint8_t Color::green() const { return static_cast<uint8_t>(m_color.y() * 255); }
	uint8_t Color::blue() const { return static_cast<uint8_t>(m_color.z() * 255); }
	HSV Color::hsv() const { LIBRAPID_NOT_IMPLEMENTED; }
	HSVA Color::hsva() const { LIBRAPID_NOT_IMPLEMENTED; }
	float Color::hue() const { LIBRAPID_NOT_IMPLEMENTED; }
	float Color::saturation() const { LIBRAPID_NOT_IMPLEMENTED; }
	float Color::value() const { LIBRAPID_NOT_IMPLEMENTED; }
	HSL Color::hsl() const { LIBRAPID_NOT_IMPLEMENTED; }
	HSLA Color::hsla() const { LIBRAPID_NOT_IMPLEMENTED; }
	float Color::lightness() const { LIBRAPID_NOT_IMPLEMENTED; }
	float Color::alpha() const { return static_cast<uint8_t>(m_color.w() * 255); }

	const Color colors::white	  = Color::fromRGBA({255, 255, 255, 255});
	const Color colors::black	  = Color::fromRGBA({0, 0, 0, 255});
	const Color colors::red		  = Color::fromRGBA({255, 0, 0, 255});
	const Color colors::green	  = Color::fromRGBA({0, 255, 0, 255});
	const Color colors::blue	  = Color::fromRGBA({0, 0, 255, 255});
	const Color colors::yellow	  = Color::fromRGBA({255, 255, 0, 255});
	const Color colors::cyan	  = Color::fromRGBA({0, 255, 255, 255});
	const Color colors::magenta	  = Color::fromRGBA({255, 0, 255, 255});
	const Color colors::orange	  = Color::fromRGBA({255, 165, 0, 255});
	const Color colors::purple	  = Color::fromRGBA({128, 0, 128, 255});
	const Color colors::brown	  = Color::fromRGBA({165, 42, 42, 255});
	const Color colors::pink	  = Color::fromRGBA({255, 192, 203, 255});
	const Color colors::gray	  = Color::fromRGBA({128, 128, 128, 255});
	const Color colors::lightGray = Color::fromRGBA({211, 211, 211, 255});
	const Color colors::darkGray  = Color::fromRGBA({169, 169, 169, 255});
} // namespace surge
