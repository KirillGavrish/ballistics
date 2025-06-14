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

    SatelliteParameters(double const mass_)
        : mass(mass_)
    {}
};

#endif //BASICTYPES_HPP
