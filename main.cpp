//
//  main.cpp
//  Rijndael
//
//  Created by jonas on 12/03/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

int S_caja[16][16] = {0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
                      0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
                      0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
                      0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
                      0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
                      0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
                      0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
                      0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
                      0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
                      0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
                      0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
                      0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
                      0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
                      0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
                      0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
                      0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16};
int klave[4][4] = {0x00,0x04,0x08,0x0c,
                   0x01,0x05,0x09,0x0d,
                   0x02,0x06,0x0a,0x0e,
                   0x03,0x07,0x0b,0x0f};
int mensaje[4][4] = {0x00,0x44,0x88,0xcc,
                   0x11,0x55,0x99,0xdd,
                   0x22,0x66,0xaa,0xee,
                   0x33,0x77,0xbb,0xff};
int Rcon[4][10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};


void dividir_hexadecimal(int hex, int& d, int& i){
    d = hex/0x10;
    i = hex%0x10;
}
void imprimir_mensaje(){
    cout << setfill('0');
    for (int i = 0 ; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << setw(2) << uppercase << mensaje[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void imprimir_Key(){
    cout << setfill('0');
    for (int i = 0 ; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << setw(2) << uppercase << klave[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int xtime(int valor){
    //desplaza un bit hacia la izquierda y suma el valor a 0x11b que es el valor del polinomio
    valor=valor<<1;
    if (valor & 0x100) {
        valor=valor^0x11b;
    }
    return valor;
}
void binario2(int n, int p, int* v){
    if (p != 8) {
        if (n != 0) {
            binario2(n/2, p+1, v);
            //printf("%i",n%2);
            v[p] = n%2;
        }
        if (n == 0) {
            binario2(n/2, p+1, v);
            //printf("%i",0);
            v[p] = 0;
        }
    }
}
void mostrarBinario(int* v){
    for (int i = 7;  i >= 0; i=i-1) {
        cout << v[i];
    }
}
void mostrarResultado(){
    cout << setfill('0');
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 ; j++) {
            cout << hex << setw(2) << nouppercase << mensaje[i][j];
        }
    }
    cout << endl << endl;
}


//Proceso de encriptación A
void AddRoundKey(){
    //Recorre cada una de las celdas de la matriz del mensaje y hace un XOR con cada una de las celdas de la clave
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 4; j++) {
            mensaje[i][j] = mensaje[i][j] ^ klave[i][j];
        }
    }
}
void SubBytes(){
    //Recorre cada una de las celdas del mensaje, divide cada celda en dos (8 bits en 4 y 4) y coloca en el mensaje el valor que den esos datos en la caja S.
    int r,l;
    for (int i = 0; i < 4; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            dividir_hexadecimal(mensaje[i][j], r, l);
            mensaje[i][j] = S_caja[r][l];
        }
    }
}
void ShiftRows(){
    //Rueda en la segunda fila 1, en la segunda 2 y en la tercera 3 elementos a la derecha.
    int tmp;
    tmp = mensaje[1][0];
    mensaje[1][0] = mensaje[1][1];
    mensaje[1][1] = mensaje[1][2];
    mensaje[1][2] = mensaje[1][3];
    mensaje[1][3] = tmp;
    int tmp2[2];
    tmp2[0] = mensaje[2][0];
    tmp2[1] = mensaje[2][1];
    mensaje[2][0] = mensaje[2][2];
    mensaje[2][1] = mensaje[2][3];
    mensaje[2][2] = tmp2[0];
    mensaje[2][3] = tmp2[1];
    int tmp3[3];
    tmp3[0] = mensaje[3][0];
    tmp3[1] = mensaje[3][1];
    tmp3[2] = mensaje[3][2];
    mensaje[3][0] = mensaje[3][3];
    mensaje[3][1] = tmp3[0];
    mensaje[3][2] = tmp3[1];
    mensaje[3][3] = tmp3[2];
}
void MixColumns(){
    //multiplicación de la matriz mensaje por los campos de Galois mediante el uso de la función xtime
    int a,b,c,d;
    for (int i = 0; i < 4; i++) {
        a = (((xtime(mensaje[0][i])) ^ (xtime(mensaje[1][i])^mensaje[1][i])) ^ ((mensaje[2][i]) ^ (mensaje[3][i])));
        b = ((mensaje[0][i]) ^ (xtime(mensaje[1][i]))) ^ ((xtime(mensaje[2][i])^(mensaje[2][i])) ^ (mensaje[3][i]));
        c = mensaje[0][i] ^ mensaje[1][i] ^ (xtime(mensaje[2][i])) ^ (xtime(mensaje[3][i])^mensaje[3][i]);
        d = (xtime(mensaje[0][i])^mensaje[0][i]) ^ mensaje[1][i] ^ mensaje[2][i] ^ (xtime(mensaje[3][i]));
        mensaje[0][i] = a;
        mensaje[1][i] = b;
        mensaje[2][i] = c;
        mensaje[3][i] = d;
    }
}

//Programación de la clave B
void KeySchedule(int RC){
    //Primero desplaza hacia abajo la primera columna. y cada una de las celdas de esa columna la utiliza para crear una nueva en base a la caja S.
    //Después suma la primera columna con la última junto con la constante de Rijndael.
    //A continuación va sumando cada una de las columnas entre si, segunda con primera, da la segunda, tercera con segunda da la tercera y cuarta con tercera da la cuarta.
    int r,l;
    int tmp = klave[0][3];
    int tmpv1[4];
    tmpv1[0] = klave[1][3];
    tmpv1[1] = klave[2][3];
    tmpv1[2] = klave[3][3];
    tmpv1[3] = tmp;
    int tmpv[4];
    for (int i = 0; i < 4 ; i++) {
        dividir_hexadecimal(tmpv1[i], r, l);
        tmpv[i] = S_caja[r][l];
    }
    
    for (int i = 0; i < 4; i++) {
        klave[i][0] = klave[i][0] ^ tmpv[i] ^ Rcon[i][RC];
    }
    for (int i = 0; i < 4; i++) {
        klave[i][1] = klave[i][1] ^ klave[i][0];
    }
    for (int i = 0; i < 4; i++) {
        klave[i][2] = klave[i][2] ^ klave[i][1];
    }
    for (int i = 0; i < 4; i++) {
        klave[i][3] = klave[i][3] ^ klave[i][2];
    }
}


int main()
{
    /*cout << "Introduce la clave: (16 bytes, ¡¡introducir por parejas!!)" << endl;
    int count = 1;
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "byte " << count << ": ";
            cin >> hex >> klave[i][j];
            count = count + 1;
        }
    }
    cout << "Introduce el bloque de texto original: (16 bytes, ¡¡introducir por parejas!!)" << endl;
    count = 1;
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "byte " << count << ": ";
            cin >> hex >> mensaje[i][j];
            count = count + 1;
        }
    }*/
    //inicialización
    AddRoundKey();
    //rondas de la 1 a la 9
    for (int i = 0; i < 9; i++) {
        SubBytes();
        ShiftRows();
        MixColumns();
        KeySchedule(i);
        AddRoundKey();
    }
    //ronda 10
    SubBytes();
    ShiftRows();
    KeySchedule(9);
    AddRoundKey();
    
    //imprimir_mensaje();
    mostrarResultado();
    return 0;
}

