#include <iostream>
#include <thread>
#include <atomic>
#include "SafeQueue.h"
#include "RadarGenerator.h"
#include "RadarProcessor.h"

int main()
{
    // Set a small buffer size (e.g., 3) to force the "Buffer Full" warning test
    SafeQueue<std::unique_ptr<Target>> radarQueue(3);
    std::atomic<bool> isRunning{true};

    RadarGenerator generator(radarQueue, isRunning);
    RadarProcessor processor(radarQueue, isRunning);

    std::cout << "--- Radar System Online (Buffered) ---" << std::endl;

    std::thread genThread(&RadarGenerator::run, &generator);
    std::thread procThread(&RadarProcessor::run, &processor);

    // Run for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "--- Shutting Down System ---" << std::endl;

    // 1. Tell threads to stop their loops
    isRunning = false;

    // 2. Wake up the processor if it's stuck waiting
    radarQueue.shutdown();

    // 3. Cleanly join threads
    if (genThread.joinable())
        genThread.join();
    if (procThread.joinable())
        procThread.join();

    std::cout << "--- System Offline ---" << std::endl;

    return 0;
}