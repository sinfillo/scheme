#include "object.h"
#include <vector>
#include <cmath>

std::shared_ptr<Object> Number::Set() {
    return std::make_shared<Number>(value_);
}

std::shared_ptr<Object> Symbol::Set() {
    if (name_ == "+") {
        return std::make_shared<DoPlus>();  // do
    }
    if (name_ == "-") {
        return std::make_shared<DoMinus>();  // do
    }
    if (name_ == "*") {
        return std::make_shared<DoMul>();  // do
    }
    if (name_ == "/") {
        return std::make_shared<DoDiv>();  // do
    }
    if (name_ == "number?") {
        return std::make_shared<DoIntegerPredicate>();  // do
    }
    if (name_ == "=") {
        return std::make_shared<DoEqual>();  // do
    }
    if (name_ == "<") {
        return std::make_shared<DoLess>();  // do
    }
    if (name_ == ">") {
        return std::make_shared<DoGreater>();  // do
    }
    if (name_ == "<=") {
        return std::make_shared<DoLessOrEqual>();  // do
    }
    if (name_ == ">=") {
        return std::make_shared<DoGreaterOrEqual>();  // do
    }
    if (name_ == "max") {
        return std::make_shared<DoMax>();  // do
    }
    if (name_ == "min") {
        return std::make_shared<DoMin>();  // do
    }
    if (name_ == "abs") {
        return std::make_shared<DoAbs>();  // do
    }
    if (name_ == "boolean?") {
        return std::make_shared<DoBooleanPredicate>();  // do
    }
    if (name_ == "not") {
        return std::make_shared<DoNot>();  // do
    }
    if (name_ == "or") {
        return std::make_shared<DoOr>();  // do
    }
    if (name_ == "and") {
        return std::make_shared<DoAnd>();  // do
    }
    if (name_ == "quote") {
        return std::make_shared<DoQuote>();  // do
    }
    if (name_ == "pair?") {
        return std::make_shared<DoPairPredicate>();  // do
    }
    if (name_ == "null?") {
        return std::make_shared<DoNullPredicate>();  // do
    }
    if (name_ == "list?") {
        return std::make_shared<DoListPredicate>();  // do
    }
    if (name_ == "cons") {
        return std::make_shared<DoCons>();  // do
    }
    if (name_ == "car") {
        return std::make_shared<DoCar>();  // do
    }
    if (name_ == "cdr") {
        return std::make_shared<DoCdr>();  // do
    }
    if (name_ == "list") {
        return std::make_shared<DoList>();  // do
    }
    if (name_ == "list-ref") {
        return std::make_shared<DoListRef>();  // do
    }
    if (name_ == "list-tail") {
        return std::make_shared<DoListTail>();  // do
    }
    if (name_ == "#t") {
        return std::make_shared<Boolean>(true);  // do
    }
    if (name_ == "#f") {
        return std::make_shared<Boolean>(false);  // do
    }
    return std::make_shared<Symbol>(name_);
}

std::shared_ptr<Object> Boolean::Set() {
    return std::make_shared<Boolean>(value_);
}

std::vector<std::shared_ptr<Object>> GetVector(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> ans;
    if (ver == nullptr) {
        return ans;
    }
    while (true) {
        if (Is<Cell>(ver)) {
            ans.push_back(As<Cell>(ver)->GetFirst());
            if (As<Cell>(ver)->GetSecond() == nullptr) {
                return ans;
            }
            ver = As<Cell>(ver)->GetSecond();
        } else {
            ans.push_back(ver);
            return ans;
        }
    }
}

std::shared_ptr<Object> DoPlus::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    std::shared_ptr<Number> ans = std::make_shared<Number>(0);
    for (const auto& elem : cur_vec) {
        if (elem == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        std::shared_ptr<Object> calc = elem->Calculate();
        if (Is<Number>(calc)) {
            ans->SetValue(ans->GetValue() + As<Number>(calc)->GetValue());
        } else {
            throw RuntimeError("Expected number");
        }
    }
    return ans;
}

