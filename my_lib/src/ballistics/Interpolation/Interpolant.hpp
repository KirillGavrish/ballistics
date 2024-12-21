#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include "ballistics/exceptions/BallisticsException.hpp"

using u32 = std::uint32_t;

template<typename xType, typename yType>
class Interpolant
{
    std::vector<xType> nodes_;
    std::vector<yType> values_;

public:
    Interpolant(std::vector<xType> const &, std::vector<yType> const &);
    yType evaluate(xType) const;
};

template<typename xType, typename yType>
Interpolant<xType, yType>::Interpolant(std::vector<xType> const &nodes, std::vector<yType> const &values)
        : nodes_(nodes), values_(values)
{
    if (nodes.size() - values.size() != 0)
        throw BallisticsException("Defferent sizes of nodes and values!");
}

template<typename xType, typename yType>
yType Interpolant<xType, yType>::evaluate(xType x) const {
    std::cout << x - nodes_[0];
    if (x < nodes_[0] || x > nodes_[nodes_.size() - 1])
        throw BallisticsException(" Requested point is out of data to Interpolant");

    auto iterator = std::lower_bound(nodes_.begin(), nodes_.end(), x);
    u32 index = iterator - nodes_.begin();

    const auto [a,b, value_a, value_b] = index != 0
        ? std::tuple{nodes_[index - 1], *iterator, values_[index - 1], values_[index]}
    : std::tuple{nodes_[0], nodes_[1], values_[0], values_[1]};

    double k = (value_b - value_a) / (b - a);
    return k * (x - a) + value_a;
}

#endif //INTERPOLATOR_HPP
