#ifndef DLOGGERTARGET_H
#define DLOGGERTARGET_H

#include <string>
enum Level {
	INFO, WARN, ERROR,
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

#endif
