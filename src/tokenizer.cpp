#include "tokenizer.h"
#include "error.h"
#include <iostream>

Tokenizer::Tokenizer(std::istream* in) : in_(in) {
    std::optional<Token> maybe_token = ReadCurToken();
    if (maybe_token.has_value()) {
        token_ = maybe_token.value();
    }
}

bool Tokenizer::IsEnd() {
    Token end = Token(SymbolToken("\0"));
    return token_ == end;
}

void Tokenizer::Next() {
    std::optional<Token> maybe_token = ReadCurToken();
    if (!maybe_token.has_value()) {
        throw SyntaxError();
    } else {
        token_ = maybe_token.value();
    }
}

Token Tokenizer::GetToken() {
    Token end = Token(SymbolToken("\0"));
    if (token_ == end) {
        throw SyntaxError();
    }
    return token_;
}

bool Tokenizer::IsDigit(char sym) {
    return (sym >= '0' && sym <= '9');
}

bool Tokenizer::IsStartSymbol(char sym) {
    // [a-zA-Z<=>*/#]
    if (sym >= 'a' && sym <= 'z') {
        return true;
    }
    if (sym >= 'A' && sym <= 'Z') {
        return true;
    }
    if (sym == '<') {
        return true;
    }
    if (sym == '=') {
        return true;
    }
    if (sym == '>') {
        return true;
    }
    if (sym == '*') {
        return true;
    }
    if (sym == '/') {
        return true;
    }
    if (sym == '#') {
        return true;
    }
    return false;
}

bool Tokenizer::IsOtherSymbol(char sym) {
    // [a-zA-Z<=>*/#0-9?!-]
    if (IsStartSymbol(sym)) {
        return true;
    }
    if (IsDigit(sym)) {
        return true;
    }
    if (sym == '?') {
        return true;
    }
    if (sym == '!') {
        return true;
    }
    if (sym == '-') {
        return true;
    }
    return false;
}

std::optional<Token> Tokenizer::ReadCurToken() {
    Token ans = Token(SymbolToken("\0"));
    bool long_word = false;
    while (in_->peek() != EOF && (in_->peek() == ' ' || in_->peek() == '\n')) {
        in_->get();
    }
    while (in_->peek() != EOF) {
        if (!long_word) {
            char sym = in_->get();
            if (sym == '.') {
                ans = DotToken();
                break;
            }
            if (sym == '\'') {
                ans = QuoteToken();
                break;
            }
            if (sym == '(') {
                ans = BracketToken::OPEN;
                break;
            }
            if (sym == ')') {
                ans = BracketToken::CLOSE;
                break;
            }
            if (IsDigit(sym)) {
                ans = Token(ConstantToken(sym - '0'));
                long_word = true;
                continue;
            }
            if (sym == '+') {
                if (IsDigit(in_->peek())) {
                    char next_sym = in_->get();
                    ans = Token(ConstantToken(next_sym - '0'));
                    long_word = true;
                    continue;
                } else {
                    ans = Token(SymbolToken("+"));
                    break;
                }
            }
            if (sym == '-') {
                if (IsDigit(in_->peek())) {
                    char next_sym = in_->get();
                    ans = Token(ConstantToken(-1 * (next_sym - '0')));
                    long_word = true;
                    continue;
                } else {
                    ans = Token(SymbolToken("-"));
                    break;
                }
            }
            if (IsStartSymbol(sym)) {
                std::string to_add;
                to_add += sym;
                ans = Token(SymbolToken(to_add));
                long_word = true;
                continue;
            }
            return std::nullopt;
        } else {
            if (ConstantToken* constant_token = std::get_if<ConstantToken>(&ans)) {
                if (IsDigit(in_->peek())) {
                    char next_sym = in_->get();
                    int64_t cur_digit = next_sym - '0';
                    constant_token->AddDigit(cur_digit);
                } else {
                    break;
                }
            } else {
                SymbolToken* sym_token = std::get_if<SymbolToken>(&ans);
                if (IsOtherSymbol(in_->peek())) {
                    char next_sym = in_->get();
                    sym_token->AddSymbol(next_sym);
                } else {
                    break;
                }
            }
        }
    }
    return ans;
}
