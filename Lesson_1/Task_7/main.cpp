#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    float x = 0;
    float y = 0;
    float N = 0;
    float distance = 0;

    cout << "Enter your x: ";
    cin >> x;

    cout << "Enter your y: ";
    cin >> y;

    cout << "Enter radius N: ";
    cin >> N;

    distance = sqrt(pow(x, 2) + pow(y, 2));

    cout << distance << " from the center";
    if (distance > N)
        cout << " (beyond radius)";
    cout << endl;

    return 0;
}
