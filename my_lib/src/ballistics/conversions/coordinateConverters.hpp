//
// Created by Kirill Gavrish on 11.02.2025.
//

#ifndef COORDINATECONVERTERS_H
#define COORDINATECONVERTERS_H

#include "ballistics/types/Vector.hpp"

struct Cartesian {
    // Класс орбиты в декартовых координатах
    Vector3d position;  // Радиус-вектор
    Vector3d velocity;  // Вектор скорости
};

struct Keplerian {
    double semiMajorAxis;      // большая полуось (метры)
    double eccentricity;       // эксцентриситет
    double inclination;        // наклонение (радианы)
    double argumentPeriapsis;  // аргумент перицентра (радианы)
    double ascendingNode;      // долгота восходящего узла (радианы)
};

struct KeplerianTrueAnomaly : Keplerian {
    double trueAnomaly;  // истинная аномалия (радианы)
};

struct KeplerianMeanAnomaly : Keplerian {
    double meanAnomaly;  // средняя аномалия (радианы)
};

#endif //COORDINATECONVERTERS_H
