# Manual Técnico del Programa de Dibujo en Consola

## Descripción General
Este programa permite dibujar varias figuras geométricas en la consola utilizando caracteres ASCII. Los usuarios pueden mover un cursor, seleccionar diferentes formas para dibujar, cambiar el carácter de dibujo y el color del texto, limpiar la pantalla, y guardar el contenido de la pantalla en un archivo de texto.

## Dependencias
El programa utiliza las siguientes librerías:
- `iostream` para operaciones de entrada y salida.
- `conio.h` para la detección de teclas.
- `windows.h` para la manipulación de la consola en Windows.
- `fstream` para la lectura y escritura de archivos.
- `vector` para el manejo de la pantalla como una matriz de caracteres.

## Constantes
- `SCREEN_WIDTH`: Ancho de la pantalla de la consola.
- `SCREEN_HEIGHT`: Alto de la pantalla de la consola.

## Variables Globales
- `pantalla`: Vector de cadenas que representa el contenido actual de la pantalla.
- `caracterDibujo`: Carácter utilizado para dibujar las figuras.
- `colorCaracter`: Color del carácter de dibujo en la consola.

## Funciones

### Ajuste de Coordenadas
- `int adjustX(int x)`: Ajusta las coordenadas X para asegurarse de que estén dentro del límite de la pantalla.
- `int adjustY(int y)`: Ajusta las coordenadas Y para asegurarse de que estén dentro del límite de la pantalla.

### Control de la Consola
- `void gotoxy(int x, int y)`: Mueve el cursor a la posición (x, y) en la consola.
- `void setColor(int color)`: Establece el color del texto en la consola.

### Dibujo de Figuras
- `void dibujarBorde()`: Dibuja el borde de la pantalla.
- `void dibujarRectangulo(int x, int y, int ancho, int alto, bool green = false)`: Dibuja un rectángulo en la posición especificada con un tamaño dado.
- `void drawCircle(int radius, int centerX, int centerY)`: Dibuja un círculo con un radio y un centro especificados.
- `void drawEquilateralTriangle(int base, int x, int y)`: Dibuja un triángulo equilátero con una base dada.
- `void dibujarCuadrado(int x, int y, int lado)`: Dibuja un cuadrado en la posición especificada con un tamaño dado.
- `void dibujarLinea(int x, int y, int longitud, int orientacion)`: Dibuja una línea en la dirección especificada.
- `void dibujarRombo(int x, int y, int lado, bool orientacionArriba)`: Dibuja un rombo con un tamaño de lado especificado y orientación (arriba o abajo).
- `void dibujarHexagono(int x, int y, int lado, bool orientacionVertical)`: Dibuja un hexágono con un tamaño de lado especificado y orientación (vertical u horizontal).

### Manipulación de la Pantalla
- `void limpiarMenu(int desde, int hasta)`: Limpia el menú en las líneas especificadas.
- `void limpiarLinea(int y)`: Limpia una línea especificada en la pantalla.
- `void limpiarPantalla()`: Limpia toda la pantalla.
- `void grabarPantalla(const string& filename)`: Guarda el contenido actual de la pantalla en un archivo de texto.
- `void abrirArchivo(const string& filename)`: Abre un archivo de texto y lo muestra en la pantalla.

### Interacción del Usuario
- `void cambiarCaracter()`: Permite al usuario cambiar el carácter de dibujo.
- `void cambiarColor()`: Permite al usuario cambiar el color del carácter de dibujo.

## Main Loop
El bucle principal del programa permite al usuario mover el cursor con las teclas de flecha y seleccionar diferentes figuras para dibujar mediante teclas de función (F1-F12). También proporciona opciones para abrir archivos, cambiar el carácter de dibujo, cambiar el color, y guardar la pantalla actual.

## Teclas de Función
- `F1`: Dibuja un triángulo.
- `F2`: Dibuja un cuadrado.
- `F3`: Dibuja un rectángulo.
- `F4`: Dibuja un círculo.
- `F5`: Dibuja una línea.
- `F6`: Dibuja un rombo.
- `F7`: Dibuja un hexágono.
- `F8`: Cambia el carácter de dibujo.
- `F9`: Limpia la pantalla.
- `F10`: Cambia el color del carácter.
- `F12`: Guarda la pantalla en un archivo.
- `Ctrl + A`: Abre un archivo y muestra su contenido en la pantalla.

## Ejecución
Para compilar y ejecutar el programa, utiliza un compilador compatible con C++ en Windows, ya que el programa depende de la biblioteca `windows.h`. 

```sh
g++ -o dibujar dibujar.cpp -static-libgcc -static-libstdc++
./dibujar
