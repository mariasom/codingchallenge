// Implement c++11 threading example
//   2-3 threads running
#include<iostream> 
#include<thread>
#include<vector>

int sum = 0;
void multiply(std::vector<int> row, std::vector<int> v ) {
    int result = 0; 
    if (row.size() == v.size()) {
        for(int i = 0; i < row.size(); i++) 
            result += row[i]*v[i]; 
    std::cout << "vector:" << result << std::endl;
    sum+= result;
    }
}

int main () {
    // matrix and vector multiplication
    std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}}; // matrix
    std::vector<int> v = {2,4,6}; // vector

    std::thread one(multiply, matrix[0], v);
    std::thread two(multiply, matrix[1], v);
    std::thread three(multiply, matrix[2], v);
    
    one.join();
    two.join();
    three.join();
    std::cout << "Sum of result vector elements: " << sum << std::endl;

    return 0;
} 
