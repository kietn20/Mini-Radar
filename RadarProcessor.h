#pragma once
#include <atomic>
#include "SafeQueue.h"
#include "Target.h"

class RadarProcessor
{
private:
    SafeQueue<std::unique_ptr<Target>> &queue;
    std::atomic<bool> &isRunning;

public:
    RadarProcessor(SafeQueue<std::unique_ptr<Target>> &q, std::atomic<bool> &run)
        : queue(q), isRunning(run) {}

    void run();
};