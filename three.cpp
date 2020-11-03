//  Use c++11 std::condition_signal in solution from #2 to synchronize threads
//       -- Psuedo Code --
//       main:
//         1) start: thread 1, thread 2, thread 3
//         2) all threads block on condition_signal
//         3) main signals condition_signal
//         4) join all threads to prevent exit main // gimmee

//         thread 1:
//            break from condition_signal due to step 3
//            sleep (random(1,5))
//            signal thread 2
//            wait on condition_signal

//        example output:
//          main: starting all threads
//          thread1: starting, waiting.
//          thread2: starting, waiting.
//          thread3: starting, waiting.
//          main: starting thread 1.
//          thread1: signal received, doing work ....
//          thread1: done with work, signal next thread
//          thread2: signal received, doing work ....
//          thread2: done with work, signal next thread

//          on and on and on until you CTRL-C the program
#include<iostream> 
#include<thread>
#include<vector>
#include<mutex>
#include<condition_variable>
#include<stdlib.h>     
#include<time.h>       

int sum = 0;
bool count = false;
std::mutex m;
std::condition_variable cv;

void multiply(std::vector<int> row, std::vector<int> v ) {
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, []{return count = true;});
    int result = 0; 
    if (row.size() == v.size()) {
        for(int i = 0; i < row.size(); i++) 
            result += row[i]*v[i]; 
    std::cout << "vector:" << result << std::endl;
    sum+= result;
    }
    cv.notify_one();
}

int main () {
    // matrix and vector multiplication
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}}; // matrix
    std::vector<int> v = {2,4,6}; // vector

    std::thread one(multiply, matrix[0], v);
    //std::this_thread::sleep_for(std::chrono::seconds(rand()%5 + 1));
    std::thread two(multiply, matrix[1], v);
    //std::this_thread::sleep_for(std::chrono::seconds(rand()%5 + 1));
    std::thread three(multiply, matrix[2], v);

    count = true;
    
    one.join();
    two.join();
    three.join();
    std::cout << "Sum of result vector elements: " << sum << std::endl;

    return 0;
} 
