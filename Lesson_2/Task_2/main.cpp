#include <iostream>

using namespace std;

int main()
{
    int numbers[20];
    int maximum = 0;
    for (int number = 0; number < 20; ++number) {
        cout << "Enter value: ";
        cin >> numbers[number];
        if (maximum < numbers[number])
            maximum = numbers[number];
        if (numbers[number] == 0)
            break;
    }

    for (int number = 0; number < 20; ++number) {
        if (numbers[number] == 0)
            break;
        int spaces = (maximum - numbers[number]) / 2;
        for (int space = 0; space < spaces; ++space)
            cout << " ";
        for (int asterisk = 0; asterisk < numbers[number]; ++asterisk)
            cout << "*";
        cout << endl;
    }
    return 0;
}
