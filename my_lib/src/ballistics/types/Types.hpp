#ifndef BASICTYPES_HPP
#define BASICTYPES_HPP

#include "Eigen/Geometry"
#include "ballistics/time/Time.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"
#include "ballistics/time/TimeConverter.hpp"

using Vector3d = Eigen::Matrix<double, 3, 1>;
using Vector6d = Eigen::Matrix<double, 6, 1>;

struct State {
    Vector3d position;
    Vector3d velocity;

    State() = default;
    State(Vector3d const &otherPosition, Vector3d const &otherVelocity)
        : position(otherPosition), velocity(otherVelocity)
    {}
    State(Eigen::Matrix<double, 6, 1> const &vec)
        : position({vec(0, 0), vec(1, 0), vec(1, 0)}),
          velocity({vec(3, 0), vec(4, 0), vec(5, 0)})
    {}

    std::size_t static size() { return 6; }
    State static Zero() { return State{Vector3d::Zero(), Vector3d::Zero()}; }

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
    [[nodiscard]] double norm() const {
        return std::sqrt(position.norm() * position.norm() + velocity.norm() * velocity.norm());
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

struct SatelliteParametersFull
{
    double mass;
    double area;
    double dragCoefficient;

    SatelliteParametersFull(double const mass_, double const area_, double const dragCoefficient_)
        : mass(mass_), area(area_), dragCoefficient(dragCoefficient_)
    {}
};

struct Parameters
{
    Time<Scale::TT> t;

    Parameters(Time<Scale::TT> const &t_)
        : t(t_)
    {}

    Parameters operator+(double const &step) const
    {
        double newjDay;
        double const newjDayPart = modf(t.jDay() + t.jDayPart() + step, &newjDay);
        return {{newjDay, newjDayPart}};
    }
    double operator-(Parameters const &other) const {
        return (t.jDay() - other.t.jDay()) + (t.jDayPart() - other.t.jDayPart());
    }
};

template <typename DutContainer>
struct ParametersFull
{
    Time<Scale::TT> t;
    Vector3d earthAngularVelocity;
    double tsi;
    TimeConverter<DutContainer> timeConverter;
    [[nodiscard]] Time<Scale::TDB> tdb() const { return timeConverter.convert<Scale::TDB>(t); }

    ParametersFull(Time<Scale::TT> const &t_, Vector3d const &earthAngularVelocity_,
                   double const tsi_)
        : t(t_), earthAngularVelocity(earthAngularVelocity_), tsi(tsi_)
    {}

    ParametersFull operator+(double const &step) const
    {
        double newTjDay;
        double const newTjDayPart = modf(t.jDay() + t.jDayPart() + step, &newTjDay);
        return {{newTjDay, newTjDayPart}, earthAngularVelocity, tsi};
    }
    double operator-(ParametersFull const &other) const {
        return (t.jDay() - other.t.jDay()) + (t.jDayPart() - other.t.jDayPart());
    }
};
#endif //BASICTYPES_HPP