std::shared_ptr<Object> DoMinus::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        throw RuntimeError("No arguments");
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    if (!Is<Number>(calc)) {
        throw RuntimeError("Expected number");
    }
    if (cur_vec.size() == 1) {
        return calc;
    }
    std::shared_ptr<Number> ans = std::make_shared<Number>(As<Number>(calc)->GetValue());
    bool flag = true;
    for (const auto& elem : cur_vec) {
        if (flag) {
            flag = false;
            continue;
        }
        if (elem == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc = elem->Calculate();
        if (Is<Number>(calc)) {
            ans->SetValue(ans->GetValue() - As<Number>(calc)->GetValue());
        } else {
            throw RuntimeError("Expected number");
        }
    }
    return ans;
}

std::shared_ptr<Object> DoMul::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    std::shared_ptr<Number> ans = std::make_shared<Number>(1);
    for (const auto& elem : cur_vec) {
        if (elem == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        std::shared_ptr<Object> calc = elem->Calculate();
        if (Is<Number>(calc)) {
            ans->SetValue(ans->GetValue() * As<Number>(calc)->GetValue());
        } else {
            throw RuntimeError("Expected number");
        }
    }
    return ans;
}

std::shared_ptr<Object> DoDiv::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        throw RuntimeError("No arguments");
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    if (!Is<Number>(calc)) {
        throw RuntimeError("Expected number");
    }
    if (cur_vec.size() == 1) {
        return calc;
    }
    std::shared_ptr<Number> ans = std::make_shared<Number>(As<Number>(calc)->GetValue());
    bool flag = true;
    for (const auto& elem : cur_vec) {
        if (flag) {
            flag = false;
            continue;
        }
        if (elem == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc = elem->Calculate();
        if (Is<Number>(calc)) {
            ans->SetValue(ans->GetValue() / As<Number>(calc)->GetValue());
        } else {
            throw RuntimeError("Expected number");
        }
    }
    return ans;
}

std::shared_ptr<Object> DoAbs::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        throw RuntimeError("No arguments");
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    if (!Is<Number>(calc)) {
        throw RuntimeError("Expected number");
    }
    if (cur_vec.size() > 1) {
        throw RuntimeError("Expected 1 argument");
    }
    std::shared_ptr<Number> ans = std::make_shared<Number>(std::abs(As<Number>(calc)->GetValue()));
    return ans;
}

