#include "parser.h"
#include "error.h"
#include "tokenizer.h"

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    Token cur = tokenizer->GetToken();
    if (tokenizer->IsEnd()) {
        throw SyntaxError("End symbol detected");
    }
    tokenizer->Next();
    if (SymbolToken* sym_token = std::get_if<SymbolToken>(&cur)) {
        if (sym_token->GetName() == "#t") {
            return std::make_shared<Boolean>(true);
        }
        if (sym_token->GetName() == "#f") {
            return std::make_shared<Boolean>(false);
        }
        return std::make_shared<Symbol>(sym_token->GetName());
    }
    if (ConstantToken* constant_token = std::get_if<ConstantToken>(&cur)) {
        return std::make_shared<Number>(constant_token->GetValue())->Set();
    }
    if (DotToken* dot_token = std::get_if<DotToken>(&cur)) {
        throw SyntaxError("Dot symbol detected");
    }
    if (QuoteToken* quote_token = std::get_if<QuoteToken>(&cur)) {
        return std::make_shared<Cell>(std::make_shared<Symbol>("quote"),
                                      std::make_shared<Cell>(Read(tokenizer), nullptr));
    }
    if (BracketToken* bracket_token = std::get_if<BracketToken>(&cur)) {
        if (*bracket_token == BracketToken::CLOSE) {
            throw SyntaxError("Expected open bracket but found close bracket");
        }
        std::shared_ptr<Object> to_ret = ReadList(tokenizer);
        return to_ret;
    }

    throw SyntaxError("Failed to read token");
}

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    Token cur = tokenizer->GetToken();
    if (BracketToken* bracket_token = std::get_if<BracketToken>(&cur)) {
        if (*bracket_token == BracketToken::CLOSE) {
            tokenizer->Next();
            return nullptr;
        }
    }
    std::shared_ptr<Object> first = Read(tokenizer);
    if (tokenizer->IsEnd()) {
        throw SyntaxError("End symbol detected");
    }
    cur = tokenizer->GetToken();
    if (std::get_if<SymbolToken>(&cur) || std::get_if<ConstantToken>(&cur) ||
        std::get_if<BracketToken>(&cur) || std::get_if<QuoteToken>(&cur)) {
        std::shared_ptr<Object> second = ReadList(tokenizer);
        return std::make_shared<Cell>(first, second);
    }
    if (DotToken* dot_token = std::get_if<DotToken>(&cur)) {
        tokenizer->Next();
        std::shared_ptr<Object> second = Read(tokenizer);
        if (tokenizer->IsEnd()) {
            throw SyntaxError("End symbol detected");
        }
        Token check_bracket = tokenizer->GetToken();
        if (BracketToken* bracket_token = std::get_if<BracketToken>(&check_bracket)) {
            if (*bracket_token == BracketToken::CLOSE) {
                tokenizer->Next();
                return std::make_shared<Cell>(first, second);
            }
        }
    }

    throw SyntaxError("Failed to read list token");
}
