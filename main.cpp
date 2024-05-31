#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 85;
const int SCREEN_HEIGHT = 25;
vector<string> pantalla(SCREEN_HEIGHT, string(SCREEN_WIDTH, ' '));

char caracterDibujo = '*';
int colorCaracter = FOREGROUND_RED | FOREGROUND_INTENSITY;

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
        pantalla[0][i] = '-';

        gotoxy(i, SCREEN_HEIGHT - 1);
        cout << "-";
        pantalla[SCREEN_HEIGHT - 1][i] = '-';
    }

    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        gotoxy(0, j);
        cout << "|";
        pantalla[j][0] = '|';

        gotoxy(SCREEN_WIDTH - 1, j);
        cout << "|";
        pantalla[j][SCREEN_WIDTH - 1] = '|';
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
                cout << caracterDibujo;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                cout << caracterDibujo;
            } else {
                cout << " ";
            }

            if ((i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) && green) {
                pantalla[currentY][currentX] = caracterDibujo;
            } else if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                pantalla[currentY][currentX] = caracterDibujo;
            } else {
                pantalla[currentY][currentX] = ' ';
            }
        }
    }
}

void drawCircle(int radius, int centerX, int centerY) {
    if (radius < 1) return;
    int x = radius, y = 0, P = 1 - radius;
    auto plotPoints = [&](int xCenter, int yCenter, int X, int Y) {
        auto plot = [&](int x, int y) {
            int adjustedX = adjustX(x);
            int adjustedY = adjustY(y);
            gotoxy(adjustedX, adjustedY);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << '*';
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            pantalla[adjustedY][adjustedX] = '*';
        };

        plot(xCenter + X, yCenter + Y);
        plot(xCenter - X, yCenter + Y);
        plot(xCenter + X, yCenter - Y);
        plot(xCenter - X, yCenter - Y);
        plot(xCenter + Y, yCenter + X);
        plot(xCenter - Y, yCenter + X);
        plot(xCenter + Y, yCenter - X);
        plot(xCenter - Y, yCenter - X);
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
        cout << caracterDibujo;
        pantalla[adjustY(y + row)][adjustX(x1)] = caracterDibujo;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        gotoxy(adjustX(x2), adjustY(y + row));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << caracterDibujo;
        pantalla[adjustY(y + row)][adjustX(x2)] = caracterDibujo;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if (row == height) {
            for (int col = x1 + 1; col < x2; ++col) {
                gotoxy(adjustX(col), adjustY(y + row));
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << caracterDibujo;
                pantalla[adjustY(y + row)][adjustX(col)] = caracterDibujo;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
        }
    }
}

void dibujarCuadrado(int x, int y, int lado) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {
            int cx = adjustX(x + j);
            int cy = adjustY(y + i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }
    }
}

void dibujarLinea(int x, int y, int longitud, int orientacion) {
    for (int i = 0; i < longitud; ++i) {
        gotoxy(adjustX(x), adjustY(y));
        cout << caracterDibujo;
        pantalla[adjustY(y)][adjustX(x)] = caracterDibujo;
        switch (orientacion) {
            case 1: y--; break;
            case 2: y++; break;
            case 3: x++; break;
            case 4: x--; break;
        }

        x = adjustX(x);
        y = adjustY(y);
    }
}


void dibujarRombo(int x, int y, int lado, bool orientacionArriba) {
    int dx = 0;
    int dy = orientacionArriba ? -1 : 1;

    for (int i = 0; i <= lado; ++i) {
        gotoxy(adjustX(x + dx), adjustY(y + dy * i));
        cout << caracterDibujo;
        pantalla[adjustY(y + dy * i)][adjustX(x + dx)] = caracterDibujo;
        gotoxy(adjustX(x - dx), adjustY(y + dy * i));
        cout << caracterDibujo;
        pantalla[adjustY(y + dy * i)][adjustX(x - dx)] = caracterDibujo;
        dx++;
    }

    dx = lado - 1;
    for (int i = lado + 1; i <= 2 * lado; ++i) {
        gotoxy(adjustX(x + dx), adjustY(y + dy * i));
        cout << caracterDibujo;
        pantalla[adjustY(y + dy * i)][adjustX(x + dx)] = caracterDibujo;
        gotoxy(adjustX(x - dx), adjustY(y + dy * i));
        cout << caracterDibujo;
        pantalla[adjustY(y + dy * i)][adjustX(x - dx)] = caracterDibujo;
        dx--;
    }
}

