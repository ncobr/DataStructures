#include <iostream>

using namespace std;

/*
typedef struct {
    double real;
    double img;
} complexNumber;

int main() {

    complexNumber a;
    a.real = 3.2;
    a.img = 0.0;

    cout << "(" << a.real << ", " << a.img << "i)" << endl;
    cout << &a << endl;

    complexNumber *p = &a;
    p->img = 3.1415;
    cout << "(" << a.real << "," << a.img << "i)" << endl;
    cout << &a << endl;
    return 0;
}


// Punteros dobles:
typedef struct {
    int red;
    int green;
    int blue;
} RGBColor;

typedef struct {
    int row;
    int col;
    RGBColor color;
} pixel;

RGBColor create(int r, int g, int b) {
    RGBColor color;
    color.red = 255;
    color.blue = 0;
    color.green = 0;
    return color;
}

RGBColor printColor(RGBColor *color) {
    cout << "(" << color->red << ", " << color->green << ", " << color->blue
         << ")" << endl;
}

int main() {
    RGBColor red = create(255, 0, 0);
    pixel p;
    p.row = 0;
    p.col = 0;
    p.color = &red;
    printColor(&red);
    return 0;
}
*/

int main() {
    int a = 42;
    int *p = &a;
    int **q = &p;

    cout << a << endl;
    cout << &a << endl;

    cout << p << endl;
    cout << &p << endl;

    cout << q << endl;
    cout << &q << endl;

    // Cambiar el valore de a desde q
    **q = 10;
    cout << a << endl;
    return 0;
}
