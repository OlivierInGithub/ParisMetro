#pragma once

#include <string>
#include <set>
#include <vector>

namespace ParisMetro
{
	class Station
	{
	public:
		Station();
		Station(std::wstring name, double latitude, double longitude);
		Station(Station&&) = default;
		Station(const Station&) = default;
		~Station();

		Station& operator = (Station&&) = default;

		std::set<long> stop_ids;
		std::wstring name;
		double latitude;
		double longitude;
	};

	class IRatpPlanProvider
	{
	public:
		~IRatpPlanProvider() = default;
		virtual std::vector<Station> GetStations() = 0;
	};
}

