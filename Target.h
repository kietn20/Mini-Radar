#pragma once
#include <string>

class Target
{
protected:
    int id;
    double x, y;
    double speed;

public:
    Target(int id, double x, double y, double speed)
        : id(id), x(x), y(y), speed(speed) {}

    // Virtual destructor is mandatory for polymorphism
    virtual ~Target() = default;

    // Pure virtual functions: Derived classes MUST implement these
    virtual void updatePosition() = 0;
    virtual std::string getType() const = 0;

    // Const-correct getters
    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
};