#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

class BallisticsException final : public std::exception {
    std::string message_;

public:
    explicit BallisticsException(std::string const&message);
    explicit BallisticsException(char const *message);
    [[nodiscard]] const char *what() const noexcept override;
};

#endif //EXCEPTION_HPP
