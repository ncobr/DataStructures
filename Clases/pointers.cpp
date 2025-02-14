#include <iostream>

using namespace std;

int main() {
    cout<<"1. Toda variable ocupa un lugar en la memoria." << endl;
    cout<<"2. Todo lugar en la memoria tiene una direccion." << endl;
    cout<<"3. Un puntero es una variable (como cualquier otra) que almacena direcciones de memoria." << endl;

    int x;
    x = 10;
    cout << "Valor " << x << endl;
    cout << "Direccion " << &x << endl;

    double y;
    y = 3.1415;
    cout << "Valor " << y << endl;
    cout << "Direccion " << &y << endl;

    char z;
    z = 'a';
    cout << "Valor " << z << endl;
    cout << "Direccion " << &z << endl;

    int* px;
    px = &x;
    cout << "Valor " << px << endl;
    cout << "Valor en la pos de memoria " << *px << endl;
    cout << "Direccion " << &px << endl;
    *px = 42;
    cout << "Valor de x " << x << endl;

    int m = 15;
    px = &m;
    *px = 34;
    cout << m << endl;

    void* r;
    return 0;
}
