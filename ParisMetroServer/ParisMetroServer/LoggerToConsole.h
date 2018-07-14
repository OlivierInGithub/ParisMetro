#pragma once
#include "ILogger.h"
class LoggerToConsole :
	public ILogger
{
public:
	LoggerToConsole();
	~LoggerToConsole();

	virtual void LogMessage(std::string message) override;
	virtual void LogMessage(std::wstring message) override;
};

