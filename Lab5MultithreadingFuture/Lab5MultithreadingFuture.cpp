
#include <future>
#include <chrono>
#include <iostream>
#include <syncstream>

namespace lab5
{
    using namespace std::chrono_literals;
    
    void calculation(const std::string& name, const std::chrono::seconds& duration)
    {
        std::this_thread::sleep_for(duration);
        std::osyncstream(std::cout) << name << std::endl;
    }

    void thread1()
    {
        calculation("A1", 7s);
        calculation("A2", 1s);
    }

    void thread2()
    {
        calculation("B1", 1s);
        calculation("B2", 7s);
    }

    void work()
    {
        auto start = std::chrono::high_resolution_clock::now();

        auto th1 = std::async(std::launch::async, thread1);
        auto th2 = std::async(std::launch::async, thread2);

        calculation("C", 1s);
        calculation("F", 1s);

        th1.wait();
        th2.wait();
        calculation("D", 1s);

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

        std::cout << "Work done in: " << elapsed;
    }
}

int main(int argc, char* argv[])
{
    lab5::work();
    return 0;
}
