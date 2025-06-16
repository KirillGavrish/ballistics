//
// Created by Kirill Gavrish on 11.02.2025.
//
#include <cmath>
#include <limits>
#include "ballistics/conversions/coordinateConverters.hpp"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

template <typename T>
decltype(auto) normalizeAng(const T number) {
    static_assert(std::is_floating_point_v<T>);
    const double n = std::fmod(number, M_PI*2);
    return n >= 0 ? n : n + M_PI;
}

template <typename T>
struct SinCos {
    T sin;
    T cos;
};

template <typename T>
[[nodiscard]] decltype(auto) calcSinCos(const T angle) {
    return SinCos<T>{std::sin(angle), std::cos(angle)};
}

[[nodiscard]] Cartesian convertKeplerianToCartesian(const KeplerianTrueAnomaly& orbit, double gravityParameter) {
    /** formulas from GMATMathSpec 3.1.3, p. 50-51*/

    const double semimajor = orbit.semiMajorAxis;
    const double eccentricity = orbit.eccentricity;
    const double inclination = orbit.inclination;
    const double argumentPeriapsis = orbit.argumentPeriapsis;
    const double ascendingNode = orbit.ascendingNode;
    const double trueAnomaly = orbit.trueAnomaly;

    const double focalParameter = semimajor * (1 - eccentricity * eccentricity);
    const double distance = focalParameter / (1 + eccentricity * std::cos(trueAnomaly));

    const double cosArgumentPeriapsisAndTrueAnomaly = std::cos(argumentPeriapsis + trueAnomaly);
    const double sinArgumentPeriapsisAndTrueAnomal = std::sin(argumentPeriapsis + trueAnomaly);

    const double cosInclination = std::cos(inclination);
    const double sinInclination = std::sin(inclination);

    const double sinAscendingNode = std::sin(ascendingNode);
    const double cosAscendingNode = std::cos(ascendingNode);

    const double cosTrueAnomaly = std::cos(trueAnomaly);
    const double sinTrueAnomaly = std::sin(trueAnomaly);

    const Vector3d position = (Vector3d((cosArgumentPeriapsisAndTrueAnomaly * cosAscendingNode -
                                        cosInclination * sinArgumentPeriapsisAndTrueAnomal * sinAscendingNode),
                                       (cosArgumentPeriapsisAndTrueAnomaly * sinAscendingNode +
                                        cosInclination * sinArgumentPeriapsisAndTrueAnomal * cosAscendingNode),
                                       (sinArgumentPeriapsisAndTrueAnomal * sinInclination)) * distance).eval();

    const double sqrtGravParamByFocalParameter = std::sqrt(gravityParameter / focalParameter);
    const double cosTrueAnomalyPlusEcc = cosTrueAnomaly + eccentricity;
    const double cosArgumentPeriapsis = std::cos(argumentPeriapsis);
    const double sinArgumentPeriapsis = std::sin(argumentPeriapsis);

    const Vector3d velocity(
        sqrtGravParamByFocalParameter * cosTrueAnomalyPlusEcc *
                (-sinArgumentPeriapsis * cosAscendingNode - cosInclination * sinAscendingNode * cosArgumentPeriapsis) -
            sqrtGravParamByFocalParameter * sinTrueAnomaly *
                (cosArgumentPeriapsis * cosAscendingNode - cosInclination * sinAscendingNode * sinArgumentPeriapsis),
        sqrtGravParamByFocalParameter * cosTrueAnomalyPlusEcc *
                (-sinArgumentPeriapsis * sinAscendingNode + cosInclination * cosAscendingNode * cosArgumentPeriapsis) -
            sqrtGravParamByFocalParameter * sinTrueAnomaly *
                (cosArgumentPeriapsis * sinAscendingNode + cosInclination * cosAscendingNode * sinArgumentPeriapsis),
        sqrtGravParamByFocalParameter * (cosTrueAnomalyPlusEcc * sinInclination * cosArgumentPeriapsis -
                                         sinTrueAnomaly * sinInclination * sinArgumentPeriapsis));
    return Cartesian{position, velocity};
}

