#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int choice;
    double num1, num2, result;
    
    cout << "Welcome to the Professional Calculator" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Please select an operation:" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Power" << endl;
    cout << "6. Square Root" << endl;
    cout << "7. Exit" << endl;
    cout << "-------------------------------------" << endl;
    
    do {
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter two numbers to add: ";
                cin >> num1 >> num2;
                result = num1 + num2;
                cout << "Result: " << result << endl;
                break;
            case 2:
                cout << "Enter two numbers to subtract: ";
                cin >> num1 >> num2;
                result = num1 - num2;
                cout << "Result: " << result << endl;
                break;
            case 3:
                cout << "Enter two numbers to multiply: ";
                cin >> num1 >> num2;
                result = num1 * num2;
                cout << "Result: " << result << endl;
                break;
            case 4:
                cout << "Enter two numbers to divide: ";
                cin >> num1 >> num2;
                if (num2 == 0) {
                    cout << "Error: Division by zero" << endl;
                } else {
                    result = num1 / num2;
                    cout << "Result: " << result << endl;
                }
                break;
            case 5:
                cout << "Enter base and exponent: ";
                cin >> num1 >> num2;
                result = pow(num1, num2);
                cout << "Result: " << result << endl;
                break;
            case 6:
                cout << "Enter a number to calculate its square root: ";
                cin >> num1;
                if (num1 < 0) {
                    cout << "Error: Square root of a negative number is not defined" << endl;
                } else {
                    result = sqrt(num1);
                    cout << "Result: " << result << endl;
                }
                break;
            case 7:
                   system("gnome-terminal -- bash -c './os; exec bash'");
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 7." << endl;
                break;
        }
        
    } while (choice != 7);
    
    return 0;
}
