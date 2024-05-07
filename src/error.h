#pragma once

#include <stdexcept>

struct SyntaxError : public std::runtime_error {
    SyntaxError() : std::runtime_error("Wtf"){};
    SyntaxError(const std::string& error_text) : std::runtime_error(error_text){};
    
    // using std::runtime_error::runtime_error;
};

struct RuntimeError : public std::runtime_error {
    RuntimeError() : std::runtime_error("lol re"){};
    RuntimeError(const std::string& error_text) : std::runtime_error(error_text){};
    // using std::runtime_error::runtime_error;
};

struct NameError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
