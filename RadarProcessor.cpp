#include "RadarProcessor.h"
#include <iostream>
#include <thread>

void RadarProcessor::run()
{
    while (isRunning)
    {
        std::unique_ptr<Target> target;

        // Pass the target pointer by reference to be filled
        if (queue.pop(target))
        {
            // Success: We got data
            if (target->getType() == "Noise")
            {
                // std::cout << "[Processor] Filtered Noise" << std::endl; // Optional: lessen clutter
            }
            else
            {
                target->updatePosition();
                std::cout << "[Processor] Tracking " << target->getType()
                          << " [ID: " << target->getId()
                          << "] at Pos: (" << target->getX() << ", " << target->getY() << ")" << std::endl;
            }
        }
        else
        {
            // Failure: Queue was shut down
            std::cout << "[Processor] Queue shutdown signal received. Exiting." << std::endl;
            break;
        }

        // std::cout << "..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}