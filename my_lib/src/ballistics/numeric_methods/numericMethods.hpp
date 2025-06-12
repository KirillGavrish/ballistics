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

template <typename ButcherTable>
class NumericalMethod
{
    ButcherTable butcherTable;
public:

    template <typename RHS>
    typename RHS::vec makeStep(typename RHS::vec initialVec, typename RHS::ArgType t, double step, RHS const &rhs)
    {
        Eigen::Vector<Eigen::Vector<double, RHS::size_>, ButcherTable::c.size()> k;
        k[0] = rhs.evaluate(initialVec);

        for (std::size_t i = 1; i < k.size(); ++i)
        {
            auto tmp = Eigen::Vector<double, RHS::size_>::Zeros();
            for (std::size_t j = 0; j < i; ++j) {
                tmp += k[j] * ButcherTable::a[i * ButcherTable::s-1 + j];
            }
            k[i] = rhs.evaluate({initialVec + step * tmp, t + step * ButcherTable::c[i]});
        }

        Eigen::Vector<double, RHS::size_> u1 = k[0] * ButcherTable::b[0];
        Eigen::Vector<double, RHS::size_> u2 = k[0] * ButcherTable::b[0];

        for (std::size_t i = 1; i < k.size(); ++i)
        {
            u1 += k[i] * ButcherTable::b[i];
            u2 += k[i] * ButcherTable::b[i];
        }
        u1 = u1 * step + initialVec;
        u2 = u2 * step + initialVec;
        return {u1, u2}; // ерунда написана что я написал 2 или 3 месяца назад бред
    }

};

#endif //NUMERICMETHODS_HPP
