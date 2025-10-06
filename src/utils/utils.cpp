#include "Utils.hpp"

std::vector<std::string> splitByCr(const std::string& input) {
    std::vector<std::string>    result;
    std::istringstream          iss(input);
    std::string                 line;

    while (std::getline(iss, line, '\n')) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.resize(line.size() - 1);
        }
        result.push_back(line);
    }

    return result;
}