std::shared_ptr<Object> DoMax::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        throw RuntimeError("No arguments");
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    if (!Is<Number>(calc)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Number> ans = std::make_shared<Number>(As<Number>(calc)->GetValue());
    bool flag = true;
    for (const auto& elem : cur_vec) {
        if (flag) {
            flag = false;
            continue;
        }
        if (elem == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc = elem->Calculate();
        if (Is<Number>(calc)) {
            ans->SetValue(std::max(ans->GetValue(), As<Number>(calc)->GetValue()));
        } else {
            throw RuntimeError("Expected number");
        }
    }
    return ans;
}

std::shared_ptr<Object> DoMin::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        throw RuntimeError("No arguments");
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    if (!Is<Number>(calc)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Number> ans = std::make_shared<Number>(As<Number>(calc)->GetValue());
    bool flag = true;
    for (const auto& elem : cur_vec) {
        if (flag) {
            flag = false;
            continue;
        }
        if (elem == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc = elem->Calculate();
        if (Is<Number>(calc)) {
            ans->SetValue(std::min(ans->GetValue(), As<Number>(calc)->GetValue()));
        } else {
            throw RuntimeError("Expected number");
        }
    }
    return ans;
}

std::shared_ptr<Object> DoNot::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        throw RuntimeError("No arguments");
    }
    if (cur_vec.size() > 1) {
        throw RuntimeError("Expected 1 argument");
    }
    if (cur_vec[0] == nullptr) {
        return std::make_shared<Boolean>(false);
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    if (Is<Boolean>(calc) && !As<Boolean>(calc)->GetValue()) {
        return std::make_shared<Boolean>(true);
    }
    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> DoEqual::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(true);
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc1 = cur_vec[0]->Calculate();
    if (!Is<Number>(calc1)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> calc2;
    for (size_t i = 1; i < cur_vec.size(); ++i) {
        if (cur_vec[i] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc2 = cur_vec[i]->Calculate();
        if (!Is<Number>(calc2)) {
            throw RuntimeError("Expected number");
        }
        if (As<Number>(calc1)->GetValue() != As<Number>(calc2)->GetValue()) {
            return std::make_shared<Boolean>(false);
        }
        calc1 = calc2;
    }
    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> DoLess::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(true);
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc1 = cur_vec[0]->Calculate();
    if (!Is<Number>(calc1)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> calc2;
    for (size_t i = 1; i < cur_vec.size(); ++i) {
        if (cur_vec[i] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc2 = cur_vec[i]->Calculate();
        if (!Is<Number>(calc2)) {
            throw RuntimeError("Expected number");
        }
        if (As<Number>(calc1)->GetValue() >= As<Number>(calc2)->GetValue()) {
            return std::make_shared<Boolean>(false);
        }
        calc1 = calc2;
    }
    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> DoGreater::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(true);
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc1 = cur_vec[0]->Calculate();
    if (!Is<Number>(calc1)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> calc2;
    for (size_t i = 1; i < cur_vec.size(); ++i) {
        if (cur_vec[i] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc2 = cur_vec[i]->Calculate();
        if (!Is<Number>(calc2)) {
            throw RuntimeError("Expected number");
        }
        if (As<Number>(calc1)->GetValue() <= As<Number>(calc2)->GetValue()) {
            return std::make_shared<Boolean>(false);
        }
        calc1 = calc2;
    }
    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> DoLessOrEqual::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(true);
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc1 = cur_vec[0]->Calculate();
    if (!Is<Number>(calc1)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> calc2;
    for (size_t i = 1; i < cur_vec.size(); ++i) {
        if (cur_vec[i] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc2 = cur_vec[i]->Calculate();
        if (!Is<Number>(calc2)) {
            throw RuntimeError("Expected number");
        }
        if (As<Number>(calc1)->GetValue() > As<Number>(calc2)->GetValue()) {
            return std::make_shared<Boolean>(false);
        }
        calc1 = calc2;
    }
    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> DoGreaterOrEqual::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(true);
    }
    if (cur_vec[0] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> calc1 = cur_vec[0]->Calculate();
    if (!Is<Number>(calc1)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> calc2;
    for (size_t i = 1; i < cur_vec.size(); ++i) {
        if (cur_vec[i] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        calc2 = cur_vec[i]->Calculate();
        if (!Is<Number>(calc2)) {
            throw RuntimeError("Expected number");
        }
        if (As<Number>(calc1)->GetValue() < As<Number>(calc2)->GetValue()) {
            return std::make_shared<Boolean>(false);
        }
        calc1 = calc2;
    }
    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> DoIntegerPredicate::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() != 1) {
        throw RuntimeError("Expected 1 argument");
    }
    if (cur_vec[0] == nullptr) {
        return std::make_shared<Boolean>(false);
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    return std::make_shared<Boolean>(Is<Number>(calc));
}

std::shared_ptr<Object> DoBooleanPredicate::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() != 1) {
        throw RuntimeError("Expected 1 argument");
    }
    if (cur_vec[0] == nullptr) {
        return std::make_shared<Boolean>(false);
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    return std::make_shared<Boolean>(Is<Boolean>(calc));
}

std::shared_ptr<Object> DoOr::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(false);
    }
    std::shared_ptr<Object> calc;
    for (const auto& elem : cur_vec) {
        if (elem == nullptr) {
            return elem;
        }
        calc = elem->Calculate();
        if (Is<Boolean>(calc) && As<Boolean>(calc)->GetValue()) {
            return calc;
        }
    }
    return calc;
}

std::shared_ptr<Object> DoAnd::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() < 2) {
        return std::make_shared<Boolean>(true);
    }
    std::shared_ptr<Object> calc;
    for (const auto& elem : cur_vec) {
        if (elem == nullptr) {
            return std::make_shared<Boolean>(false);
        }
        calc = elem->Calculate();
        if (Is<Boolean>(calc) && !As<Boolean>(calc)->GetValue()) {
            return calc;
        }
    }
    return calc;
}

std::shared_ptr<Object> DoQuote::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() == 1) {
        return cur_vec[0];
    }
    throw RuntimeError("Expected 1 argument");
}

std::shared_ptr<Object> DoPairPredicate::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() == 1) {
        if (cur_vec[0] == nullptr) {
            return std::make_shared<Boolean>(false);
        }
        return std::make_shared<Boolean>(Is<Cell>(cur_vec[0]->Calculate()));
    }
    throw RuntimeError("Expected 1 argument");
}

std::shared_ptr<Object> DoNullPredicate::Apply(std::shared_ptr<Object> ver) {
    if (ver == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    if (As<Cell>(ver)->GetSecond() != nullptr) {
        throw RuntimeError("This is not a cell");
    }
    if (As<Cell>(ver)->GetFirst() == nullptr) {
        return std::make_shared<Boolean>(true);
    }
    std::shared_ptr<Object> calc = As<Cell>(ver)->GetFirst()->Calculate();
    if (calc == nullptr) {
        return std::make_shared<Boolean>(true);
    }
    return std::make_shared<Boolean>(false);
}

static bool IsList(std::shared_ptr<Object> cur) {
    if (cur == nullptr) {
        return true;
    }
    if (!Is<Cell>(cur)) {
        return false;
    }
    return IsList(As<Cell>(cur)->GetSecond());
}

std::shared_ptr<Object> DoListPredicate::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() != 1) {
        throw RuntimeError("Expected 1 argument");
    }
    if (cur_vec[0] == nullptr) {
        return std::make_shared<Boolean>(true);
    }
    std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
    return std::make_shared<Boolean>(IsList(calc));
}

std::shared_ptr<Object> DoCons::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() != 2) {
        throw RuntimeError("Expected 2 arguments");
    }
    std::shared_ptr<Object> first = nullptr;
    if (cur_vec[0] != nullptr) {
        first = cur_vec[0]->Calculate();
    }
    std::shared_ptr<Object> second = nullptr;
    if (cur_vec[1] != nullptr) {
        second = cur_vec[1]->Calculate();
    }
    return std::make_shared<Cell>(first, second);
}

