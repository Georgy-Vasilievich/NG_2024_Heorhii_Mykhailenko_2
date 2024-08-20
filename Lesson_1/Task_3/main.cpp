#include <iostream>

using namespace std;

int main()
{
    int money = 0;
    cout << "How much money do you earn? ";
    cin >> money;

    if (money < 1000)
        cout << "Work more. ";
    if (money > 999) {
        if (money > 999999)
            cout << "You are a millionaire. ";
        if (money < 1000000)
            cout << "You work great. ";
    }

    cout << "You are doing great!" << endl;

    return 0;
}
