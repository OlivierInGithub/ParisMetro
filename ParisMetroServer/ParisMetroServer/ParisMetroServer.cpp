// ParisMetroServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RatpPlanReader.h"
#include "LoggerToConsole.h"
#include <iomanip> //setprecision

#include <string>
#include <sstream>

using namespace ParisMetro;

const std::string RatpFilePath = "C:/Users/rouss/Documents/RATP/RATP_GTFS_LINES";

int main()
{
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	LoggerToConsole logger;
	logger.LogMessage("Starting Paris Metro Server");

	RatpPlanReader planReader(logger, RatpFilePath);
	logger.LogMessage("Retrieving stations");
	std::vector<Station> stations = planReader.GetStations();
	logger.LogMessage("Stations retrieved!");

	logger.LogMessage("Some of the stations: ");

	wchar_t firstLetter = 'A';

	for (const auto& p : stations)
	{
		if (p.name[0] == firstLetter)
		{
			std::wostringstream msg;
			msg << "Station name " << p.name << ", lati " << std::setprecision(17) << p.latitude
				<< ", longi " << p.longitude << ", stop ids ";
			for (long stopId : p.stop_ids)
				msg << stopId << " ";
			logger.LogMessage(msg.str());
			firstLetter++;
		}
	}

	system("pause");
    return 0;
}

