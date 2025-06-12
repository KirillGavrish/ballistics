#include "ballistics/ephemeris/EphemerisCalculator.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"

Vector3d EphemerisCalculator::calcPosition(TDB const time, CelestialBodies origin, CelestialBodies body) const
{
    double position[3];
    calceph_compute(calceph, time.jDay(), time.jDayPart(), static_cast<int>(body),
                    static_cast<int>(origin), position);
    return Vector3d{position} * 1000;
}

Vector6d EphemerisCalculator::calcState(TDB const time, CelestialBodies origin, CelestialBodies body) const
{
    double state[6];
    calceph_compute(calceph, time.jDay(), time.jDayPart(), static_cast<int>(body),
                    static_cast<int>(origin), state);
    return Vector6d{state} * 1000;
}

double EphemerisCalculator::au() const
{
    double AU;
    if (!calceph_getconstant(calceph, "AU", &AU)) {
        throw BallisticsException("Can't read value of AU!");
    }
    return AU;
}

double EphemerisCalculator::clight() const
{
    double CLIGHT;
    if (!calceph_getconstant(calceph, "CLIGHT", &CLIGHT)) {
        throw BallisticsException("Can't read value of CLIGHT!");
    }
    return CLIGHT;
}

