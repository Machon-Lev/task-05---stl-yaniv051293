#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include "Location.h"
#include "DistanceCalculator.h"

std::map<std::string, Location> dataMap;

void readFile() {
    std::string filePath;
    std::cout << "Enter the file path: ";
    std::cin >> filePath;
    std::ifstream file(filePath); // Replace "input.txt" with the path to your file
    //std::ifstream file("C:\\exelteam_c\\task6_yaniv\\resources\\data.txt")
    
    if (!file.is_open()) {
        throw std::runtime_error( "Failed to open the file.");
    }

    std::string line;
    std::string locationName;

    while (std::getline(file, line)) {
        locationName = line;
        if (std::getline(file, line)) {
            size_t spacePos = line.find(' ');
            Location location;
            location.latitude = std::stod(line.substr(0, spacePos));
            location.longitude = std::stod(line.substr(spacePos + 3));
            dataMap[locationName] = location;
        }
    }
    file.close();


}


// Predicate to check if a city is within the given radius from the selected city
bool isWithinRadius(const std::pair<std::string, Location>& cityData, const Location& selectedCityData,  int radius, 
                    const DistanceCalculator& distanceCalculator) {
    return distanceCalculator.calculateDistance(cityData.second, selectedCityData) <= radius;
}

// Predicate to check if a city is to the north of the selected city
bool isToNorth(const Location& cityLocation , const Location& selectedCityLocation) {
    return cityLocation.latitude > selectedCityLocation.latitude;
}

// Print the details based on the given city, radius, and norm
void printDetails(const std::string& city, double radius, int norm) {
    auto iter = dataMap.find(city);
    if (iter == dataMap.end()) {
        throw std::runtime_error("ERROR: "+ city+" isn't found in the city list. Please try again.");
    }
    Location selectedLocation = iter->second;
    
    DistanceCalculator distanceCalculator(norm);

    int citiesWithinRadius = std::count_if(dataMap.begin(), dataMap.end(), [&](const std::pair<std::string, Location>& cityData) {
        return cityData.first != city && isWithinRadius(cityData,  selectedLocation, radius, distanceCalculator);
        });

    int citiesToNorth = std::count_if(dataMap.begin(), dataMap.end(), [&](const std::pair<std::string, Location>& cityData) {
        return cityData.first != city && isToNorth(cityData.second,  selectedLocation);
        });

    std::cout << "Search result:" << std::endl;
    std::cout << citiesWithinRadius << " city/cities found in the given radius." << std::endl;
    std::cout << citiesToNorth << " cities are to the north of the selected city." << std::endl;
    std::cout << "City list:" << std::endl;

    std::map<std::string, Location> myMap;
    std::list<std::string> myList;

    std::copy_if(dataMap.begin(), dataMap.end(), std::inserter(myMap, myMap.begin()), [&](const auto& cityData) {
        return cityData.first != city && isWithinRadius(cityData, selectedLocation, radius, distanceCalculator);
        });

    std::transform(myMap.begin(), myMap.end(), std::back_inserter(myList), [](const auto& cityData) {
        return cityData.first;
        });

    std::copy(myList.begin(), myList.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}


std::string getCity() {
    std::string city;
    bool cityValid = false;

    while (!cityValid) {
        std::cout << "Please enter selected city name (with line break after it):\n";
        std::getline(std::cin >> std::ws, city);

        if (city == "0" || std::any_of(dataMap.begin(), dataMap.end(), [&](const auto& pair) {return pair.first == city; }))
            cityValid = true;

        if (!cityValid) {
            std::cout << "Invalid city name. Please try again." << std::endl;
        }
    }

    return city;
}
int main() {
    std::string city;
    double radius;
    int norm;
    try
    {
        readFile();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    city = getCity();
    while (city != "0")
    {

        std::cout << "\nPlease enter the wanted radius :";
        try
        {
            if (!(std::cin >> radius))
            {
                throw std::runtime_error("Invalid input for radius. Please enter a valid number.");
            }
            if (radius < 0)
            {
                throw std::runtime_error("Radius cannot be negative. Please enter a non-negative value.");
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception caught: " << e.what() << std::endl;
            // Clear input stream and ignore remaining characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Prompt for radius again
            continue;
        }

        std::cout << "\nPlease enter the wanted norm (0- L2, Euclidean distance, 1- Linf, Chebyshev distance, 2- L1, Manhattan distance):";
        try
        {
            if (!(std::cin >> norm))
            {
                throw std::runtime_error("Invalid input for norm. Please enter a valid number.");
            }
            if (norm < 0 || norm > 2)
            {
                throw std::runtime_error("Invalid norm. Please enter a value between 0 and 2.");
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception caught: " << e.what() << std::endl;
            // Clear input stream and ignore remaining characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Prompt for norm again
            continue;
        }
        try
        {
            printDetails(city, radius, norm);
        }
        catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        city = getCity();
    }
    return 0;
}