#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr
#include "Aircraft.h"

int main()
{
    // We use a vector of unique_ptrs to the Base class.
    // This is the "Modern C++" way to handle polymorphism safely.
    std::vector<std::unique_ptr<Target>> radar_screen;

    // Adding different types to our collection
    radar_screen.push_back(std::make_unique<HostileJet>(101, 0.0, 0.0, 500.0));
    radar_screen.push_back(std::make_unique<Noise>(999, 10.0, 10.0, 0.0));

    std::cout << "--- Radar Scan Starting ---" << std::endl;

    for (const auto &t : radar_screen)
    {
        t->updatePosition();
        std::cout << "ID: " << t->getId()
                  << " | Type: " << t->getType()
                  << " | New Pos: (" << t->getX() << ", " << t->getY() << ")"
                  << std::endl;
    }

    return 0;
}