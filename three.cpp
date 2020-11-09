#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <condition_variable>

/* 
	a/ zozeniem si linter, ked bude nieco skaredo odsadene vyhovorim sa nan
    b/ 
    https://stackoverflow.com/questions/35252119/stdlock-guard-example-explanation-on-why-it-works
    The mutex is always the same one, it has nothing to do with the scope. The point of lock_guard is just to make locking and unlocking the mutex easier for you. 
    For example, if you manually lock/unlock, but your function throws an exception somewhere in the middle, it will never reach the unlock statement. 
    So, doing it the manual way you have to make sure that the mutex is always unlocked. 
    On the other hand, the lock_guard object gets destroyed automatically whenever the function is exited – regardless how it is exited.
*/

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
bool blocked = false;

std::mutex m;
std::condition_variable cv;

int generateSeconds() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(5, 10);
    return dist(mt);
}

void sleep(int sec) {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return blocked == true;});
    std::cout << "thread sleeps for " << sec << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(sec));
    cv.notify_one();
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