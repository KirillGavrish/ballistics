//
// Created by Kirill Gavrish on 13.02.2025.
//

#ifndef NUMERICMETHODS_HPP
#define NUMERICMETHODS_HPP

#include <array>
#include "Eigen/Dense"

struct RK4First
{
    static constexpr unsigned int s = 4;
    static constexpr std::array<double, s> c = {1, 1, 1, 1};
    static constexpr std::array<double, s> b = {2, 2, 2, 2};
    static constexpr std::array<double, 6> a = {1, 2, 3, 4, 5, 6};
};

class Oscillator
{
    using ArgType = double;
    static constexpr unsigned int size_ = 2;
    using vec = Eigen::Vector<double, size_>;
    [[nodiscard]] vec evaluate(ArgType const &, vec const &) const;
};

template <typename ButcherTable, typename Step>
class NumericalMethod
{
    ButcherTable butcherTable;
public:
    template <typename RHS>
    typename RHS::State makeStep(typename RHS::State const &initialVec, typename RHS::ArgType const &t, Step const &step,
                               RHS const &rhs)
    {
        Eigen::Vector<typename RHS::State, ButcherTable::c.size()> k;
        k[0] = rhs.evaluate(initialVec);
        for (std::size_t i = 1; i < k.size(); ++i)
        {
            auto tmp = RHS::State::Zeros();
            for (std::size_t j = 0; j < i; ++j) {
                tmp += k[j] * ButcherTable::a[i * ButcherTable::s-1 + j];
            }
            k[i] = rhs.evaluate({initialVec + step * tmp, t + step * ButcherTable::c[i]});
        }
        typename RHS::State u = k[0] * ButcherTable::b[0];
        for (std::size_t i = 1; i < k.size(); ++i) {
            u += k[i] * ButcherTable::b[i];
        }
        u = u * step + initialVec;
        return u;
    }

};

#endif //NUMERICMETHODS_HPP
