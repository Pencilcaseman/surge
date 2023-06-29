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
		float a = 1.0f;
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
		Color(uint8_t r, uint8_t g, uint8_t b, float a = 1.0f);
		Color(const librapid::Vec4f &vec);
		Color(const Color &other)	  = default;
		Color(Color &&other) noexcept = default;

		static Color fromRGBA(const RGBA &rgba);
		static Color fromHSVA(const HSVA &hsva);
		static Color fromHSLA(const HSLA &hsla);

		static Color random();

		Color &operator=(const Color &other)	 = default;
		Color &operator=(Color &&other) noexcept = default;

		bool operator==(const Color &other) const;
		bool operator!=(const Color &other) const;

		LIBRAPID_NODISCARD RGB rgb() const;
		LIBRAPID_NODISCARD RGBA rgba() const;
		LIBRAPID_NODISCARD HSV hsv() const;
		LIBRAPID_NODISCARD HSVA hsva() const;
		LIBRAPID_NODISCARD HSL hsl() const;
		LIBRAPID_NODISCARD HSLA hsla() const;

		const static Color empty;
		const static Color gray;
		const static Color darkGray;
		const static Color veryDarkGray;
		const static Color lightGray;
		const static Color veryLightGray;
		const static Color yellow;
		const static Color gold;
		const static Color orange;
		const static Color pink;
		const static Color red;
		const static Color maroon;
		const static Color green;
		const static Color lime;
		const static Color darkGreen;
		const static Color skyBlue;
		const static Color blue;
		const static Color darkBlue;
		const static Color purple;
		const static Color violet;
		const static Color darkPurple;
		const static Color beige;
		const static Color brown;
		const static Color darkBrown;
		const static Color white;
		const static Color black;
		const static Color blank;
		const static Color magenta;
		const static Color cyan;
	private:
		librapid::Vec4f m_color; // Stores the value as RGBA (0.0f - 1.0f)
	};
} // namespace surge
