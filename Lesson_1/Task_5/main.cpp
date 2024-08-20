#include <cmath>
#include <complex>
#include <iostream>

using namespace std;

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;
    float D = 0;

    cout << "Enter a: ";
    cin >> a;

    cout << "Enter b: ";
    cin >> b;

    cout << "Enter c: ";
    cin >> c;

    D = pow(b, 2) - 4 * a * c;

    complex<float> root = sqrt(complex<float>(D));

    complex<float> x1 = (-b + root) / (2 * a);
    complex<float> x2 = (-b - root) / (2 * a);

    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;

    return 0;
}
