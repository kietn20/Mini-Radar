#pragma once
#include "Target.h"

class HostileJet : public Target
{
public:
    using Target::Target;
    void updatePosition() override
    {
        x += speed;
        y += speed;
    }
    std::string getType() const override { return "Hostile Jet"; }
};

class FriendlyHelicopter : public Target
{
public:
    using Target::Target;
    void updatePosition() override
    {
        x += speed * 0.2;
        y += speed * 0.1;
    }
    std::string getType() const override { return "Friendly Heli"; }
};

class Noise : public Target
{
public:
    using Target::Target;
    void updatePosition() override { /* Noise doesn't move logically */ }
    std::string getType() const override { return "Noise"; }
};