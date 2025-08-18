#include <cstdlib> 
#include <cmath>
#include <iostream>

using namespace std; 

int main(){
    overload_function(); 
    return 0; 
}

void overload_function(){
    cout << "overload" << endl; 
}

void overload_function(string overload){ 
    cout << "overload " << overload << endl; 
}

