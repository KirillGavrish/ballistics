#include "EOPContainer.hpp"
#include "ballistics/interpolation/Interpolant.hpp"


std::vector<double> EOPContainer::mjDays() const {return mjDays_;}

std::vector<double> EOPContainer::duts() const {return duts_;}

double EOPContainer::dut(double const mjDay) const {return Interpolant{mjDays_, duts_}.evaluate(mjDay);}

double EOPContainer::x(double const mjDay) const {return Interpolant{mjDays_, x_}.evaluate(mjDay);}

double EOPContainer::y(double const mjDay) const {return Interpolant{mjDays_, y_}.evaluate(mjDay);}

double EOPContainer::dX(double const mjDay) const {return Interpolant{mjDays_, dX_}.evaluate(mjDay);}

double EOPContainer::dY(double const mjDay) const {return Interpolant{mjDays_, dY_}.evaluate(mjDay);}