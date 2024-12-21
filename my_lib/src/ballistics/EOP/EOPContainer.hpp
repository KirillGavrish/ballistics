#ifndef EOPCONTAINER_HPP
#define EOPCONTAINER_HPP

#include <vector>

class EOPContainer
{
    std::vector<double> mjDays_;
    std::vector<double> duts_;
    std::vector<double> x_;
    std::vector<double> y_;
    std::vector<double> dX_;
    std::vector<double> dY_;
public:
    EOPContainer(
        std::vector<double> const &,
        std::vector<double> const &,
        std::vector<double> const &,
        std::vector<double> const &,
        std::vector<double> const &,
        std::vector<double> const &
        );
    [[nodiscard]] std::vector<double> mjDays() const;
    [[nodiscard]] std::vector<double> duts() const;

    [[nodiscard]] double dut(double mjDay) const;
    [[nodiscard]] double dX(double mjDay) const;
    [[nodiscard]] double dY(double mjDay) const;
    [[nodiscard]] double x(double mjDay) const;
    [[nodiscard]] double y(double mjDay) const;
};

#endif //EOPCONTAINER_HPP
