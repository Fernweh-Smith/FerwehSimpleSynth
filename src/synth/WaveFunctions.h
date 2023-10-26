//
// Created by Dylan Smith on 17/10/2023.
//

#pragma once

namespace WaveFunctions{
    double sinFromAngle(double angle);
    double sawtoothFromAngle(double angle);
    double triangleFromAngle(double angle);
    double squareFromAngle(double angle);

    double shapeByPower(double x, double power);
    double shapeByFractionalPower(double x, double power);

}


