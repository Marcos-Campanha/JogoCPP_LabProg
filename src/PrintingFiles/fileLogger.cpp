#include "../../include/PrintingFiles/fileLogger.hpp"

FileLogger::FileLogger()
{
    logFile.open("data/battle_log.txt", std::ios::out);
}

FileLogger::~FileLogger() {};

void FileLogger::logToFileAndConsole(const std::string& message)
{
    std::cout << message << std::endl;
    logFile << message << std::endl;
}

void FileLogger::logToFileAndConsoleNoBreak(const std::string& message)
{
    std::cout << message;
    logFile << message;
}