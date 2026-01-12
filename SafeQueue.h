#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

template <typename T>
class SafeQueue
{
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    size_t maxSize;
    bool active; // Shutdown flag

public:
    // Constructor with default max size
    SafeQueue(size_t size = 10) : maxSize(size), active(true) {}

    void push(T value)
    {
        std::lock_guard<std::mutex> lock(mtx);

        // BUFFER OVERFLOW PROTECTION
        // If queue is full, drop the oldest data to make room
        if (queue.size() >= maxSize)
        {
            std::cout << "[SafeQueue] Warning: Buffer Full! Dropping old data." << std::endl;
            queue.pop(); // Remove oldest
        }

        queue.push(std::move(value));
        cv.notify_one();
    }

    // Returns true if value popped, false if queue was shutdown
    bool pop(T &value)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until queue has data OR system is shutting down
        cv.wait(lock, [this]
                { return !queue.empty() || !active; });

        // If we woke up because of shutdown and queue is empty, return false
        if (!active && queue.empty())
        {
            return false;
        }

        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    // Signal all threads to stop waiting
    void shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            active = false;
        }
        cv.notify_all(); // Wake up everyone
    }
};