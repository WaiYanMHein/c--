#include <iostream> 
#include <cmath>
#include <cstdlib>
#include <ctime>

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
    std::cout << "number = " << a << endl;  

    cout << "Sale = " << 95000 << endl; 
    cout << "County Tax = " << 4 << "%" << endl; 
    cout << "State Tax = " << 2 << "%" << endl; 
    
    /*
    //reading from console
    cout << "Enter two values: "; 
    double value1;
    double value2;  
    // note we can do 10 space 10 to insert into value1 and 2
    cin >> value1; 
    cin >> value2; 
    cout << value1 + value2 << endl;
    */ 

    // cmath sqrt
    cout << sqrt(4) << endl; 

    // random
    srand(1); 
    int number1 = rand(); 
    cout << number1 << endl; 
    srand(2); 
    int number2 = rand(); 
    cout << number2 << endl; 
    srand(time(0)); 
    int number3 = rand(); 
    cout << number3 << endl;
    
    const short dice_max = 6; 
    const short dice_min = 1; 
    short roll = (rand() % (dice_max) + dice_min); 
    cout << roll << endl; 

    return 0;
}
