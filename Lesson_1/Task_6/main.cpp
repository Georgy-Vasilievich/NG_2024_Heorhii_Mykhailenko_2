#include <iostream>

using namespace std;

int main()
{
    int size = 0;

    cout << "Enter size: ";
    cin >> size;

    for (int iteration = 0; iteration < size; ++iteration) {
        int spaces = size - iteration - 1;
        int asterisks = 1 + iteration * 2;
        for (int space = 0; space < spaces; ++space)
            cout << " ";
        for (int asterisk = 0; asterisk < asterisks; ++asterisk)
            cout << "*";
        cout << endl;
    }

    for (int space = 0; space < size - 1; ++space)
        cout << " ";
    cout << "*" << endl;

    return 0;
}