std::shared_ptr<Object> DoCar::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() == 1) {
        if (cur_vec[0] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
        if (!Is<Cell>(calc)) {
            throw RuntimeError("This is not a cell");
        }
        return As<Cell>(calc)->GetFirst();
    }
    throw RuntimeError("Expected 1 argument");
}

std::shared_ptr<Object> DoCdr::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() == 1) {
        if (cur_vec[0] == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        std::shared_ptr<Object> calc = cur_vec[0]->Calculate();
        if (!Is<Cell>(calc)) {
            throw RuntimeError("This is not a cell");
        }
        return As<Cell>(calc)->GetSecond();
    }
    throw RuntimeError("Expected 1 argument");
}

std::shared_ptr<Object> DoList::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.empty()) {
        return nullptr;
    }
    std::shared_ptr<Cell> ans = std::make_shared<Cell>(nullptr, nullptr);
    std::shared_ptr<Cell> ptr = ans;
    for (size_t i = 0; i < cur_vec.size(); ++i) {
        std::shared_ptr<Object> elem = cur_vec[i];
        if (elem == nullptr) {
            ptr->SetFirst(nullptr);
        } else {
            ptr->SetFirst(elem->Calculate());
        }
        if (i != cur_vec.size() - 1) {
            ptr->SetSecond(std::make_shared<Cell>(nullptr, nullptr));
            ptr = As<Cell>(ptr->GetSecond());
        } else {
            ptr->SetSecond(nullptr);
        }
    }

    return ans;
}

