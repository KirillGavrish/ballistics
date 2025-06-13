#ifndef BASICTYPES_HPP
#define BASICTYPES_HPP

#include <vector>
#include "Eigen/Geometry"
#include "ballistics/time/Time.hpp"
#include "sofa/sofa.h"

struct State
{
    Eigen::Vector3d position;
    Eigen::Vector3d velocity;
};

using Vector3d = Eigen::Matrix<double, 3, 1>;
using Vector6d = Eigen::Matrix<double, 6, 1>;

struct SatelliteParameters
{
    double mass;
    Eigen::Quaterniond quaternionGcrsToEcef;

    SatelliteParameters(double const mass_, Time<Scale::TT> const &t)
        : mass(mass_)
    {
        Time<Scale::TT> constexpr j2000 = {2451545, 0};
        double nutationPrecession[3][3];
        double nutation[3][3], precession[3][3];

        iauPmat06(j2000.jDay() + j2000.jDayPart(), t.jDay() + t.jDayPart(), precession);

        double epsa;
        iauNut06a(j2000.jDay() + j2000.jDayPart(), t.jDay() + t.jDayPart(), &epsa, nutation);

        iauRxr(nutation, precession, nutationPrecession);
        double const gast = iauGst06(t.jDay() + t.jDayPart(), 0.0, t.jDay() + t.jDayPart(), 0.0, nutationPrecession);

        double rotationZ[3][3];
        iauRz(gast, rotationZ);

        Eigen::Matrix3d const rotMatrix = Eigen::Map<Eigen::Matrix3d>(&rotationZ[0][0]);
        quaternionGcrsToEcef = Eigen::Quaterniond(rotMatrix);
        quaternionGcrsToEcef.normalize();
    }
};

#endif //BASICTYPES_HPP
