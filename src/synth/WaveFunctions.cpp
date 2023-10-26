//
// Created by Dylan Smith on 17/10/2023.
//

#include "WaveFunctions.h"
#include <cmath>
#include <numbers>


#define PI std::numbers::pi
#define TWO_PI (std::numbers::pi * 2.0)

double WaveFunctions::sinFromAngle(double angle) {
    return std::sin(angle);
}

double WaveFunctions::sawtoothFromAngle(double angle) {
    return std::fmod( (angle - PI) /  PI, 2.0) - 1.0;
//    return std::fmod( (PI - angle) /  PI, 2.0) - 1.0;

}

double WaveFunctions::triangleFromAngle(double angle) {
    return (2.0 * std::acos( std::sin(-angle)) / PI) - 1.0;
}

double WaveFunctions::squareFromAngle(double angle) {
    const double angleModulo = std::fmod((angle * -1.0)/TWO_PI, 1.0);
//    return (std::round(angleModulo) * 2.0) - 1.0;
    return (std::signbit(sinFromAngle(angle)) * 2.0) - 1.0;
}

double WaveFunctions::shapeByPower(double x, double power) {
    double sign = 1.0;
    if(std::signbit(x)){
        sign = -1.0;
    }
    return sign * std::pow(std::abs(x), power);
 }

double WaveFunctions::shapeByFractionalPower(double x, double power) {
    double sign = 1.0;
    if(std::signbit(x)){
        sign = -1.0;
    }
    return sign * std::pow(std::abs(x), 1.0 / power);

}
