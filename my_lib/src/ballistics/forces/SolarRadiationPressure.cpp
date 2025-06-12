//
// Created by Kirill Gavrish on 29.04.2025.
//

#include "ballistics/forces/SolarRadiationPressure.hpp"

double СylindricalShadowFunction::calcShadowFunction(Time<Scale::TDB> const &, Vector3d const &position,
                                                     Vector3d const &sunPosition, Vector3d const &moonPosition)
{
    double const rho = position.cross(-sunPosition).norm() / sunPosition.norm();
    if ((position.dot(sunPosition) < 0) && (rho <  earthRadius))
    {
        return 0;
    }
    else
    {
        Vector3d const sunRelativeMoon = sunPosition - moonPosition;
        Vector3d const positionRelativeMoon = position - moonPosition;
        double const rhoMoon = positionRelativeMoon.cross(-sunRelativeMoon).norm() / sunRelativeMoon.norm();
        if ((positionRelativeMoon.dot(sunRelativeMoon) < 0) && (rhoMoon <  moonRadius)) {
            return 0;
        }
    }
    return -1;
}