#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>

void assertf(bool condition, const char *format, ...)
{
#ifndef RELEASE
	if (!condition) {
		char output[512];
		va_list args;
		va_start(args, format);
		vsnprintf(output, 512, format, args);
		va_end(args);
		std::string outputStr = output;
		outputStr += '\n';
		throw std::runtime_error(outputStr);
	}
#endif
}

#endif

