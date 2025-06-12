#ifndef BASICTYPES_HPP
#define BASICTYPES_HPP

#include <vector>
#include "Eigen/Geometry"

struct State {
    Eigen::Vector3d position;
    Eigen::Vector3d velocity;
};

using Vector3d = Eigen::Matrix<double, 3, 1>;
using Vector6d = Eigen::Matrix<double, 6, 1>;

#endif //BASICTYPES_HPP
