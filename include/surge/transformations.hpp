#pragma once

namespace surge {
	void pushMatrix();
	void popMatrix();

	void translate(double x, double y);
	void translate(const librapid::Vec2d &vec);

	void rotate(double angle, double x = 0, double y = 0, double z = 1);

	void scale(double x, double y);
	void scale(const librapid::Vec2d &vec);

	void resetMatrix();
} // namespace surge
