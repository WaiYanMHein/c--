#ifndef CODE_TIMER_H
#define CODE_TIMER_H

#include <chrono>
#include <iostream>
#include <functional>
#include <string>

using namespace std;
using namespace chrono;

class CodeTimer {
private:
    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;
    string timer_name;
    
public:
    // Constructor
    CodeTimer(const string& name = "Timer");
    
    // Start timing
    void start();
    
    // Stop timing and return duration in nanoseconds
    long long stop();
    
    // Stop timing and print result
    void stopAndPrint();
    
    // Static method to time a function and return duration
    template<typename Func, typename... Args>
    static long long timeFunction(Func&& func, Args&&... args) {
        auto start = high_resolution_clock::now();
        func(forward<Args>(args)...);
        auto end = high_resolution_clock::now();
        return duration_cast<nanoseconds>(end - start).count();
    }
    
    // Static method to time a function and print result
    template<typename Func, typename... Args>
    static void timeFunctionAndPrint(const string& functionName, Func&& func, Args&&... args) {
        auto start = high_resolution_clock::now();
        func(forward<Args>(args)...);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start).count();
        cout << functionName << " took: " << duration << " nanoseconds" << endl;
    }
    
    // Benchmark a function multiple times
    template<typename Func, typename... Args>
    static void benchmark(const string& functionName, int iterations, Func&& func, Args&&... args) {
        cout << "Benchmarking " << functionName << " (" << iterations << " iterations):" << endl;
        
        long long totalTime = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = 0;
        
        for(int i = 0; i < iterations; i++) {
            auto start = high_resolution_clock::now();
            func(forward<Args>(args)...);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start).count();
            
            totalTime += duration;
            minTime = min(minTime, duration);
            maxTime = max(maxTime, duration);
        }
        
        cout << "  Average: " << (totalTime / iterations) << " nanoseconds" << endl;
        cout << "  Min: " << minTime << " nanoseconds" << endl;
        cout << "  Max: " << maxTime << " nanoseconds" << endl;
        cout << "  Total: " << totalTime << " nanoseconds" << endl;
    }
};

#endif
