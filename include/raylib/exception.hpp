#pragma once

namespace raylib {
	class RayLibException : public std::runtime_error {
	public:
		RayLibException(const std::string &message);

		void traceLog(int logLevel = LOG_ERROR);
	};
} // namespace raylib
