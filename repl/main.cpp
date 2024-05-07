#include "../src/scheme.h"

#include <exception>
#include <iostream>

int main() {
    Interpreter interpreter;
    std::string s;
    while (std::getline(std::cin, s)) {
        try {
            std::cout << interpreter.Run(s) << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        } catch (...) {
            std::cerr << "(" << std::endl;
        }
    }

    return 0;
}