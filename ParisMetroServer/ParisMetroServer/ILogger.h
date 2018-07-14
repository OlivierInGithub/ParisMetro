#pragma once

#include<string>

class ILogger
{
public:
	~ILogger() = default;
	virtual void LogMessage(std::string message) = 0;
	virtual void LogMessage(std::wstring message) = 0;
};
