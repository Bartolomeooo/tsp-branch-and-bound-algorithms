#ifndef TRAVELLING_SALESMAN_PROBLEM_ALGORITHMUTILS_H
#define TRAVELLING_SALESMAN_PROBLEM_ALGORITHMUTILS_H



#include <vector>

class AlgorithmUtils {
public:
    static int factorial(int n);

    static void customShuffle(std::vector<int>& cities);

    static bool nextPermutation(std::vector<int>& cities);

    static void reverse(std::vector<int>& nums, int start, int end);

    static void swap(int& a, int& b);
};

#endif