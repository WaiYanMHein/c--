#include <iostream>
#include <cstdlib>

using namespace std; 

class Solution {
public:
    int maxDiff(int num) {
        string num_str = to_string(num);
        
        // Helper lambda function to replace all occurrences of target digit with replacement digit
        auto replaceAll = [](string s, char target, char replacement) {
            for (char& c : s) {
                // Check if current character matches the target digit
                if (c == target) {
                    // Replace it with the new digit
                    c = replacement;
                }
            }
            // Convert modified string back to integer
            return stoi(s);
        };
        
        // Find maximum number: replace first non-9 digit with 9 for maximum value
        int max_num = num;
        for (char digit : num_str) {
            if (digit != '9') {
                // Replace all occurrences of this digit with 9 to maximize the number
                max_num = replaceAll(num_str, digit, '9');
                break; // Stop after finding the first non-9 digit
            }
        }
        
        // Find minimum number: use greedy strategy to minimize value
        int min_num = num;
        if (num_str[0] != '1') {
            // If first digit is not 1, replace all first digits with 1 to minimize
            min_num = replaceAll(num_str, num_str[0], '1');
        } else {
            // If first digit is 1, find first digit that's not 0 or 1
            for (char digit : num_str) {
                if (digit != '0' && digit != '1') {
                    // Replace all occurrences of this digit with 0 to minimize
                    min_num = replaceAll(num_str, digit, '0');
                    break; // Stop after finding the first valid digit to replace
                }
            }
        }
        
        // Return the maximum difference between max and min possible numbers
        return max_num - min_num;
    }
};