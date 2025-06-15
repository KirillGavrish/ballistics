#include <Paths.hpp>
#include "ballistics/forces/CentralForce.hpp"
#include "gtest/gtest.h"
#include "ballistics/types/Types.hpp"
#include "ballistics/conversions/QuaternionConvertion.hpp"
#include "ballistics/forces/ForceCalculator.hpp"
#include <iostream>
#include "ballistics/forces/CentralAndJ2Force.hpp"
#include "ballistics/types/SatelliteRHS.hpp"

static constexpr double eps = std::numeric_limits<double>::epsilon();
static constexpr double eps10 = std::numeric_limits<double>::epsilon() * 10;
static constexpr double eps1000 = std::numeric_limits<double>::epsilon() * 1000;

TEST(ForceCalculator, adequacyISS) {
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const centralForce(resourcesPath() / "CentralForce/");
    ForceCalculator const forceCalculator(centralForce, centralForce, centralForce);
    State const current  = {{6781000, 0, 0}, {0, 7660, 0}};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
    ASSERT_NEAR(8.68 * 3., calculated.norm() / satelliteParameters.mass, 1.);
}

TEST(ForceCalculator, adequacyGEO)
{
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const centralForce(resourcesPath() / "CentralForce/");
    ForceCalculator const forceCalculator(centralForce, centralForce, centralForce);
    State const current  = {{42157000, 0, 0}, {0, 3070, 0}};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
    ASSERT_NEAR(0.224 * 3, calculated.norm() / satelliteParameters.mass, 0.001);
}

TEST(ForceCalculator, combination)
{
    Parameters const parameters({2451545, 0});
    SatelliteParameters const satelliteParameters(1000);
    CentralForce const centralForce(resourcesPath() / "CentralForce/");
    CentralAndJ2Force constexpr centralAndJ2Force;
    ForceCalculator const forceCalculator(centralForce, centralAndJ2Force);
    State const current  = {{42157000, 0, 0}, {0, 3070, 0}};
    Vector3d const calculated = forceCalculator.calcForce(current, satelliteParameters, parameters);
   // SatelliteRHS const rhs(forceCalculator, satelliteParameters);
    //Vector3d const calculated = rhs.evaluate(current, parameters);
    ASSERT_NEAR(0.224 * 2, calculated.norm() / satelliteParameters.mass, 0.001);
}