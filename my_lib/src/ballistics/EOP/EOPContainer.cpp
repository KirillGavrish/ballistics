#include "EOPContainer.hpp"
#include "ballistics/interpolation/Interpolant.hpp"

EOPContainer::EOPContainer(
       std::vector<double> const &mjDays,
       std::vector<double> const &duts,
       std::vector<double> const &x,
       std::vector<double> const &y,
       std::vector<double> const &dX,
       std::vector<double> const &dY
) : mjDays_(mjDays), duts_(duts), x_(x), y_(y), dX_(dX), dY_(dY)
{}

std::vector<double> EOPContainer::mjDays() const {return mjDays_;};

std::vector<double> EOPContainer::duts() const {return duts_;};

double EOPContainer::dut(double const mjDay) const {return Interpolant{mjDays_, duts_}.evaluate(mjDay);}

double EOPContainer::x(double const mjDay) const {return Interpolant{mjDays_, x_}.evaluate(mjDay);}

double EOPContainer::y(double const mjDay) const {return Interpolant{mjDays_, y_}.evaluate(mjDay);}

double EOPContainer::dX(double const mjDay) const {return Interpolant{mjDays_, dX_}.evaluate(mjDay);}

double EOPContainer::dY(double const mjDay) const {return Interpolant{mjDays_, dY_}.evaluate(mjDay);}