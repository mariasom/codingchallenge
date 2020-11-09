#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <condition_variable>

/*
 Use c++11 std::condition_signal in solution from #2 to synchronize threads
      -- Psuedo Code --
      main:
        1) start: thread 1, thread 2, thread 3
        2) all threads block on condition_signal
        3) main signals condition_signal  
        4) join all threads to prevent exit main // gimmee

        thread 1:
           break from condition_signal due to step 3
           sleep (random(1,5))
           signal thread 2
           wait on condition_signal

       example output:
         main: starting all threads
         thread1: starting, waiting.
         thread2: starting, waiting.
         thread3: starting, waiting.
         main: starting thread 1.
         thread1: signal received, doing work ....
         thread1: done with work, signal next thread
         thread2: signal received, doing work ....
         thread2: done with work, signal next thread

         on and on and on until you CTRL-C the program
*/
bool generating = true;
int seconds = 0;

std::mutex m;
std::condition_variable cv;

void generateSeconds() {
    generating = true;
    std::cout << "generating seconds" << std::endl;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(5, 10);
    seconds = dist(mt);
    generating = false;
    cv.notify_one();
}

void sleep() {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return generating == false && seconds != 0;});
    std::cout << "thread sleeps for " << seconds << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    lk.unlock();
    cv.notify_one();
}

int main() {
    std::thread one(generateSeconds);
    std::thread two(sleep);

    one.join();
    two.join();

    return 0;
}