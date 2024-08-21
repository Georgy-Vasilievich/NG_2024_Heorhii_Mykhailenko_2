#include <iostream>

using namespace std;

int main()
{
    char str[256];
    cout << "Enter some string: ";
    cin.getline(str, 256);
    int words = 0;
    int letters = 0;

    for (int character = 0; str[character] != 0; ++character) {
        if (str[character] < 'A'
                || str[character] > 'z'
                || (str[character] > 'Z'
                    && str[character] < 'a')
                ) {
            if (letters > 0) {
                letters = 0;
                ++words;
            }
        } else {
            ++letters;
        }
    }

    if (letters > 0)
        ++words;

    cout << "Number of words: " << words << endl;

    return 0;
}
