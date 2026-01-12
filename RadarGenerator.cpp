#include "RadarGenerator.h"
#include <chrono>
#include <iostream>

void RadarGenerator::run()
{
    int idCounter = 1;
    std::uniform_int_distribution<int> dist(0, 2); // To pick target type

    while (isRunning)
    {
        std::unique_ptr<Target> newTarget;
        int choice = dist(rng);

        if (choice == 0)
            newTarget = std::make_unique<HostileJet>(idCounter++, 0, 0, 100.0);
        else if (choice == 1)
            newTarget = std::make_unique<FriendlyHelicopter>(idCounter++, 0, 0, 20.0);
        else
            newTarget = std::make_unique<Noise>(idCounter++, 0, 0, 0);

        std::cout << "[Generator] Created: " << newTarget->getType() << std::endl;

        // Pass ownership to the queue
        queue.push(std::move(newTarget));

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}