#include <iostream>
#include <thread>
#include "SafeQueue.h"

void producer(SafeQueue<int> &q)
{
    for (int i = 1; i <= 5; ++i)
    {
        std::cout << "[Producer] Generating Signal: " << i << std::endl;
        q.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer(SafeQueue<int> &q)
{
    for (int i = 1; i <= 5; ++i)
    {
        int val = q.pop();
        std::cout << "[Consumer] Processed Signal: " << val << std::endl;
    }
}

int main()
{
    SafeQueue<int> radarSignalQueue;

    std::cout << "--- Starting Multi-threaded Communication Test ---" << std::endl;

    // Launch two threads
    std::thread producerThread(producer, std::ref(radarSignalQueue));
    std::thread consumerThread(consumer, std::ref(radarSignalQueue));

    // Wait for both threads to finish
    producerThread.join();
    consumerThread.join();

    std::cout << "--- Test Complete ---" << std::endl;

    return 0;
}