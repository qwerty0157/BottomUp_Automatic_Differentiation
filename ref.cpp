#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <cmath>

using namespace std;

class Expr {
public:
    virtual ~Expr() {}
    virtual string tostr() const = 0;
    virtual string tostr2() const { return tostr(); }
    virtual shared_ptr<Expr> differentiate() const = 0;
    virtual shared_ptr<Expr> integrate() const = 0;
    virtual double eval() const = 0;
    shared_ptr<Expr> indefIntegrate() const;
};

class Num : public Expr {
    int n;
public:
    Num(int n) : n(n) {}
    virtual ~Num() {}
    virtual string tostr() const;
    virtual shared_ptr<Expr> differentiate() const;
    virtual shared_ptr<Expr> integrate() const;
    virtual double eval() const;
};

class Add : public Expr {
    shared_ptr<Expr> x, y;
public:
    Add(const shared_ptr<Expr> &x, const shared_ptr<Expr> &y) : x(x), y(y) {}
    virtual ~Add() {}
    virtual string tostr() const;
    virtual string tostr2() const { return "(" + tostr() + ")"; }
    virtual shared_ptr<Expr> differentiate() const;
    virtual shared_ptr<Expr> integrate() const;
    virtual double eval() const;
};

class Mul : public Expr {
    shared_ptr<Expr> x, y;
public:
    Mul(const shared_ptr<Expr> &x, const shared_ptr<Expr> &y) : x(x), y(y) {}
    virtual ~Mul() {}
    virtual string tostr() const;
    virtual shared_ptr<Expr> differentiate() const;
    virtual shared_ptr<Expr> integrate() const;
    virtual double eval() const;
};

class Div : public Expr {
    shared_ptr<Expr> x, y;
public:
    Div(const shared_ptr<Expr> &x, const shared_ptr<Expr> &y) : x(x), y(y) {}
    virtual ~Div() {}
    virtual string tostr() const;
    virtual shared_ptr<Expr> differentiate() const;
    virtual shared_ptr<Expr> integrate() const;
    virtual double eval() const;
};

class Var : public Expr {
    string name;
    int n;
public:
    Var(const string &name, int n) : name(name), n(n) {}
    virtual ~Var() {}
    virtual string tostr() const;
    virtual shared_ptr<Expr> differentiate() const;
    virtual shared_ptr<Expr> integrate() const;
    virtual double eval() const;
};

shared_ptr<Expr> num(int n) {
    return shared_ptr<Expr>(new Num(n));
}

shared_ptr<Expr> var(const string &name, int n) {
    return shared_ptr<Expr>(new Var(name, n));
}

shared_ptr<Expr> x(int n) { return var("x", n); }

shared_ptr<Expr> operator+(const shared_ptr<Expr> &x, int n) {
    return shared_ptr<Expr>(new Add(x, num(n)));
}

shared_ptr<Expr> operator+(const shared_ptr<Expr> &x, const shared_ptr<Expr> &y) {
    return shared_ptr<Expr>(new Add(x, y));
}

shared_ptr<Expr> operator*(const shared_ptr<Expr> &x, const shared_ptr<Expr> &y) {
    return shared_ptr<Expr>(new Mul(x, y));
}

shared_ptr<Expr> operator/(const shared_ptr<Expr> &x, const shared_ptr<Expr> &y) {
    return shared_ptr<Expr>(new Div(x, y));
}

string to_string(int n) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", n);
    return buf;
}

string Num::tostr() const { return to_string(n); }
string Add::tostr() const { return x->tostr () + "+" + y->tostr(); }
string Mul::tostr() const { return x->tostr2() + "*" + y->tostr2(); }
string Div::tostr() const { return x->tostr2() + "/" + y->tostr2(); }
string Var::tostr() const { return n == 1 ? name : name + "^" + to_string(n); }

shared_ptr<Expr> Num::differentiate() const { return num(0); }
shared_ptr<Expr> Add::differentiate() const { return x->differentiate() + y->differentiate(); }
shared_ptr<Expr> Mul::differentiate() const { return x * y->differentiate(); }
shared_ptr<Expr> Div::differentiate() const { return x->differentiate() / y; }
shared_ptr<Expr> Var::differentiate() const {
    if (name != "x") return num(0);
    return n == 1 ? num(1) : num(n) * x(n - 1);
}

shared_ptr<Expr> Num::integrate() const { return n == 1 ? x(1) : num(n) * x(1); }
shared_ptr<Expr> Add::integrate() const { return x->integrate() + y->integrate(); }
shared_ptr<Expr> Mul::integrate() const { return x * y->integrate(); }
shared_ptr<Expr> Div::integrate() const { return x->integrate() / y; }
shared_ptr<Expr> Var::integrate() const {
    if (name != "x") return var(name, n) * x(1);
    return x(n + 1) / num(n + 1);
}

shared_ptr<Expr> Expr::indefIntegrate() const {
    return integrate() + var("C", 1);
}

double Num::eval() const { return n; }
double Add::eval() const { return x->eval() + y->eval(); }
double Mul::eval() const { return x->eval() * y->eval(); }
double Div::eval() const { return x->eval() / y->eval(); }
double Var::eval() const { return NAN; }

int main() {
    auto f = x(3) + x(2) + x(1) + 1;
    auto f1 = f->differentiate();
    auto f2 = f->indefIntegrate();
    auto f3 = f2->differentiate();
    cout << "f1: d/dx " << f->tostr() << " = " << f1->tostr() << endl;
    cout << "f2: ∫ " << f->tostr() << " dx = " << f2->tostr() << endl;
    cout << "f3: d/dx f2 = " << f3->tostr() << endl;
}