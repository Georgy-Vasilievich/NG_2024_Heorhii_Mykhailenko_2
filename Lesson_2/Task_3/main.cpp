#include <iostream>

using namespace std;

int main()
{
    int columns[5];
    int rows = 0;
    for (int column = 0; column < 5; ++column) {
        cout << "Enter amount in " << column + 1 << " column: ";
        cin >> columns[column];
        if (columns[column] > rows)
            rows = columns[column];
    }

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < 5; ++column) {
            if (row < columns[column])
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}
