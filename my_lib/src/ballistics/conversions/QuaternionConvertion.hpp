#ifndef QUATERNIONCONVERTION_HPP
#define QUATERNIONCONVERTION_HPP

#include "ballistics/time/Time.hpp"
#include "Eigen/Dense"
#include "sofa/sofa.h"

class QuaternionConvertion
{
public:
    [[nodiscard]] static Eigen::Quaterniond guaternionGcrstoEcef(Time<Scale::TT> const &t)
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
        return Eigen::Quaterniond(rotMatrix).normalized();
    }
};
#endif //QUATERNIONCONVERTION_HPP
