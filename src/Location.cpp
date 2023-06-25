#include "../include/Location.h"
std::ostream& operator<<(std::ostream& os, const Location& loc)
{
	os << "(" << loc.latitude << " , " << loc.longitude << " ) ";
	return os;
}

bool Location::operator==(const Location& loc)
{
	return loc.latitude == latitude && loc.longitude == longitude;
}

bool Location::operator!=(const Location& loc)
{
	return loc.latitude != latitude || loc.longitude != longitude;
}

Location Location::operator+(Location loc)
{
	return Location(loc.latitude + latitude,loc.longitude + longitude);
}

Location Location::operator+=(Location loc)
{
	latitude += loc.latitude;
	longitude += loc.longitude;
	return *this;
}

