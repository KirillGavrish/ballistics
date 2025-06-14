#include <Paths.hpp>

#include "ballistics/forces/CentralForce.hpp"
#include "gtest/gtest.h"
#include "ballistics/types/Types.hpp"
#include "ballistics/conversions/QuaternionConvertion.hpp"

struct Parameters
{
    Time<Scale::TT> t0;
    Time<Scale::TT> t;
};

TEST(CentralForce, adequacy)
{
    Parameters const parameters({2451545, 0}, {2451545, 0.01});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const forceCalculator(resourcesPath() / "CentralForce/egm2008.egm.cof", satelliteParameters);
    State const current  = {};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
    ASSERT_NEAR(9.8, calculated.norm(), 0.5);
}

TEST(CentralForce, adequacy2)
{
    Parameters const parameters({2451545, 0}, {2451545, 0.1});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const forceCalculator(resourcesPath() / "CentralForce/egm2008.egm.cof", satelliteParameters);
    State const current  = {};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
    ASSERT_NEAR(9.8, calculated.norm(), 0.5);
}