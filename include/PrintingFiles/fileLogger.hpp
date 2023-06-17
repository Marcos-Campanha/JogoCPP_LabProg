#pragma once

#ifndef FILELOGGER_HPP
#define FILELOGGER_HPP

#include "loggerInterface.hpp"
#include <fstream>
#include <iostream>

class FileLogger : public LoggerInterface
{
private:
	std::ofstream logFile;

public:
    FileLogger();

    ~FileLogger();

    void logToFileAndConsole(const std::string& message) override;

    void logToFileAndConsoleNoBreak(const std::string& message) override;
};

#endif