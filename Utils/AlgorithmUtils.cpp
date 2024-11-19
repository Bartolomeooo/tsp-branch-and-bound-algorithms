#include "AlgorithmUtils.h"
#include <cstdlib>
#include <ctime>
#include <vector>

// Calculate factorial of n
int AlgorithmUtils::factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Custom implementation of shuffle
void AlgorithmUtils::customShuffle(std::vector<int>& cities) {
    int n = cities.size();
    for (int i = 0; i < n; ++i) {
        int randomIndex = i + rand() % (n - i);  // Randomly choose an index
        AlgorithmUtils::swap(cities[i], cities[randomIndex]);  // Swap values
    }
}

// Custom implementation of next permutation
bool AlgorithmUtils::nextPermutation(std::vector<int>& nums) {
    int n = nums.size(), i, l;

    // Find the first index where nums[i] < nums[i+1] from the back
    for (i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) break;
    }

    if (i < 0) {
        // If no such index exists, reverse the sequence and return false
        AlgorithmUtils::reverse(nums, 0, n - 1);
        return false;
    } else {
        // Find the smallest number greater than nums[i] to swap
        for (l = n - 1; l > i; l--) {
            if (nums[l] > nums[i]) break;
        }
        // Swap and reverse the sequence after index i
        AlgorithmUtils::swap(nums[i], nums[l]);
        AlgorithmUtils::reverse(nums, i + 1, n - 1);
        return true;  // Successfully generated the next permutation
    }
}

// Custom reverse implementation for a vector
void AlgorithmUtils::reverse(std::vector<int>& nums, int start, int end) {
    while (start < end) {
        AlgorithmUtils::swap(nums[start], nums[end]);
        start++;
        end--;
    }
}

// Custom swap implementation
void AlgorithmUtils::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
