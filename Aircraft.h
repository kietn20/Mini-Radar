#pragma once
#include "Target.h"
#include <iostream>

class HostileJet : public Target
{
public:
    using Target::Target; // Inherit the constructor

    void updatePosition() override
    {
        x += speed * 2.0; // Jets move fast
        y += speed * 1.5;
    }

    std::string getType() const override { return "Hostile Jet"; }
};

class Noise : public Target
{
public:
    using Target::Target;

    void updatePosition() override
    {
        // Random erratic movement
        x += (rand() % 10 - 5) * 0.1;
        y += (rand() % 10 - 5) * 0.1;
    }

    std::string getType() const override { return "Atmospheric Noise"; }
};