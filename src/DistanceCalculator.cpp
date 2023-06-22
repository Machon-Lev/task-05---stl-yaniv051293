#include "DistanceCalculator.h"
#include <cmath>
#include <array>

DistanceCalculator::DistanceCalculator(int index) {
    std::array<DistanceFunction, 3> distanceFunctions = {
        calculateL2Distance,
        calculateLinfDistance,
        calculateL1Distance
    };

    if (index >= 0 && index < distanceFunctions.size()) {
        distanceFunction = distanceFunctions[index];
    }
    else {
        // Handle invalid index here
        throw std::out_of_range("Invalid distance function index");
    }
}

double DistanceCalculator::calculateDistance(const Location& location1, const Location& location2) const {
    return distanceFunction(location1, location2);
}

// Euclidean distance (L2 distance)
double DistanceCalculator::calculateL2Distance(const Location& location1, const Location& location2) {
    double dx = location1.latitude - location2.latitude;
    double dy = location1.longitude - location2.longitude;
    return std::sqrt(dx * dx + dy * dy);
}

// Chebyshev distance (L-infinity distance)
double DistanceCalculator::calculateLinfDistance(const Location& location1, const Location& location2) {
    double dx = std::abs(location1.latitude - location2.latitude);
    double dy = std::abs(location1.longitude - location2.longitude);
    return std::max(dx, dy);
}

// Manhattan distance (L1 distance)
double DistanceCalculator::calculateL1Distance(const Location& location1, const Location& location2) {
    double dx = std::abs(location1.latitude - location2.latitude);
    double dy = std::abs(location1.longitude - location2.longitude);
    return dx + dy;
}




