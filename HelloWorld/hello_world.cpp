#include <iostream> 

using namespace std; // makes it so that std::cout isn't needed

int main() {
    const double pi = 3.14;
    int a = 1;
    int b = 2; 
    int temp = a; 
    a = b;
    b = temp;

    // stdout 
    std::cout << a << std::endl;
    std::cout << a + b << std::endl; 
    
    // looping in c++
    /*for (int i = 0; i < 10; i++){ 
        std::cout << i << std::endl; 
    }*/ 
    
    // concatentaion of int and String
    std::cout << "number = " << a;  

    cout << "Sale = " << 95000 << endl; 
    cout << "County Tax = " << 4 << "%" << endl; 
    cout << "State Tax = " << 2 << "%" << endl; 

    return 0;
}
