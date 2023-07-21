#include <surge/surge.hpp>
#include <rlgl.h>

namespace surge {
	void pushMatrix() { ::rlPushMatrix(); }

	void popMatrix() { ::rlPopMatrix(); }

	void translate(double x, double y) {
		::rlTranslatef(static_cast<float>(x), static_cast<float>(y), 0);
	}

	void translate(const librapid::Vec2d &vec) {
		::rlTranslatef(static_cast<float>(vec.x()), static_cast<float>(vec.y()), 0);
	}

	void rotate(double angle, double x, double y, double z) {
		// Convert radians to degrees
		::rlRotatef(static_cast<float>(angle * librapid::RADTODEG),
					static_cast<float>(x),
					static_cast<float>(y),
					static_cast<float>(z));
	}

	void scale(double x, double y) { ::rlScalef(static_cast<float>(x), static_cast<float>(y), 1); }

	void scale(const librapid::Vec2d &vec) {
		::rlScalef(static_cast<float>(vec.x()), static_cast<float>(vec.y()), 1);
	}

	void resetMatrix() { ::rlLoadIdentity(); }
} // namespace surge
