#include <Paths.hpp>
#include "ballistics/forces/CentralForce.hpp"
#include "gtest/gtest.h"
#include "ballistics/types/Types.hpp"
#include "ballistics/conversions/QuaternionConvertion.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;
static constexpr double eps1000 = std::numeric_limits<double>::epsilon() * 1000;

TEST(CentralForce, adequacyISS)
{
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const forceCalculator(resourcesPath() / "CentralForce/");
    State const current  = {{6781000, 0, 0}, {0, 7660, 0}};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
    std::cout << calculated.norm() / satelliteParameters.mass << std::endl;
    ASSERT_NEAR(8.68, calculated.norm() / satelliteParameters.mass, 0.01);
}

TEST(CentralForce, adequacyGEO)
{
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const forceCalculator(resourcesPath() / "CentralForce/");
    State const current  = {{42157000, 0, 0}, {0, 3070, 0}};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
    ASSERT_NEAR(0.224, calculated.norm() / satelliteParameters.mass, 0.001);
}