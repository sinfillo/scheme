#pragma once

#include <memory>
#include <string>
#include "error.h"

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
    virtual std::shared_ptr<Object> Set() {
        throw RuntimeError();
    }
    virtual std::shared_ptr<Object> Calculate() {
        throw RuntimeError();
    }
    virtual std::string ToStr() {
        throw RuntimeError();
    }
};

class Number : public Object {
public:
    Number(){};
    Number(const int64_t& value) : value_(value){};
    int64_t GetValue() const {
        return value_;
    }
    void SetValue(const int64_t& new_value) {
        value_ = new_value;
    }
    std::shared_ptr<Object> Set() override;
    std::shared_ptr<Object> Calculate() override {
        return shared_from_this();
    }
    std::string ToStr() override {
        return std::to_string(value_);
    }

private:
    int64_t value_;
};

class Symbol : public Object {
public:
    Symbol(){};
    Symbol(const std::string& name) : name_(name){};
    const std::string& GetName() const {
        return name_;
    }
    std::shared_ptr<Object> Calculate() override {
        return shared_from_this();
    }
    std::shared_ptr<Object> Set() override;
    std::string ToStr() override {
        return name_;
    }

private:
    std::string name_;
};

class Cell : public Object {
public:
    Cell(){};
    Cell(const std::shared_ptr<Object>& first, const std::shared_ptr<Object>& second)
        : first_(first), second_(second){};
    std::shared_ptr<Object> GetFirst() const {
        return first_;
    }
    std::shared_ptr<Object> GetSecond() const {
        return second_;
    }
    void SetFirst(std::shared_ptr<Object> first) {
        first_ = first;
    }
    void SetSecond(std::shared_ptr<Object> second) {
        second_ = second;
    }
    std::shared_ptr<Object> Set() override {
        throw RuntimeError();
    }
    std::shared_ptr<Object> Calculate() override;
    std::string ToStr() override;

private:
    std::shared_ptr<Object> first_, second_;
};

class Boolean : public Object {
public:
    Boolean(){};
    Boolean(const bool& value) : value_(value){};
    bool GetValue() const {
        return value_;
    }
    std::shared_ptr<Object> Set() override;
    std::shared_ptr<Object> Calculate() override {
        return shared_from_this();
    }
    std::string ToStr() override {
        if (value_) {
            return "#t";
        }
        return "#f";
    }

private:
    bool value_ = true;
};

class Func : public Object {
public:
    virtual ~Func() = default;
    virtual std::shared_ptr<Object> Apply([[maybe_unused]] std::shared_ptr<Object> ver) {
        throw RuntimeError();
    }
    /*virtual std::string ToStr() {
        throw RuntimeError();
    }*/
};

class DoPlus : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "+";
    }
};

class DoMinus : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "-";
    }
};

class DoMul : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "*";
    }
};

class DoDiv : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "/";
    }
};

class DoIntegerPredicate : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "number?";
    }
};

class DoEqual : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "=";
    }
};

class DoGreater : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return ">";
    }
};

class DoLess : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "<";
    }
};

class DoGreaterOrEqual : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return ">=";
    }
};

class DoLessOrEqual : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "<=";
    }
};

class DoMax : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "max";
    }
};

class DoMin : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "min";
    }
};

class DoAbs : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "abs";
    }
};

class DoBooleanPredicate : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "boolean?";
    }
};

class DoNot : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "not";
    }
};

class DoOr : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "or";
    }
};

class DoAnd : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "and";
    }
};

class DoQuote : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "quote";
    }
};

class DoPairPredicate : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "pair?";
    }
};

class DoNullPredicate : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "null?";
    }
};

class DoListPredicate : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "list?";
    }
};

class DoCons : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "cons";
    }
};

class DoCar : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "car";
    }
};

class DoCdr : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "cdr";
    }
};

class DoList : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "list";
    }
};

class DoListRef : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "list-ref";
    }
};

class DoListTail : public Func {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> ver) override;
    std::string ToStr() override {
        return "list-tail";
    }
};

///////////////////////////////////////////////////////////////////////////////

// Runtime type checking and convertion.
// This can be helpful: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T>(obj);
}

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return (std::dynamic_pointer_cast<T>(obj) != nullptr);
}