[[nodiscard]] KeplerianTrueAnomaly convertCartesianToKeplerian(const Cartesian& orbit, double gravityParameter) {
    /** formulas from GMATMathSpec 3.1.2, p. 46-49*/
    const Vector3d& position = orbit.position;
    const Vector3d& velocity = orbit.velocity;

    const double velocityNormSqr = velocity.squaredNorm();
    const double positionNorm = position.norm();

    const Vector3d orbitalMomentum = position.cross(velocity);  // орбитальный момент
    const Vector3d orbitalMomentumNormalized = orbitalMomentum.normalized();
    const Vector3d nodeVectorExp = Vector3d::UnitZ().cross(orbitalMomentum);  // вектор линии узлов
    const double nodeVectorExpNorm = nodeVectorExp.norm();
    const Vector3d e1 = nodeVectorExpNorm > 0 ? Vector3d(nodeVectorExp / nodeVectorExpNorm) : Vector3d::UnitX();
    const Vector3d e2 = orbitalMomentumNormalized.cross(e1);

    const Vector3d eccentricityExp =
        ((velocityNormSqr - gravityParameter / positionNorm) * position - position.dot(velocity) * velocity) /
        gravityParameter;  // эксцентриситет(вектор)

    const double eccentricityExpNorm = eccentricityExp.norm();
    const Vector3d g1 = eccentricityExpNorm > 0 ? Vector3d(eccentricityExp / eccentricityExpNorm) : e1;
    const Vector3d g2 = orbitalMomentumNormalized.cross(g1);
    const double energyIntegral = velocityNormSqr / 2 - gravityParameter / positionNorm;  // интеграл энергии
    const double semiMajorAxis = -gravityParameter / (2 * energyIntegral);  // большая полуось

    const Vector3d vectorForInclination = e1.cross(Vector3d::UnitZ());  // e1.cross(Vector3d::UnitZ())
    const double inclinationX = orbitalMomentum.z();
    const double inclinationY = orbitalMomentum.dot(vectorForInclination);
    const double inclination = std::atan2(inclinationY, inclinationX);
    const double ascNode = std::atan2(e1.y(), e1.x());
    const double ex = g1.dot(e1);
    const double ey = g1.dot(e2);
    const double argPerig = std::atan2(ey, ex);
    const double posX = position.dot(g1);
    const double posY = position.dot(g2);
    const double anomaly = std::atan2(posY, posX);

    return KeplerianTrueAnomaly{semiMajorAxis, eccentricityExpNorm, inclination, normalizeAng(argPerig),
                                normalizeAng(ascNode), normalizeAng(anomaly)};
}

[[nodiscard]] double propagateMeanAnomaly(const double meanAnomaly, const double semiMajorAxis,
                                          const double deltaInSeconds, const double gravityParameter) {
    const double meanMotion = std::sqrt(gravityParameter / semiMajorAxis / semiMajorAxis / semiMajorAxis);
    return meanAnomaly + meanMotion * deltaInSeconds;
}

[[nodiscard]] KeplerianMeanAnomaly propagate(const KeplerianMeanAnomaly& orbit, double deltaInSeconds,
                                             double gravityParameter) {
    const double newMeanAnomaly =
        propagateMeanAnomaly(orbit.meanAnomaly, orbit.semiMajorAxis, deltaInSeconds, gravityParameter);
    return {orbit.semiMajorAxis,     orbit.eccentricity,  orbit.inclination,
            orbit.argumentPeriapsis, orbit.ascendingNode, newMeanAnomaly};
}

[[nodiscard]] double calcMeanFromEccentric(double eccentricAnomaly, double eccentricity) {
    const double eccentricAnomalyNormalized = normalizeAng(eccentricAnomaly);
    const double meanAnomaly = eccentricAnomalyNormalized - eccentricity * sin(eccentricAnomalyNormalized);
    return normalizeAng(meanAnomaly);
}

[[nodiscard]] double calcEccentricFromTrue(double trueAnomaly, double eccentricity) {
    if (eccentricity < 1) {  /// Эллиптический случай
        const double sin = std::sin(trueAnomaly) * std::sqrt(1 - eccentricity * eccentricity);
        const double cos = eccentricity + std::cos(trueAnomaly);
        const double eccentricAnomaly = std::atan2(sin, cos);
        return eccentricAnomaly >= 0 ? eccentricAnomaly : eccentricAnomaly + 2 * M_PI;
    } else if (eccentricity == 1) {  /// Параболический случай
        return std::tan(trueAnomaly / 2);
    } else {  /// Гиперболический случай
        const auto [sinNu, cosNu] = calcSinCos(trueAnomaly);
        const double denom = 1 + eccentricity * cosNu;
        const double shH = sinNu * std::sqrt(eccentricity * eccentricity - 1) / denom;
        const double chH = (eccentricity + cosNu) / denom;
        return std::log(shH + chH);
    }
}

