#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include "LockGuard.h"

/*
    Use your implementation of c++11 lock_guard (NOT std::lock_guard)
    to protect a common resource in your threading example from #3 and #4
*/

std::mutex mut;

int generateSeconds() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(5, 10);
    return dist(mt);
}

void sleep(int sec) {
    codingChallenge::lock_guard l(mut);
    std::cout << "thread sleeps for " << sec << " seconds" << std::endl;
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