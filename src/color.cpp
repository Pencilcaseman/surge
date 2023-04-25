#include <surge/surge.hpp>

namespace surge {
	namespace detail {
		static RGB hsvToRgb(float h, float s, float v) {
			h = librapid::clamp(h, 0.0f, 1.0f);
			s = librapid::clamp(s, 0.0f, 1.0f);
			v = librapid::clamp(v, 0.0f, 1.0f);
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
			t = librapid::clamp(t, 0.0f, 1.0f);
			if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
			if (t < 1.0f / 2.0f) return q;
			if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
			return p;
		}

		RGB hslToRgb(float h, float s, float l) {
			h = librapid::clamp(h, 0.0f, 1.0f);
			s = librapid::clamp(s, 0.0f, 1.0f);
			l = librapid::clamp(l, 0.0f, 1.0f);

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
	Color::Color(uint8_t r, uint8_t g, uint8_t b, float a) :
			m_color(librapid::Vec4d(r, g, b, a) / 255.0f) {}

	Color::Color(const librapid::Vec4f &color) : m_color(color) {}

	Color Color::fromRGBA(const RGBA &rgba) {
		return librapid::Vec4f {static_cast<float>(rgba.r) / 255.0f,
								static_cast<float>(rgba.g) / 255.0f,
								static_cast<float>(rgba.b) / 255.0f,
								rgba.a};
	}

	Color Color::fromHSVA(const HSVA &hsva) {
		float h		   = librapid::clamp(hsva.h, 0.0f, 1.0f);
		float s		   = librapid::clamp(hsva.s, 0.0f, 1.0f);
		float v		   = librapid::clamp(hsva.v, 0.0f, 1.0f);
		float a		   = librapid::clamp(hsva.a, 0.0f, 1.0f);
		auto [r, g, b] = detail::hsvToRgb(h, s, v);
		return librapid::Vec4f {
		  static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), a};
	};

	Color Color::fromHSLA(const HSLA &hsla) {
		auto [r, g, b] = detail::hslToRgb(hsla.h, hsla.s, hsla.l);
		return librapid::Vec4f {
		  static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), hsla.a};
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
				m_color.w()};
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

	const Color colors::veryDarkGray  = Color::fromRGBA({15, 15, 15, 1});
	const Color colors::veryLightGray = Color::fromRGBA({240, 240, 240, 1});
	const Color colors::lightGray	  = Color::fromRGBA({200, 200, 200, 1});
	const Color colors::gray		  = Color::fromRGBA({130, 130, 130, 1});
	const Color colors::darkGray	  = Color::fromRGBA({80, 80, 80, 1});
	const Color colors::yellow		  = Color::fromRGBA({253, 249, 0, 1});
	const Color colors::gold		  = Color::fromRGBA({255, 203, 0, 1});
	const Color colors::orange		  = Color::fromRGBA({255, 161, 0, 1});
	const Color colors::pink		  = Color::fromRGBA({255, 109, 194, 1});
	const Color colors::red			  = Color::fromRGBA({230, 41, 55, 1});
	const Color colors::maroon		  = Color::fromRGBA({190, 33, 55, 1});
	const Color colors::green		  = Color::fromRGBA({0, 228, 48, 1});
	const Color colors::lime		  = Color::fromRGBA({0, 158, 47, 1});
	const Color colors::darkGreen	  = Color::fromRGBA({0, 117, 44, 1});
	const Color colors::skyBlue		  = Color::fromRGBA({102, 191, 255, 1});
	const Color colors::blue		  = Color::fromRGBA({0, 121, 241, 1});
	const Color colors::darkBlue	  = Color::fromRGBA({0, 82, 172, 1});
	const Color colors::purple		  = Color::fromRGBA({200, 122, 255, 1});
	const Color colors::violet		  = Color::fromRGBA({135, 60, 190, 1});
	const Color colors::darkPurple	  = Color::fromRGBA({112, 31, 126, 1});
	const Color colors::beige		  = Color::fromRGBA({211, 176, 131, 1});
	const Color colors::brown		  = Color::fromRGBA({127, 106, 79, 1});
	const Color colors::darkBrown	  = Color::fromRGBA({76, 63, 47, 1});
	const Color colors::white		  = Color::fromRGBA({255, 255, 255, 1});
	const Color colors::black		  = Color::fromRGBA({0, 0, 0, 1});
	const Color colors::blank		  = Color::fromRGBA({0, 0, 0, 0});
	const Color colors::magenta		  = Color::fromRGBA({255, 0, 255, 1});
	const Color colors::cyan		  = Color::fromRGBA({0, 255, 255, 1});
} // namespace surge