[[nodiscard]] double calcEccentricFromMean(double meanAnomaly, double eccentricity, unsigned int maxNewtonIteration,
                                           double tolerance) {
    const double meanAnomalyNormalized = normalizeAng(meanAnomaly);
    double eccentricAnomaly = meanAnomalyNormalized > M_PI ? meanAnomalyNormalized - eccentricity
                                                                         : meanAnomalyNormalized + eccentricity;
    for (unsigned int i = 0; i < maxNewtonIteration; ++i) {
        const double delta = (meanAnomalyNormalized + eccentricity * std::sin(eccentricAnomaly) - eccentricAnomaly) /
                             (1 - eccentricity * std::cos(eccentricAnomaly));
        eccentricAnomaly += delta;
        if (std::abs(delta) < tolerance) {
            return eccentricAnomaly;
        }
    }
    return eccentricAnomaly;
}

[[nodiscard]] double calcTrueFromEccentric(double eccentricAnomaly, double eccentricity) {
    const double sin = std::sin(eccentricAnomaly) * std::sqrt(1 - eccentricity * eccentricity);
    const double cos = std::cos(eccentricAnomaly) - eccentricity;
    const double anomaly = std::atan2(sin, cos);
    return anomaly >= 0 ? anomaly : anomaly + 2 * M_PI;
}

[[nodiscard]] double calcTrueFromMean(const double meanAnomaly, const double eccentricity, const unsigned int maxIter,
                                      const double tol) {
    auto eccentric = calcEccentricFromMean(meanAnomaly, eccentricity, maxIter, tol);
    return normalizeAng(calcTrueFromEccentric(eccentric, eccentricity));
}

[[nodiscard]] double calcTrueFromMean(const double meanAnomaly, const double eccentricity) {
    return calcTrueFromMean(meanAnomaly, eccentricity, 150, 100 * std::numeric_limits<double>::epsilon());
}

[[nodiscard]] double calcMeanFromTrue(const double trueAnomaly, const double eccentricity) {
    const double eccentric = calcEccentricFromTrue(trueAnomaly, eccentricity);
    return normalizeAng(calcMeanFromEccentric(eccentric, eccentricity));
}

[[nodiscard]] double propagateTrueAnomaly(const double trueAnomaly, const double semiMajorAxis, const double eccentricity,
                                          const double deltaInSeconds, const double gravityParameter) {
    // Представляем истинную аномалию в виде Nu = 2pi*N + deltaNu = mainNu + deltaNu
    const double mainTrueAnomaly = 2 * M_PI * std::floor(trueAnomaly / 2 / M_PI);
    const double deltaTrueAnomaly = trueAnomaly - mainTrueAnomaly;

    const double meanAnomaly = calcMeanFromTrue(deltaTrueAnomaly, eccentricity);

    const double newMeanAnomaly = propagateMeanAnomaly(meanAnomaly, semiMajorAxis, deltaInSeconds, gravityParameter);

    // Представляем среднюю аномалию в виде M = 2pi*K + deltaM = mainM + deltaM
    const double mainNewMeanAnomaly = 2 * M_PI * std::floor(newMeanAnomaly / 2 / M_PI);
    const double deltaNewMeanAnomaly = newMeanAnomaly - mainNewMeanAnomaly;

    constexpr double tol = 20 * std::numeric_limits<double>::epsilon();
    const auto newTrueAnomaly = calcTrueFromMean(deltaNewMeanAnomaly, eccentricity, 150, tol);

    return newTrueAnomaly + mainNewMeanAnomaly + mainTrueAnomaly;
}

[[nodiscard]] KeplerianTrueAnomaly propagate(const KeplerianTrueAnomaly& orbit, const double deltaInSeconds,
                                             const double gravityParameter) {
    const auto newTrueAnomaly = propagateTrueAnomaly(orbit.trueAnomaly, orbit.semiMajorAxis, orbit.eccentricity,
                                                           deltaInSeconds, gravityParameter);
    return KeplerianTrueAnomaly{orbit.semiMajorAxis, orbit.eccentricity, orbit.inclination, orbit.argumentPeriapsis,
                                orbit.ascendingNode, newTrueAnomaly};
}
