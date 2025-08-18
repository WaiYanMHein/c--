#include <iostream> 
#include <cstdlib>
#include <cmath> 
#include <vector>
#include <matplotlib-cpp> 
#include <eigen3> 
#include <numcpp> 

using namespace std; 

void stability(double e = 0.0, double f0 = 4, double t = 0.0, double lambda = -1.0, double h = 0.001, double T = 2.0) {
    double f = f0; 
    while(t<T) {
        t += h; 
        f = (1+lambda * h) * f; 
        e = f - f0 * exp(lambda * t); 
        cout << e << endl; 
    }
}

int main(){
    stability(); 
    return 0; 
}