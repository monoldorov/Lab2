#include "MenuQueue.hpp"
#include "Complex.hpp"

int main() {
    menu();
    Complex a(1, 2);
    Complex b(3, 4);
    Complex c = a * 5;
    cout << &a << ' ' << &b << ' ' << &c << endl;

    return 0;
}