#include "stdafx.h"
#include "RatpPlanReader.h"
#include "ILogger.h"
#include <sstream>
#include <fstream>


using namespace ParisMetro;

RatpPlanReader::RatpPlanReader(ILogger& logger, std::string ifilePath)
	:log(logger), filePath(ifilePath)
{
}

RatpPlanReader::~RatpPlanReader()
{
}

std::vector<Station> ParisMetro::RatpPlanReader::GetStations()
{
	std::ostringstream msg;
	msg << "Ratp Plan Reader will start reading " << filePath;
	log.LogMessage(msg.str());

	std::map<std::wstring, Station> stations;

	for (auto & p : fs::directory_iterator(filePath))
	{
		ProcessDirectory(p, stations);
	}

	std::vector<Station> stationVector;
	for (const auto& p : stations)
	{
		stationVector.emplace_back(std::move(p.second));
	}

	return stationVector;
}

void RatpPlanReader::ProcessDirectory(const fs::directory_entry& dir_entry
	, std::map<std::wstring, Station>& stations)
{
	std::ostringstream msg;
	msg << "Processing directory " << dir_entry;
	log.LogMessage(msg.str());

	std::ostringstream path;
	path << dir_entry;

	std::string stopsFileStr = path.str() + "/stops.txt";

	std::wifstream stopsFile(stopsFileStr);
	std::wstring line;
	std::getline(stopsFile, line);//first line is column names, no use;

	while (std::getline(stopsFile, line))
	{
		if (!ProcessLine(line, stations))
			break;
	}
}

std::vector<std::wstring> split(const std::wstring& s, wchar_t delimiter)
{
	std::vector<std::wstring> tokens;
	std::wstring token;
	std::wistringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

bool ParisMetro::RatpPlanReader::ProcessLine(std::wstring line, std::map<std::wstring, Station>& stations)
{
	long stopId = 0;
	std::wstring stopName = L"";
	double stopLatitude = 0;
	double stopLongitude = 0;

	if (!GetDataFromLine(line, stopId, stopName, stopLatitude, stopLongitude))
		return false;

	const auto& station = stations.find(stopName);
	if (station != stations.end())
	{
		station->second.stop_ids.insert(stopId);
	}
	else
	{
		auto result = stations.try_emplace(stopName, stopName, stopLatitude, stopLongitude);
		if (result.second)
			result.first->second.stop_ids.insert(stopId);
	}
	
	return true;
}

bool ParisMetro::RatpPlanReader::GetDataFromLine(std::wstring line, long & stopId, std::wstring & stopName, double & stopLati, double & stopLongi)
{
	std::vector<std::wstring> stringVect = split(line, L',');
	if (stringVect.size() < 7)
	{
		std::wostringstream msg;
		msg << L"Error while parsing line " << line << ". Number of elements : " << stringVect.size();
		log.LogMessage(msg.str());
		return false;
	}
	std::wistringstream iss(stringVect[0]);
	iss >> stopId;
	stopName = stringVect[2].substr(1, stringVect[2].size() - 2);
	std::wistringstream iss2(stringVect[4]);
	iss2 >> stopLati;
	std::wistringstream iss3(stringVect[5]);
	iss3 >> stopLongi;
	return true;
}
