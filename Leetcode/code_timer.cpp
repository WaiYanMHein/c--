#include "code_timer.h"
#include <ctime>
#include <chrono> 
#include <iostream> 
#include <cstdlib> 
#include <cmath> 

using namespace std;
using namespace chrono;

// Constructor
CodeTimer::CodeTimer(const string& name) : timer_name(name) {}

// Start timing
void CodeTimer::start() {
    start_time = high_resolution_clock::now();
}

// Stop timing and return duration in nanoseconds
long long CodeTimer::stop() {
    end_time = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end_time - start_time).count();
}

// Stop timing and print result
void CodeTimer::stopAndPrint() {
    long long duration = stop();
    cout << timer_name << " took: " << duration << " nanoseconds" << endl;
}