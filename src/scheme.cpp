#include "scheme.h"

std::string Interpreter::Run(const std::string& str) {
    std::stringstream to_read{str};
    Tokenizer tokenizer(&to_read);
    std::shared_ptr<Object> ver = Read(&tokenizer);
    if (!tokenizer.IsEnd()) {
        throw SyntaxError();
    }
    if (ver == nullptr) {
        throw RuntimeError();
    }
    std::shared_ptr<Object> ans = ver->Calculate();
    if (ans == nullptr) {
        return "()";
    } else {
        return ans->ToStr();
    }
}
