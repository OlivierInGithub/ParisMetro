#include "stdafx.h"
#include "LoggerToConsole.h"

#include <iostream>

LoggerToConsole::LoggerToConsole()
{
}


LoggerToConsole::~LoggerToConsole()
{
}

void LoggerToConsole::LogMessage(std::string message)
{
	std::cout << message << "\n";
}

void LoggerToConsole::LogMessage(std::wstring message)
{
	std::wcout << message << L"\n";
}
