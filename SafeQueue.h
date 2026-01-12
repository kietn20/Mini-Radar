#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue
{
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    // Add an item to the queue
    void push(T value)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(std::move(value));
        } // Lock is released here when lock_guard goes out of scope
        cv.notify_one(); // Wake up one waiting thread
    }

    // Get an item from the queue (waits if empty)
    T pop()
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the queue is not empty.
        // The lambda []{ return !queue.empty(); } prevents "Spurious Wakeups"
        cv.wait(lock, [this]
                { return !queue.empty(); });

        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    bool isEmpty()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }
};