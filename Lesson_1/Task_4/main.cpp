#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    char operation;
    float firstNumber = 0;
    float secondNumber = 0;
    float result = 0;

    cout << "Enter the first number: ";
    cin >> firstNumber;

    cout << "Enter the second number: ";
    cin >> secondNumber;

    cout << "Enter the operation: ";
    cin >> operation;

    switch (operation) {
    case '+':
        result = firstNumber + secondNumber;
        break;
    case '-':
        result = firstNumber - secondNumber;
        break;
    case '*':
        result = firstNumber * secondNumber;
        break;
    case '/':
        if (secondNumber == 0) {
            cout << "Division by zero." << endl;
            return 1;
        }
        result = firstNumber / secondNumber;
        break;
    case '^':
        result = pow(firstNumber, secondNumber);
        break;
    case 'r':
        if (secondNumber <= 0) {
            cout << "Non-positive n." << endl;
            return 2;
        }
        result = pow(firstNumber, 1.0/secondNumber);
        break;
    default:
        cout << "Invalid operation." << endl;
        return 3;
    }

    cout << result << endl;

    return 0;
}
