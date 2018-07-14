#pragma once
#include "Station.h"
#include "ILogger.h"
#include <filesystem>
#include <map>

namespace fs = std::experimental::filesystem::v1;

namespace ParisMetro {

	class RatpPlanReader :
		public IRatpPlanProvider
	{
	public:
		RatpPlanReader(ILogger& logger, std::string filePath);
		~RatpPlanReader();

		// Inherited via IRatpPlanProvider
		virtual std::vector<Station> GetStations() override;

	private:
		void ProcessDirectory(const fs::directory_entry& dir_entry, 
			std::map<std::wstring, Station>& stations);
		bool ProcessLine(std::wstring line, std::map<std::wstring, Station>& stations);
		bool GetDataFromLine(std::wstring line, long& stopId, std::wstring& stopName, double& stopLati, double& stopLongi);

		ILogger& log;
		std::string filePath;

	};
}

