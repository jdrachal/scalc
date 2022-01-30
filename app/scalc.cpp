#include <iostream>
#include <queue>
#include <stdexcept>
#include "../include/expression/expression.hpp"

int main(int argc, char *argv[]) {

    std::vector<std::string> args(argv + 1, argv + argc);

    try {
        expression::Expression ex;

        for (const auto &num: ex.evaluateExpression(args)) {
            std::cout << num << std::endl;
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}