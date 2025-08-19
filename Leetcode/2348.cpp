#include <iostream>
#include <vector> 
#include <cmath> 
#include <cstdlib>

using namespace std; 

long long zeroFilledSubarray(vector<int>& nums) {
    long long counter = 0; 
    long long consecutive_zeros = 0; 
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            counter += consecutive_zeros; 
            consecutive_zeros += 1; 
        } else {
            consecutive_zeros = 1; 
        }
    }
    return counter; 
}   

long long optimized_zeroFilledSubarray(vector<int>& nums) {
    /*
    subarray of length 
    */
}