std::shared_ptr<Object> DoListRef::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() != 2) {
        throw RuntimeError("Expected 2 arguments");
    }
    if (cur_vec[1] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> index = cur_vec[1]->Calculate();
    if (!Is<Number>(index)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> list = cur_vec[0]->Calculate();
    if (list == nullptr) {
        throw RuntimeError("Expected list");
    }
    if (!Is<Cell>(list)) {
        throw RuntimeError("This is not a cell");
    }
    for (size_t i = 0; i < static_cast<size_t>(As<Number>(index)->GetValue()); ++i) {
        if (list == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        list = As<Cell>(list)->GetSecond();
    }
    if (list == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    return As<Cell>(list)->GetFirst();
}

std::shared_ptr<Object> DoListTail::Apply(std::shared_ptr<Object> ver) {
    std::vector<std::shared_ptr<Object>> cur_vec = GetVector(ver);
    if (cur_vec.size() != 2) {
        throw RuntimeError("Expected 2 arguments");
    }
    if (cur_vec[1] == nullptr) {
        throw RuntimeError("Unable to calculate object");
    }
    std::shared_ptr<Object> index = cur_vec[1]->Calculate();
    if (!Is<Number>(index)) {
        throw RuntimeError("Expected number");
    }
    std::shared_ptr<Object> list = cur_vec[0]->Calculate();
    if (list == nullptr) {
        throw RuntimeError("Expected list");
    }
    if (!Is<Cell>(list)) {
        throw RuntimeError("This is not a cell");
    }
    for (size_t i = 0; i < static_cast<size_t>(As<Number>(index)->GetValue()); ++i) {
        if (list == nullptr) {
            throw RuntimeError("Unable to calculate object");
        }
        list = As<Cell>(list)->GetSecond();
    }
    return list;
}

std::shared_ptr<Object> Cell::Calculate() {
    if (first_ == nullptr) {
        throw RuntimeError("Missing function");
    }
    if (!Is<Func>(first_->Set())) {
        throw RuntimeError("Expected function");
    }
    return As<Func>(first_->Set())->Apply(second_);
}

std::string Cell::ToStr() {
    std::string ans;
    ans += "(";
    std::shared_ptr<Object> ptr = shared_from_this();
    while (Is<Cell>(As<Cell>(ptr)->GetSecond())) {
        if (As<Cell>(ptr)->GetFirst() == nullptr) {
            ans += "()";
        } else {
            ans += As<Cell>(ptr)->GetFirst()->ToStr();
        }
        ans += " ";
        ptr = As<Cell>(ptr)->GetSecond();
    }
    if (As<Cell>(ptr)->GetSecond() == nullptr) {
        // ans.pop_back();
        if (As<Cell>(ptr)->GetFirst() == nullptr) {
            ans += "()";
        } else {
            ans += As<Cell>(ptr)->GetFirst()->ToStr();
        }
        ans += ")";
    } else {
        if (As<Cell>(ptr)->GetFirst() == nullptr) {
            ans += "()";
        } else {
            ans += As<Cell>(ptr)->GetFirst()->ToStr();
        }
        ans += " ";
        ans += ".";
        ans += " ";
        if (As<Cell>(ptr)->GetSecond() == nullptr) {
            ans += "()";
        } else {
            ans += As<Cell>(ptr)->GetSecond()->ToStr();
        }
        ans += ")";
    }
    return ans;
}
