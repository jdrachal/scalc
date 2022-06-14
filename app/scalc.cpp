#include <iostream>
#include <queue>
#include <stdexcept>
#include <filesystem>
#include "../include/expression/expression.hpp"
#include "simpleevaluator.hpp"

//#define SIMPLE_EVALUATION 1

int main(int argc, char *argv[]) {

    std::vector<std::string> args(argv + 1, argv + argc);

    try {
        expression::Expression ex;
#ifdef SIMPLE_EVALUATION
        for (const auto &num: expression::evaluate(args)) {
            std::cout << num << std::endl;
        }
#else
        for (const auto &num: ex.evaluateExpression(args)) {
            std::cout << num << std::endl;
        }
#endif
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}