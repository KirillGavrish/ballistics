#ifndef BASICTYPES_HPP
#define BASICTYPES_HPP

#include "Eigen/Geometry"
#include "ballistics/time/Time.hpp"

using Vector3d = Eigen::Matrix<double, 3, 1>;
using Vector6d = Eigen::Matrix<double, 6, 1>;

struct State
{
    Vector3d position;
    Vector3d velocity;

    State static Zero() { return {Vector3d::Zero(), Vector3d::Zero()}; }

    State operator+(State const &other) const {
        return { (position + other.position).eval(), (velocity + other.velocity).eval()};
    }
    State operator-(State const &other) const {
        return { (position - other.position).eval(), (velocity - other.velocity).eval()};
    }
    State operator*(double const scalar) const {
        return { (position * scalar).eval(), (velocity * scalar).eval()};
    }
    friend State operator*(double const scalar, State const &state) {
        return state * scalar;
    }
    State operator/(double const scalar) const {
        return { (position / scalar).eval(), (velocity / scalar).eval()};
    }
};

struct SatelliteParameters
{
    double mass;

    SatelliteParameters(double const mass_)
        : mass(mass_)
    {}
};

struct Parameters
{
    Time<Scale::TT> t;
};
#endif //BASICTYPES_HPP
