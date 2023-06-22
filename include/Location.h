#pragma once
#include <iostream>

struct Location
{

	double latitude;
	double longitude;
	friend std::ostream& operator<<(std::ostream& os, const Location& loc);
	bool operator==(const Location& loc);
	bool operator!=(const Location& loc);
	Location operator+(Location loc);
	Location operator+=(Location loc);
	Location operator<(const Location& loc) const;
};
