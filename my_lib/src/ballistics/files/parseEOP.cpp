#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <cstdint>
#include "parseEOP.hpp"
#include "ballistics/exceptions/BallisticsException.hpp"

using ByteStream = std::string_view;
using u32 = std::uint32_t;

template <typename T>
struct ParseResultBody
{
    T value;
    ByteStream tail;
};

template <typename T>
using ParseResult = std::optional<ParseResultBody<T>>;

ParseResult<std::string_view> parseBeforeString(ByteStream const stream, std::string_view const str)
{
    auto const pos = stream.find(str);
    if (std::string_view::npos == pos) {
        return std::nullopt;
    }
    return ParseResultBody<std::string_view>{str, stream.substr(pos + str.size())};
}

ParseResult<double> parseDouble(ByteStream const stream)
{
    char *end;
    double const d = std::strtod(stream.data(), &end);
    auto const N = static_cast<std::size_t>(end - stream.data());
    if (N == static_cast<std::size_t>(0)) {
        return std::nullopt;
    }
    return ParseResultBody<double>{d, {end, stream.size() - N}};
}

ParseResult<double> parseCoeff(ByteStream const stream)
{
    char *end;
    double const d = std::strtod(stream.data(), &end);
    auto const N = static_cast<std::size_t>(end - stream.data());
    std::string_view doublestr = stream.substr(0, N);
    if (doublestr.find('E') == std::string_view::npos || N == static_cast<std::size_t>(0)) {
        return std::nullopt;
    }
    return ParseResultBody<double>{d, {end, stream.size() - N}};
}

template <typename P>
auto parseVector(ByteStream stream, P const &parser)
{
    using T = decltype(parser(stream)->value);
    std::vector<T> v;
    while (true) {
        auto const opt = parser(stream);
        if (!opt) {
            return std::optional{ParseResultBody<std::vector<T>>{v, stream}};
        }
        v.push_back(opt->value);
        stream = opt->tail;
    }
}

std::string readFile(std::ifstream const &in)
{
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

EOPContainer parseEOP(std::ifstream const &eopFile)
{
    std::string const stream = readFile(eopFile);
    auto const optDataStart = parseBeforeString(stream, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    if (!optDataStart || optDataStart->tail.empty()) {
        throw BallisticsException("Cannot find beginning of the data! ---... should be");
    }
    auto const optV = parseVector(optDataStart->tail, parseDouble);
    if (!optV) {
        throw BallisticsException("Cannot parse data!");
    }
    std::vector<std::vector<double>> fieldEOP(6);
    for (u32 line = 0; line < static_cast<u32>(optV->value.size() / 16); ++line)
    {
        fieldEOP[0].push_back(optV->value[line * 16 + 3]);
        fieldEOP[1].push_back(optV->value[line * 16 + 6]);
        fieldEOP[2].push_back(optV->value[line * 16 + 4]);
        fieldEOP[3].push_back(optV->value[line * 16 + 5]);
        fieldEOP[4].push_back(optV->value[line * 16 + 8]);
        fieldEOP[5].push_back(optV->value[line * 16 + 9]);
    }
    return EOPContainer{fieldEOP[0], fieldEOP[1], fieldEOP[2], fieldEOP[3], fieldEOP[4], fieldEOP[5]};
}

EOPContainer parseEOP(std::filesystem::path const &path)
{
    if (!std::filesystem::exists(path)) {
        throw BallisticsException("Unable to open EOP file!");
    }
    std::ifstream const file(path);
    return parseEOP(file);
}