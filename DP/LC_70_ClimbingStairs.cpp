/*
 
 1. climb_rec - brute force recursion
    One can climb to each step only in two ways:
    from the step - 1 and from the step - 2. Therefore,
    the number of ways to climb to each step is the sum
    of the number of ways to climb to step - 1 and step - 2.
    Time complexity: O(2^n)
 
 2. climb_memo - same as climb_rec, but caches the already calculated values
    Time complexity: O(n)
    But it is still recursion, so for large n can cause stack overflow
 
 3. climb_dp - bottom up dynamic programming solution
    Time complexity: O(n)
    No danger of stack overflow, as it is iterative
 
 E.g. result for n = 50:
 
 num_steps_rec = 20365011074
 climb_rec takes: 50968 ms (!!!)
 
 num_steps_memo = 20365011074
 climb_memo takes: 0 ms
 
 num_steps_dp = 20365011074
 climb_dp takes: 0 ms

 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

long climb_rec(int n);
long climb_memo(int n, std::unordered_map<int, long>& stairs_map);
long climb_dp(int n);


int main() {
    
    int n = 50;
    
    // 1. Recursive:
    auto start_rec = std::chrono::steady_clock::now();
    long num_steps_rec = climb_rec(n);
    auto end_rec = std::chrono::steady_clock::now();

    // 2. Memoization
    std::unordered_map<int, long> stairs_map;
    auto start_memo = std::chrono::steady_clock::now();
    long num_steps_memo = climb_memo(n, stairs_map);
    auto end_memo = std::chrono::steady_clock::now();

    // 3. DP
    auto start_dp = std::chrono::steady_clock::now();
    long num_steps_dp = climb_dp(n);
    auto end_dp = std::chrono::steady_clock::now();


    // Show results and timing
    std::cout << "For n = " << n << ":\n";
    
    std::cout << "num_steps_rec = " << num_steps_rec << "\n";
    std::cout << "climb_rec takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_rec - start_rec).count() << " ms\n" << std::endl;
    
    std::cout << "num_steps_memo = " << num_steps_memo << "\n";
    std::cout << "climb_memo takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_memo - start_memo).count() << " ms\n" << std::endl;
    
    std::cout << "num_steps_dp = " << num_steps_dp << "\n";
    std::cout << "climb_dp takes: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_dp - start_dp).count() << " ms\n" << std::endl;

}


long climb_rec(int n) {

    if (n == 0) return 1;
    if (n < 3) return n;
    
    return climb_rec(n - 1) + climb_rec(n - 2);
}

long climb_memo(int n, std::unordered_map<int, long>& stairs_map) {
    if (n == 0) return 1;
    if (n < 3) return n;
    
    if (stairs_map[n] != 0) {
        return stairs_map[n];
    }
    
    long res = climb_memo(n - 1, stairs_map)
    + climb_memo(n - 2, stairs_map);
    stairs_map[n] = res;
    
    return res;
}

long climb_dp(int n) {
    std::unordered_map<int, long> stairs_map;
    
    stairs_map[0] = 1;
    stairs_map[1] = 1;
    stairs_map[2] = 2;
    
    for (int stair = 3; stair <= n; stair++) {
        stairs_map[stair] = stairs_map[stair - 1]
        + stairs_map[stair - 2];
    }
    
    return stairs_map[n];
    
}



