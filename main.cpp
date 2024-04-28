#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

int adjustX(int x) {
    if (x < 0) return SCREEN_WIDTH + x;
    if (x >= SCREEN_WIDTH) return x - SCREEN_WIDTH;
    return x;
}

int adjustY(int y) {
    if (y < 0) return SCREEN_HEIGHT + y;
    if (y >= SCREEN_HEIGHT) return y - SCREEN_HEIGHT;
    return y;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void dibujarBorde() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0);
        cout << "-";
        gotoxy(i, SCREEN_HEIGHT - 1);
        cout << "-";
    }

    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        gotoxy(0, j);
        cout << "|";
        gotoxy(SCREEN_WIDTH - 1, j);
        cout << "|";
    }
}

void dibujarRectangulo(int x, int y, int ancho, int alto, bool green = false) {
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            int currentX = adjustX(x + j);
            int currentY = adjustY(y + i);
            gotoxy(currentX, currentY);

            if ((i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) && green) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "*";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void drawCircle(int radius, int centerX, int centerY) {
    if (radius < 1) return;
    int x = radius, y = 0, P = 1 - radius;
    auto plotPoints = [&](int xCenter, int yCenter, int X, int Y) {
        gotoxy(adjustX(xCenter + X), adjustY(yCenter + Y));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter - X), adjustY(yCenter + Y));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter + X), adjustY(yCenter - Y));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter - X), adjustY(yCenter - Y));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter + Y), adjustY(yCenter + X));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter - Y), adjustY(yCenter + X));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter + Y), adjustY(yCenter - X));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(adjustX(xCenter - Y), adjustY(yCenter - X));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << '*';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    };
    while (x >= y) {
        plotPoints(centerX, centerY, x, y);
        y++;
        if (P <= 0) {
            P = P + 2*y + 1;
        } else {
            x--;
            P = P + 2*(y - x) + 1;
        }
    }
}


void drawEquilateralTriangle(int base, int x, int y) {
    if (base % 2 == 0) base++;
    int height = base / 2;
    for (int row = 0; row <= height; ++row) {
        int x1 = x - row;
        int x2 = x + row;

        gotoxy(adjustX(x1), adjustY(y + row));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "*";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        gotoxy(adjustX(x2), adjustY(y + row));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "*";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if (row == height) {
            for (int col = x1 + 1; col < x2; ++col) {
                gotoxy(adjustX(col), adjustY(y + row));
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << "*";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
        }
    }
}

void dibujarCuadrado(int x, int y, int lado) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {

            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
                gotoxy(adjustX(x + j), adjustY(y + i));
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                cout << "*";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
        }
    }
}

void limpiarMenu(int desde, int hasta) {
    for (int i = desde; i <= hasta; ++i) {
        gotoxy(0, i);
        for (int j = 0; j < 80; ++j) {
            cout << " ";
        }
    }
}

void limpiarLinea(int y) {
    gotoxy(0, y);
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        cout << " ";
    }
    gotoxy(0, y);
}

/*void limpiarLinea(int y) {
    gotoxy(0, y);
    for (int i = 0; i < SCREEN_WIDTH; ++i) cout << " ";
}

/*void dibujarBorde() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0);
        cout << "-";
        gotoxy(i, SCREEN_HEIGHT - 1);
        cout << "-";
    }
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        gotoxy(0, j);
        cout << "|";
        gotoxy(SCREEN_WIDTH - 1, j);
        cout << "|";
    }
}
*/

int main() {
    int x = 0, y = 0;
    int lado, ancho, alto, radio;
    char eleccion;

    do {
        dibujarBorde();
        limpiarLinea(25);
        limpiarLinea(26);
        limpiarLinea(27);
        gotoxy(0, 26);
        cout << "Usa las teclas de flecha para mover el cursor. Presiona F12 para continuar." << endl;

        bool f12Pressed = false;
        while (!f12Pressed) {
            if (_kbhit()) {
                int ch = _getch();
                if (ch == 0 || ch == 224) {
                    int key = _getch();
                    switch (key) {
                        case 72:
                            if (y > 0) y--;
                            break;
                        case 80:
                            if (y < 23) y++;
                            break;
                        case 75:
                            if (x > 0) x--;
                            break;
                        case 77:
                            if (x < 78) x++;
                            break;
                        case 134:
                            f12Pressed = true;
                            break;
                    }
                }
                gotoxy(x, y);
            }
        }

        limpiarLinea(26);
        gotoxy(0, 26);
        cout << "Selecciona la forma a dibujar:" << endl;
        cout << "1. Rectangulo" << endl;
        cout << "2. Triangulo" << endl;
        cout << "3. Circulo" << endl;
        cout << "4. Cuadrado" << endl;
        int opcion;

        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingresa el ancho y la altura del rectangulo: ";
                cin >> ancho >> alto;
                if (ancho > SCREEN_WIDTH - 2 || alto > SCREEN_HEIGHT - 2) {
                    cout << "Los datos ingresados son demasiado grandes para dibujar un rectángulo." << endl;
                    cout << "El ancho máximo permitido es: " << SCREEN_WIDTH - 2 << endl;
                    cout << "La altura máxima permitida es: " << SCREEN_HEIGHT - 2 << endl;
                    break;
                }
                dibujarRectangulo(x, y, ancho, alto, true);
                break;
            case 2:
                cout << "Ingresa el tamaño de la base del triangulo: ";
                int base;
                cin >> base;
                if (base > SCREEN_WIDTH - 2 || base > SCREEN_HEIGHT - 2) {
                    cout << "El tamaño de la base del triángulo es demasiado grande para dibujar." << endl;
                    cout << "El tamaño máximo permitido es: " << min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) << endl;
                    break;
                }
                drawEquilateralTriangle(base, x, y);
                break;
            case 3:
                cout << "Ingresa el radio del circulo: ";
                cin >> radio;
                if (radio > min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) / 2) {
                    cout << "El radio del círculo es demasiado grande para dibujar." << endl;
                    cout << "El radio máximo permitido es: " << min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) / 2 << endl;
                    break;
                }
                drawCircle(radio, x, y);
                break;
            case 4:
                cout << "Ingresa el tamaño de un lado del cuadrado: ";
                cin >> lado;
                if (lado > min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2)) {
                    cout << "El tamaño del cuadrado es demasiado grande para dibujar." << endl;
                    cout << "El tamaño máximo permitido es: " << min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) << endl;
                    break;
                }
                dibujarCuadrado(x, y, lado);
                break;
            default:
                cout << "Opcion invalida!" << endl;
        }
        limpiarLinea(25);
        limpiarLinea(26);
        limpiarLinea(27);
        limpiarLinea(28);
        limpiarLinea(29);
        limpiarLinea(30);
        limpiarLinea(31);
        limpiarLinea(32);
        limpiarLinea(33);
        limpiarLinea(34);
        gotoxy(0, 26);
        cout << "¿Deseas dibujar otra forma? (S/N): ";
        cin >> eleccion;
    } while (eleccion == 'S' || eleccion == 's');

    return 0;
}