void dibujarHexagono(int x, int y, int lado, bool orientacionVertical) {
    if (orientacionVertical) {

        for (int i = 0; i <= lado / 2; ++i) {
            int cx = adjustX(x - lado / 2 + i);
            int cy = adjustY(y - i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = 0; i <= lado / 2; ++i) {
            int cx = adjustX(x + lado / 2 - i);
            int cy = adjustY(y - i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = 1; i < lado; ++i) {
            int cx = adjustX(x - lado);
            int cy = adjustY(y - lado / 2 + i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = 1; i < lado; ++i) {
            int cx = adjustX(x + lado);
            int cy = adjustY(y - lado / 2 + i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = lado / 2; i >= 0; --i) {
            int cx = adjustX(x - lado / 2 + i);
            int cy = adjustY(y + (lado - i));
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = lado / 2; i >= 0; --i) {
            int cx = adjustX(x + lado / 2 - i);
            int cy = adjustY(y + (lado - i));
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }
    } else {

        for (int i = 0; i <= lado / 2; ++i) {
            int cx = adjustX(x - lado + i);
            int cy = adjustY(y - lado / 2 + i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = 0; i <= lado / 2; ++i) {
            int cx = adjustX(x + lado - i);
            int cy = adjustY(y - lado / 2 + i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = 1; i < lado; ++i) {
            int cx = adjustX(x - lado / 2 + i);
            int cy = adjustY(y - lado);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = 1; i < lado; ++i) {
            int cx = adjustX(x - lado / 2 + i);
            int cy = adjustY(y + lado);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = lado / 2; i >= 0; --i) {
            int cx = adjustX(x - lado + i);
            int cy = adjustY(y + lado / 2 - i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
        }

        for (int i = lado / 2; i >= 0; --i) {
            int cx = adjustX(x + lado - i);
            int cy = adjustY(y + lado / 2 - i);
            gotoxy(cx, cy);
            cout << caracterDibujo;
            pantalla[cy][cx] = caracterDibujo;
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

void limpiarPantalla() {
    system("cls");
}

void grabarPantalla(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const string& linea : pantalla) {
            file << linea << endl;
        }
        file.close();
        cout << "Pantalla grabada exitosamente en " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}

void abrirArchivo(const string& filename) {
    ifstream file(filename);
    string line;
    int y = 0;
    if (file.is_open()) {
        while (getline(file, line) && y < SCREEN_HEIGHT) {
            pantalla[y] = line;
            gotoxy(0, y);
            cout << line;
            ++y;
        }
        file.close();
    }
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

void cambiarCaracter() {
    cout << "Ingresa el nuevo caracter para dibujar: ";
    cin >> caracterDibujo;
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void cambiarColor() {
    cout << "Selecciona el color del caracter:\n";
    cout << "1. Rojo\n";
    cout << "2. Verde\n";
    cout << "3. Azul\n";
    cout << "4. Amarillo\n";
    cout << "5. Blanco\n";
    int opcion;
    cin >> opcion;
    switch (opcion) {
        case 1: colorCaracter = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
        case 2: colorCaracter = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case 3: colorCaracter = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        case 4: colorCaracter = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case 5: colorCaracter = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        default: colorCaracter = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
    }
    setColor(colorCaracter);
}

int main() {
    int x = 0, y = 0;
    int lado, ancho, alto, radio, base, orientacion;
    char eleccion;
    setColor(colorCaracter);
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
        /*cout << "Selecciona la forma a dibujar con las teclas F1-F12, Ctrl + A para abrir un archivo.";
        int opcion = _getch();
        if (opcion == 0 || opcion == 224) {
            opcion = _getch();
        }*/
        cout << "Selecciona la forma a dibujar con las teclas F1-F12, Ctrl + A para abrir un archivo." << endl;
        cout << "F1. Triangulo" << endl;
        cout << "F2. Cuadrado" << endl;
        cout << "F3. Rectangulo" << endl;
        cout << "F4. Circulo" << endl;
        cout << "F5. Linea" << endl;
        cout << "F6. Rombo" << endl;
        cout << "F7. Hexagono" << endl;
        cout << "F8. Nuevo Caracter" << endl;
        cout << "F9. Limpiar Pantalla" << endl;
        cout << "F10. Color de Caracter" << endl;
        cout << "F12. Grabar Pantalla" << endl;
        cout << "Ctrl + A. Abrir archivo y mostrar en pantalla" << endl;

        int opcion = _getch();
        if (opcion == 0 || opcion == 224) {
            opcion = _getch();
        }
        if (opcion == 1 && (GetKeyState(VK_CONTROL) & 0x8000)) {
            cout << "Ingresa el nombre del archivo para abrir (con extencion txt): ";
            string filename;
            cin >> filename;
            abrirArchivo(filename);
        } else {

            switch(opcion) {
            case 61:
                cout << "Ingresa el ancho y la altura del rectangulo: ";
                cin >> ancho >> alto;
                if (ancho > SCREEN_WIDTH - 2 || alto > SCREEN_HEIGHT - 2) {
                    cout << "Los datos ingresados son demasiado grandes para dibujar un rectangulo." << endl;
                    cout << "El ancho maximo permitido es: " << SCREEN_WIDTH - 2 << endl;
                    cout << "La altura maxima permitida es: " << SCREEN_HEIGHT - 2 << endl;
                    break;
                }
                dibujarRectangulo(x, y, ancho, alto, true);
                break;
            case 59:
                cout << "Ingresa el tamano de la base del triangulo: ";
                int base;
                cin >> base;
                if (base > SCREEN_WIDTH - 2 || base > SCREEN_HEIGHT - 2) {
                    cout << "El tamano de la base del triangulo es demasiado grande para dibujar." << endl;
                    cout << "El tamano maximo permitido es: " << min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) << endl;
                    break;
                }
                drawEquilateralTriangle(base, x, y);
                break;
            case 62:
                cout << "Ingresa el radio del circulo: ";
                cin >> radio;
                if (radio > min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) / 2) {
                    cout << "El radio del círculo es demasiado grande para dibujar." << endl;
                    cout << "El radio maximo permitido es: " << min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) / 2 << endl;
                    break;
                }
                drawCircle(radio, x, y);
                break;
            case 60:
                cout << "Ingresa el tamano de un lado del cuadrado: ";
                cin >> lado;
                if (lado > min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2)) {
                    cout << "El tamano del cuadrado es demasiado grande para dibujar." << endl;
                    cout << "El tamano maximo permitido es: " << min(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2) << endl;
                    break;
                }
                dibujarCuadrado(x, y, lado);
                break;
            case 63:
                cout << "Ingresa la longitud de la linea y la orientacion (1=Arriba, 2=Abajo, 3=Derecha, 4=Izquierda): ";
                cin >> lado >> orientacion;
                dibujarLinea(x, y, lado, orientacion);
                break;
            case 64:
                cout << "Ingresa el tamano de un lado del rombo y la orientacion (0=Abajo, 1=Arriba): ";
                cin >> lado >> orientacion;;
                dibujarRombo(x, y, lado, orientacion);
                break;
            case 65:
                cout << "Ingresa el tamano de un lado del hexagono y la orientacion (0=Horizontal, 1=Vertical): ";
                cin >> lado >> orientacion;
                dibujarHexagono(x, y, lado, orientacion == 1);
                break;
            case 66:
                cambiarCaracter();
                break;
            case 67:
                limpiarPantalla();
                break;
            case 68:
                cambiarColor();
                break;
            case 134: {

                cout << "Ingresa el nombre del archivo para grabar la pantalla: ";
                string filename;
                cin >> filename;
                grabarPantalla(filename);

                break;

            }

            case 1: {
                if (_getch() == 1) {
                    string filename;
                    cout << "Ingresa el nombre del archivo para abrir: ";
                    cin >> filename;
                    abrirArchivo(filename);
                }
                break;
            }

            default:
                cout << "Opción invalida! Tecla presionada: " << endl;
        }

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
        limpiarLinea(35);
        limpiarLinea(36);
        limpiarLinea(37);
        limpiarLinea(38);
        limpiarLinea(39);
        limpiarLinea(40);
        limpiarLinea(41);
        limpiarLinea(42);
        limpiarLinea(43);
        limpiarLinea(44);
        limpiarLinea(45);
        gotoxy(0, 26);
        cout << "¿Deseas dibujar otra forma? (S/N): ";
        cin >> eleccion;
    } while (eleccion == 'S' || eleccion == 's');

    return 0;
}

