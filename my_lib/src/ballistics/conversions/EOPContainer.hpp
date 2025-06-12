#ifndef EOPCONTAINER_HPP
#define EOPCONTAINER_HPP

#include "ballistics/types/Vector.hpp"

class EOPContainer
{
    std::vector<double> mjDays_;
    std::vector<double> duts_;
    std::vector<double> x_;
    std::vector<double> y_;
    std::vector<double> dX_;
    std::vector<double> dY_;
public:
    EOPContainer(std::vector<double> const &mjDays,
                 std::vector<double> const &duts,
                 std::vector<double> const &x,
                 std::vector<double> const &y,
                 std::vector<double> const &dX,
                 std::vector<double> const &dY)
                     : mjDays_(mjDays), duts_(duts), x_(x), y_(y), dX_(dX), dY_(dY)
    {}

    [[nodiscard]] std::vector<double> mjDays() const;
    [[nodiscard]] std::vector<double> duts() const;

    [[nodiscard]] double dut(double mjDay) const;
    [[nodiscard]] double dX(double mjDay) const;
    [[nodiscard]] double dY(double mjDay) const;
    [[nodiscard]] double x(double mjDay) const;
    [[nodiscard]] double y(double mjDay) const;
};

#endif //EOPCONTAINER_HPP
