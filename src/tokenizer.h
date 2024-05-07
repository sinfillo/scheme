#pragma once

#include <variant>
#include <optional>
#include <istream>

struct SymbolToken {
    SymbolToken(){};
    SymbolToken(const std::string& name) : name_(name){};

    bool operator==(const SymbolToken& other) const {
        return name_ == other.name_;
    }
    void AddSymbol(char sym) {
        name_ += sym;
    }
    std::string GetName() {
        return name_;
    }

private:
    std::string name_;
};

struct QuoteToken {
    QuoteToken(){};
    bool operator==(const QuoteToken&) const {
        return true;
    }
};

struct DotToken {
    DotToken(){};
    bool operator==(const DotToken&) const {
        return true;
    }
};

enum class BracketToken { OPEN, CLOSE };

struct ConstantToken {
    ConstantToken(){};
    ConstantToken(const int64_t& value) : value_(value){};
    bool operator==(const ConstantToken& other) const {
        return value_ == other.value_;
    }
    void AddDigit(int64_t digit) {
        if (value_ > 0) {
            value_ *= 10;
            value_ += digit;
        } else {
            value_ *= (-1);
            value_ *= 10;
            value_ += digit;
            value_ *= (-1);
        }
    }
    int64_t GetValue() {
        return value_;
    }

private:
    int64_t value_;
};

using Token = std::variant<ConstantToken, BracketToken, SymbolToken, QuoteToken, DotToken>;

class Tokenizer {
public:
    Tokenizer(std::istream* in);

    bool IsEnd();

    void Next();

    Token GetToken();

private:
    std::istream* in_;
    Token token_;
    std::optional<Token> ReadCurToken();
    bool IsStartSymbol(char sym);  // [a-zA-Z<=>*/#]
    bool IsOtherSymbol(char sym);  // [a-zA-Z<=>*/#0-9?!-]
    bool IsDigit(char sym);
    // bool end_ = false;
};