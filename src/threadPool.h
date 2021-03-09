#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <queue>
#include <thread>
#include <iostream>
#include <array>
#include <mutex>
#include <condition_variable>

#include "serverSocket.h"

using namespace std::chrono_literals;

// Type to be stored in queue
template<typename T, size_t size>
class ThreadPool
{

private:
    std::array<std::thread, size> threads;
    std::queue<T> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
public:
    template<typename Fn>
    ThreadPool(Fn &function, ServerSocket& server)
    {
        auto work = [&]()
        {
            while (true)
            {
                T value;
                {
                    std::unique_lock<std::mutex> mutexLock(queueMutex);

                    if (tasks.size() <= 0) // No tasks available, suspend thread i.e wait on signal
                        condition.wait(mutexLock);
                    
                    if (tasks.size() <= 0) continue;

                    value = tasks.front();
                    tasks.pop();
                }
                function(value, server);
            }
        };

        for (int i = 0; i < size; i++)
            threads[i] = std::thread(work);
    }

    void addTask(const T& value)
    {
        std::unique_lock<std::mutex> mutexLock(queueMutex);
        tasks.push(value);
        condition.notify_one();
    }

};

#endif
