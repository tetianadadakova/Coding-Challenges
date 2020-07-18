#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>


// Brute force recursion:
// Pros: easy to understand
// Cons: Exponential time complexity (~3^n in this case); Can cause stack overflow due to recursion
int num_paths_recursive(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    
    return num_paths_recursive(n - 3) + num_paths_recursive(n - 2) + num_paths_recursive(n - 1);
}

// Recursion with memoization:
// Pros: Linear time complexity
// Cons: Can cause stack overflow due to recursion
int num_paths_memo(int n, std::unordered_map<int, int>& memo) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    
    if (memo.find(n) == memo.end()) {
        int curr_res = num_paths_memo(n - 3, memo) + num_paths_memo(n - 2, memo) + num_paths_memo(n - 1, memo);
        memo[n] = curr_res;
    }
    
    return memo[n];
}

// Dynamic programming:
// Pros: Linear time complexity; No recursion => no stack overflow
// Cons: Harder to come up with solution
int num_paths_dp(int n) {
    std::vector<int> dp;
    dp.push_back(1);
    dp.push_back(1);
    dp.push_back(2);
    
    for (int i = 3; i < (n + 1); ++i) {
        int curr_res = dp[i - 3] + dp[i - 2] + dp[i - 1];
        dp.push_back(curr_res);
    }
    return dp[n];
}


int main() {
    
    int num = 30;
    
    std::cout << "Brute force recursion: " << std::endl;
    auto t_00 = std::chrono::high_resolution_clock::now();
    std::cout << "Result: " << num_paths_recursive(num) << std::endl;
    auto t_01 = std::chrono::high_resolution_clock::now();
    auto duration0 = std::chrono::duration_cast<std::chrono::microseconds>(t_01 - t_00).count();
    std::cout << "Time: " << duration0 << std::endl;

    std::cout << "Recursion with memoization: " << std::endl;
    std::unordered_map<int, int> memo;
    auto t_10 = std::chrono::high_resolution_clock::now();
    std::cout << "Result: " << num_paths_memo(num, memo) << std::endl;
    auto t_11 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t_11 - t_10).count();
    std::cout << "Time: " << duration1 << std::endl;

    std::cout << "Dynamic programming: " << std::endl;
    auto t_20 = std::chrono::high_resolution_clock::now();
    std::cout << "Result: " << num_paths_dp(num) << std::endl;
    auto t_21 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t_21 - t_20).count();
    std::cout << "Time: " << duration2 << std::endl;

}
