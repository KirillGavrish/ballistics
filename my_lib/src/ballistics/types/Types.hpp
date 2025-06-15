#ifndef BASICTYPES_HPP
#define BASICTYPES_HPP

#include "Eigen/Geometry"
#include "ballistics/time/Time.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"

using Vector3d = Eigen::Matrix<double, 3, 1>;
using Vector6d = Eigen::Matrix<double, 6, 1>;

struct State
{
    Vector3d position;
    Vector3d velocity;

    std::size_t static size() { return 6; }
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
    double operator[](std::size_t const i) const
    {
        if (i > 5u) {
            throw BallisticsException("There are no components with index >= 5 in State object!");
        }
        return i < 3 ? position(i) : velocity(i - 3u);
    }
};

// убрать потом
inline std::ostream& operator<<(std::ostream& os, const State& state) {
    os << "Position: " << state.position.transpose()
       << " | Velocity: " << state.velocity.transpose();
    return os;
}

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

    Parameters(Time<Scale::TT> const &t_)
        : t(t_)
    {}

    Parameters operator+(double const &step) const {
        double newjDay;
        double const newjDayPart = modf(t.jDay() + t.jDayPart() + step, &newjDay);
        return {{newjDay, newjDayPart}};
    }
    double operator-(Parameters const &other) const {
        return (t.jDay() - other.t.jDay()) + (t.jDayPart() - other.t.jDayPart());
    }
};
#endif //BASICTYPES_HPP
