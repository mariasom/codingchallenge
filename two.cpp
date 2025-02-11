#include <iostream>
#include <thread>
#include <chrono>
#include <random>

/*
    Implement c++11 threading example
    2-3 threads running
*/

int generateSeconds() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(5, 10);
    return dist(mt);
}

void sleep(int sec) {
    // std::cout << "thread sleeps for " << sec << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

int main() {
    std::thread one(sleep, generateSeconds());
    std::thread two(sleep, generateSeconds());
    std::thread three(sleep, generateSeconds());

    one.join();
    two.join();
    three.join();

    return 0;
}