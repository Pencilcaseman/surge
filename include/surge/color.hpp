#pragma once

namespace surge {
	struct RGB {
		uint8_t r = 255;
		uint8_t g = 255;
		uint8_t b = 255;
	};

	struct RGBA {
		uint8_t r = 255;
		uint8_t g = 255;
		uint8_t b = 255;
		uint8_t a = 255;
	};

	struct HSV {
		float h = 0.0f;
		float s = 0.0f;
		float v = 0.0f;
	};

	struct HSVA {
		float h = 0.0f;
		float s = 0.0f;
		float v = 0.0f;
		float a = 1.0f;
	};

	namespace detail {
		RGB hsvToRgb(float h, float s, float v);
		float hueToRgb(float p, float q, float t);
		RGB hslToRgb(float h, float s, float l);
	} // namespace detail

	struct HSL {
		float h = 0.0f;
		float s = 0.0f;
		float l = 0.0f;
	};

	struct HSLA {
		float h = 0.0f;
		float s = 0.0f;
		float l = 0.0f;
		float a = 1.0f;
	};

	class Color {
	public:
		Color() = default;
		explicit Color(uint8_t g);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		Color(const librapid::Vec4f &vec);
		Color(const Color &other)	  = default;
		Color(Color &&other) noexcept = default;

		static Color fromRGBA(const RGBA &rgba);
		static Color fromHSVA(const HSVA &hsva);
		static Color fromHSLA(const HSLA &hsla);

		Color &operator=(const Color &other)	 = default;
		Color &operator=(Color &&other) noexcept = default;

		LIBRAPID_NODISCARD RGB rgb() const;
		LIBRAPID_NODISCARD RGBA rgba() const;
		LIBRAPID_NODISCARD uint8_t red() const;
		LIBRAPID_NODISCARD uint8_t green() const;
		LIBRAPID_NODISCARD uint8_t blue() const;

		LIBRAPID_NODISCARD HSV hsv() const;
		LIBRAPID_NODISCARD HSVA hsva() const;
		LIBRAPID_NODISCARD float hue() const;
		LIBRAPID_NODISCARD float saturation() const;
		LIBRAPID_NODISCARD float value() const;

		LIBRAPID_NODISCARD HSL hsl() const;
		LIBRAPID_NODISCARD HSLA hsla() const;
		LIBRAPID_NODISCARD float lightness() const;

		LIBRAPID_NODISCARD float alpha() const;
	private:
		librapid::Vec4f m_color; // Stores the value as RGBA (0.0f - 1.0f)
	};

	struct colors {
		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color yellow;
		static const Color cyan;
		static const Color magenta;
		static const Color orange;
		static const Color purple;
		static const Color brown;
		static const Color pink;
		static const Color gray;
		static const Color lightGray;
		static const Color darkGray;
	};
} // namespace surge
