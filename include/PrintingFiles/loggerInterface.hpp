#pragma once

#ifndef LOGGERINTERFACE_HPP
#define LOGGERINTERFACE_HPP

#include <string>

class LoggerInterface
{
public:
	virtual ~LoggerInterface();

	virtual void logToFileAndConsole(const std::string& message) = 0;

	virtual void logToFileAndConsoleNoBreak(const std::string& message) = 0;
};

#endif