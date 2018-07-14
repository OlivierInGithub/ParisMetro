#include "stdafx.h"
#include "Station.h"

using namespace ParisMetro;

Station::Station()
{
	name = L"";
	latitude = 0;
	longitude = 0;
}

ParisMetro::Station::Station(std::wstring name, double latitude, double longitude)
	:name(name), latitude(latitude), longitude(longitude)
{
}


Station::~Station()
{
}
