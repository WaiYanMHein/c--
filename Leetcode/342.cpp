#include <iostream>
#include <cmath> 
#include <cstdlib> 
#include <ctime>
#include <chrono>
#include <random>
#include "code_timer.h"

using namespace std;

bool isPowerofFour(int n){
    //1500 - 2000 nanoseconds
    if (n < 1){
        return false;
    }
    for (int i = 0; i < 215; i++){
        if (pow(4,i) == n){
            return true;
        }
        else if (pow(4,i) > n){
            return false; 
        }
    }
    return false; 
}

bool isPowerofFourBitwise(int n){
    //100 - 500 nanoseconds
    int mask = 0b01010101010101010101010101010101; 
    if (n < 1){
        return false;
    }
    else if ((n & (n - 1)) == 0 && (n | mask) == mask){
        return true;
    } else {
        return false; 
    }
}

int main() {
    cout << "=== Testing Power of Four Functions ===" << endl;
    
    srand(time(0)); 
    int testNumber = rand(); 

    cout << "random numer " << testNumber << endl; 
    
    // Method 1: Using CodeTimer class instance
    CodeTimer timer1("Loop Version");
    timer1.start();
    bool result1 = isPowerofFour(testNumber);
    timer1.stopAndPrint();
    cout << "Result: " << result1 << endl << endl;
    
    // Method 2: Using static timeFunctionAndPrint
    CodeTimer::timeFunctionAndPrint("Bitwise Version", 
        [&]() { return isPowerofFourBitwise(testNumber); });
    cout << "Result: " << isPowerofFourBitwise(testNumber) << endl << endl;
    
    // Method 3: Benchmark both functions
    cout << "=== Benchmarking Comparison ===" << endl;
    CodeTimer::benchmark("Loop Version", 10000, 
        [&]() { isPowerofFour(testNumber); });
    
    cout << endl;
    
    CodeTimer::benchmark("Bitwise Version", 10000, 
        [&]() { isPowerofFourBitwise(testNumber); });
    
    return 0;
}