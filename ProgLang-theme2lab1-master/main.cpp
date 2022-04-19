#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "UserInterruptHandler.h"

void threadFunc()
{
}

int main()
{
    using namespace std::chrono_literals;
    UserInterruptHandler intHandler;
    std::thread t(threadFunc);
    // Первый способ проверки нажатия Ctrl+C
    while (!intHandler.checkInterruption())
    {
        std::this_thread::sleep_for(50ms);
    }
    // Второй способ проверки нажатия Ctrl+C
    try
    {
        while (1)
        {
            std::this_thread::sleep_for(50ms);
            intHandler.checkInterruptionAndThrow();
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << '\n';
    }

    if (t.joinable())
    {
        t.join();
    }

    return 0;
}
