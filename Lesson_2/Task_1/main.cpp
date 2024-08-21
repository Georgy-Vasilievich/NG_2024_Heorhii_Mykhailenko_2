#include <iostream>

using namespace std;

int main()
{
    int accounts[10];

    for (int account = 0; account < 10; ++account)
        accounts[account] = 0;

    while (true) {
        int action = 0;

        cout << "Enter action (1 - add money, 2 - remove money, 3 - display all balances): ";
        cin >> action;

        if (action < 1 || action > 3) {
            cout << "Invalid action" << endl;
            continue;
        }

        if (action != 3) {
            int account = 0;
            int money = 0;
            cout << "Enter account number: ";
            cin >> account;

            if (account < 0 || account >= 10) {
                cout << "Invalid account number." << endl;
                continue;
            }

            cout << "Enter the amount of money: ";
            cin >> money;

            if (money <= 0) {
                cout << "The amount must be positive." << endl;
                continue;
            }

            if (action == 1) {
                accounts[account] += money;
                cout << "Money added." << endl;
            } else if (accounts[account] >= money) {
                accounts[account] -= money;
                cout << "Money removed." << endl;
            } else
                cout << "Not enough money." << endl;
        } else
            for (int account = 0; account < 10; ++account)
                cout << "Account " << account << ": " << accounts[account] << endl;
    }


    return 0;
}
