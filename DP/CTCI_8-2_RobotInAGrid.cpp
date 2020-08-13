/*
 
 To compile:
 c++ -std=c++17 CTCI_8-2_RobotInAGrid.cpp
 
 This file contains two solutions:
 - robot_path: brute-force recursive solution
 - robot_path: recursive solution with memoization
 
 Run time for grid_large (calling each function 100 times) on my computer:
 - robot_path: ~40 ms
 - robot_path: ~6 ms
 
 */

#include <vector>
#include <iostream>
#include <chrono>

// Brute-force recursion
std::vector<std::vector<int>> robot_path (const std::vector<std::vector<bool>>& grid);
bool robot_path (int row, int col, const std::vector<std::vector<bool>>& grid, std::vector<std::vector<int>>& path);

// Memoization: caching the grid cells that lead nowhere
// So that we don't have to recursively check them twice
std::vector<std::vector<int>> robot_path_memo (const std::vector<std::vector<bool>>& grid);
bool robot_path_memo (int row, int col, const std::vector<std::vector<bool>>& grid, std::vector<std::vector<int>>& path, std::vector<std::vector<bool>>& memo);

void print_path (const std::vector<std::vector<int>>& path);
bool compare_paths(const std::vector<std::vector<int>>& path, const std::vector<std::vector<int>>& path_memo);

int main () {
    
    std::vector<std::vector<bool>> grid {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    
    // 1: blocked cell
    std::vector<std::vector<bool>> grid_large {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    // Run robot_path 100 times and measure how long it takes
    std::vector<std::vector<int>> path;
    auto start_rec = std::chrono::steady_clock::now();
    for (int i(0); i < 100; ++i) {
        path = robot_path(grid_large);
    }
    auto end_rec = std::chrono::steady_clock::now();
    
    // Run robot_path_memo 100 times and measure how long it takes
    std::vector<std::vector<int>> path_memo;
    auto start_memo = std::chrono::steady_clock::now();
    for (int i(0); i < 100; ++i) {
        path_memo = robot_path_memo(grid_large);
    }
    auto end_memo = std::chrono::steady_clock::now();
    
    // Print both results and elapsed time
    std::cout << "robot_path:" << std::endl;
    print_path(path);
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_rec - start_rec).count() << " ms\n" << std::endl;
    
    std::cout << "robot_path_memo:" << std::endl;
    print_path(path_memo);
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_memo - start_memo).count() << " ms\n" << std::endl;
    
    if (compare_paths(path, path_memo)) {
        std::cout << "Paths same" << std::endl;
    } else {
        std::cout << "Paths NOT same" << std::endl;
    }
    
}

std::vector<std::vector<int>> robot_path (const std::vector<std::vector<bool>>& grid) {
    
    int row = 0;
    int col = 0;
    std::vector<std::vector<int>> path;
    
    if (robot_path (row, col, grid, path)) {
        return path;
    } else {
        return std::vector<std::vector<int>>{};
    }
    
}

bool robot_path (int row, int col, const std::vector<std::vector<bool>>& grid, std::vector<std::vector<int>>& path) {
    
    // If outside of grid - no path
    if (row >= grid.size() || col >= grid[0].size()) {
        return false;
    }
    
    // Blocked cell - no path
    if (grid[row][col] == 1) return false;
    
    // Target cell - add it to path and return true
    if (row == grid.size() - 1 && col == grid[0].size() - 1) {
        path.push_back({row, col});
        return true;
    }
    
    // If we haven't returned up to now - add cell to path
    path.push_back({row, col});
    
    // Go right
    if (robot_path(row, col + 1, grid, path)) {
        return true;
    }
    // If there is no path right - Go down
    if (robot_path(row + 1, col, grid, path)) {
        return true;
    }
    
    // Up to now we have been adding cells to path as we go
    // But if there is no path, we need to remove the cell from the path
    path.pop_back();
    
    return false;
    
}

std::vector<std::vector<int>> robot_path_memo (const std::vector<std::vector<bool>>& grid) {
    
    int row = 0;
    int col = 0;
    std::vector<std::vector<int>> path;
    std::vector<std::vector<bool>> memo = grid;
    
    if (robot_path_memo (row, col, grid, path, memo)) {
        return path;
    } else {
        return std::vector<std::vector<int>>{};
    }
    
}

bool robot_path_memo (int row, int col, const std::vector<std::vector<bool>>& grid,
                      std::vector<std::vector<int>>& path, std::vector<std::vector<bool>>& memo) {
    
    // robot_path_memo is the same as robot_path
    // Except we use additional grid called memo,
    // where we mark the cells that lead nowhere
    
    if (row >= grid.size() || col >= grid[0].size()) {
        return false;
    }
    
    // If the cell is blocked or if it's in the memo (i.e. leading nowhere) - no path
    if (grid[row][col] == 1 || memo[row][col] == 1) return false;
    
    if (row == grid.size() - 1 && col == grid[0].size() - 1) {
        path.push_back({row, col});
        return true;
    }
    
    path.push_back({row, col});
    
    if (robot_path_memo(row, col + 1, grid, path, memo)) {
        return true;
    }
    if (robot_path_memo(row + 1, col, grid, path, memo)) {
        return true;
    }
    
    // This cell leads nowhere - add it to the memo
    memo[row][col] = 1;
    
    path.pop_back();
    
    return false;
    
}






void print_path (const std::vector<std::vector<int>>& path) {
    std::cout << "{";
    for (auto& e : path) {
        std::cout << "{" << e[0] << ", " << e[1] << "}" << ",";
    }
    std::cout << "\b}" << std::endl;
}

bool compare_paths(const std::vector<std::vector<int>>& path, const std::vector<std::vector<int>>& path_memo) {
    
    if (path.size() != path_memo.size()) return false;
    
    for (int i(0); i < path.size(); ++i) {
        if (path[i][0] != path_memo[i][0]) return false;
        if (path[i][1] != path_memo[i][1]) return false;
    }
    
    return true;
}




