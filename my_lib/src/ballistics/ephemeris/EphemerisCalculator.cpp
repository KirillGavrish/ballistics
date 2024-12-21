#include "EphemerisCalculator.hpp"

Vector3d EphemerisCalculator::calcPosition(TDB const time, CelestialBodies origin, CelestialBodies body) const
{
    double position[3];
    calceph_compute(
        calceph,
        time.jDay(),
        time.jDayPart(),
        static_cast<int>(body),
        static_cast<int>(origin),
        position
    );
    return Eigen::Vector3d{position} * 1000;
}

Vector6d EphemerisCalculator::calcState(TDB const time, CelestialBodies origin, CelestialBodies body) const
{
    double state[6];
    calceph_compute(
        calceph,
        time.jDay(),
        time.jDayPart(),
        static_cast<int>(body),
        static_cast<int>(origin),
        state
    );
    return Eigen::Matrix<double, 6, 1>{state} * 1000;
}
