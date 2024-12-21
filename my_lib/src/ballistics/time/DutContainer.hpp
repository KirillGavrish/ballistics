#ifndef DUTCONTAINER_HPP
#define DUTCONTAINER_HPP

#include <vector>
#include "ballistics/eop/EOPContainer.hpp"

class DutContainer
{
    std::vector<double> mjDays_;
    std::vector<double> duts_;
public:
    DutContainer(EOPContainer const &);
    [[nodiscard]] double dut(double) const;
};

#endif //DUTCONTAINER_HPP
