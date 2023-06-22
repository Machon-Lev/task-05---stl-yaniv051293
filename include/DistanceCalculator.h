#pragma once
#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

#include <functional>
#include "Location.h"

class DistanceCalculator {
public:
    using DistanceFunction = std::function<double(const Location&, const Location&)>;

    explicit DistanceCalculator(int index);

    double calculateDistance(const Location& location1, const Location& location2) const;

private:
    static double calculateL2Distance(const Location& location1, const Location& location2);
    static double calculateLinfDistance(const Location& location1, const Location& location2);
    static double calculateL1Distance(const Location& location1, const Location& location2);

    DistanceFunction distanceFunction;
};

#endif