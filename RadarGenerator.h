#pragma once
#include <thread>
#include <atomic>
#include <random>
#include "SafeQueue.h"
#include "Aircraft.h"

class RadarGenerator
{
private:
    SafeQueue<std::unique_ptr<Target>> &queue;
    std::atomic<bool> &isRunning;
    std::mt19937 rng{std::random_device{}()};

public:
    RadarGenerator(SafeQueue<std::unique_ptr<Target>> &q, std::atomic<bool> &run)
        : queue(q), isRunning(run) {}

    void run();
};