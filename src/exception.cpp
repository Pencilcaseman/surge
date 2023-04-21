#include <raylib/raylib-cpp.hpp>

namespace raylib {
	RayLibException::RayLibException(const std::string &message) : std::runtime_error(message) {}

	void RayLibException::traceLog(int logLevel) {
		::TraceLog(logLevel, std::runtime_error::what());
	}
} // namespace raylib
