#include <stdio.h>
#include <stdlib.h>

#include "includes/convert.h"

void blockTo64(char block[8], char block64[64]) {
    char *ptr;
    int i, j;
    for (ptr = block, j = 0; j < 64; ++ptr)
        for (i = 7; i >= 0; --i, ++j)
            block64[j] = (*ptr & 1 << i) ? '1' : '0';
}

char getHex(char b3, char b2, char b1, char b0) {
    int value = 0;
    if (b3 == '1')  ++value;
    value *= 2;
    if (b2 == '1')  ++value;
    value *= 2;
    if (b1 == '1')  ++value;
    value *= 2;
    if (b0 == '1')  ++value;

    switch (value) {
        case 0:  return '0';
        case 1:  return '1';
        case 2:  return '2';
        case 3:  return '3';
        case 4:  return '4';
        case 5:  return '5';
        case 6:  return '6';
        case 7:  return '7';
        case 8:  return '8';
        case 9:  return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default:
            printf("Error! getHex value is out of bounds");
            exit(1);
    }
}

void binaryToHex(char binary[64], char hex[16]) {
    for (int i = 0; i < 16; ++i) {
        int h = i * 4;
        hex[i] = getHex(binary[h], binary[h + 1], binary[h + 2], binary[h + 3]);
    }
}

void hexTo64(const char blockHex[16], char block64[64]) {
    for (int i = 0; i < 16; ++i) {
        int b = i * 4;
        switch (blockHex[i]) {
            case '0':
                block64[b + 0] = '0';
                block64[b + 1] = '0';
                block64[b + 2] = '0';
                block64[b + 3] = '0';
                break;
            case '1':
                block64[b + 0] = '0';
                block64[b + 1] = '0';
                block64[b + 2] = '0';
                block64[b + 3] = '1';
                break;
            case '2':
                block64[b + 0] = '0';
                block64[b + 1] = '0';
                block64[b + 2] = '1';
                block64[b + 3] = '0';
                break;
            case '3':
                block64[b + 0] = '0';
                block64[b + 1] = '0';
                block64[b + 2] = '1';
                block64[b + 3] = '1';
                break;
            case '4':
                block64[b + 0] = '0';
                block64[b + 1] = '1';
                block64[b + 2] = '0';
                block64[b + 3] = '0';
                break;
            case '5':
                block64[b + 0] = '0';
                block64[b + 1] = '1';
                block64[b + 2] = '0';
                block64[b + 3] = '1';
                break;
            case '6':
                block64[b + 0] = '0';
                block64[b + 1] = '1';
                block64[b + 2] = '1';
                block64[b + 3] = '0';
                break;
            case '7':
                block64[b + 0] = '0';
                block64[b + 1] = '1';
                block64[b + 2] = '1';
                block64[b + 3] = '1';
                break;
            case '8':
                block64[b + 0] = '1';
                block64[b + 1] = '0';
                block64[b + 2] = '0';
                block64[b + 3] = '0';
                break;
            case '9':
                block64[b + 0] = '1';
                block64[b + 1] = '0';
                block64[b + 2] = '0';
                block64[b + 3] = '1';
                break;
            case 'A':
                block64[b + 0] = '1';
                block64[b + 1] = '0';
                block64[b + 2] = '1';
                block64[b + 3] = '0';
                break;
            case 'B':
                block64[b + 0] = '1';
                block64[b + 1] = '0';
                block64[b + 2] = '1';
                block64[b + 3] = '1';
                break;
            case 'C':
                block64[b + 0] = '1';
                block64[b + 1] = '1';
                block64[b + 2] = '0';
                block64[b + 3] = '0';
                break;
            case 'D':
                block64[b + 0] = '1';
                block64[b + 1] = '1';
                block64[b + 2] = '0';
                block64[b + 3] = '1';
                break;
            case 'E':
                block64[b + 0] = '1';
                block64[b + 1] = '1';
                block64[b + 2] = '1';
                block64[b + 3] = '0';
                break;
            case 'F':
                block64[b + 0] = '1';
                block64[b + 1] = '1';
                block64[b + 2] = '1';
                block64[b + 3] = '1';
                break;
            default:
                printf("Error! blockHex is out of bounds");
                exit(1);
        }
    }
}

int getValue(char ch) {
    if(ch >= '0' && ch <= '9') {
        return ch - '0';
    } else {
        switch(ch) {
            case 'A': return 10;
            case 'B': return 11;
            case 'C': return 12;
            case 'D': return 13;
            case 'E': return 14;
            case 'F': return 15;
            default:
                printf("Error! ch in getValue is out of bounds");
                exit(1);
        }
    }
}

void hexToText(char decryptedHex[16], char decrypted[8]) {
    for (int i = 0; i < 8; ++i) {
        int first =  getValue(decryptedHex[i * 2]) * 16;
        int second = getValue(decryptedHex[i * 2 + 1]);
        decrypted[i] = (char) (first + second);
    }
}