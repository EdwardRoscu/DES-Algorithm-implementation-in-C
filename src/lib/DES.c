#include <stdio.h>
#include <stdlib.h>
#include "includes/convert.h"

#include "includes/DES.h"

//////////////////////////////////////////////////     Step 1     //////////////////////////////////////////////////

const int PC1[] = { 57, 49, 41, 33, 25, 17,  9,
                    1, 58, 50, 42, 34, 26, 18,
                    10,  2, 59, 51, 43, 35, 27,
                    19, 11,  3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                    14,  6, 61, 53, 45, 37, 29,
                    21, 13,  5, 28, 20, 12,  4  };

void key64to56(const char key64[64], char key56[56]) {
    for (int i = 0; i < 56; ++i)
        key56[i] = key64[PC1[i] - 1];
}

void splitKey56(const char key56[56], char C[28], char D[28]) {
    for (int i = 0; i < 28; ++i) {
        C[i] = key56[i];
        D[i] = key56[i + 28];
    }
}

void shiftLeft(const char source[28], char destination[28]) {
    for (int i = 0; i < 27; ++i) {
        destination[i] = source[i + 1];
    }
    destination[27] = source[0];
}

void shiftLeftTwice(const char source[28], char destination[28]) {
    for (int i = 0; i < 27; ++i) {
        destination[i] = source[i + 2];
    }
    destination[26] = source[0];
    destination[27] = source[1];
}

const int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void generatePairsCD(char C[17][28], char D[17][28]) {
    for (int i = 0; i < 16; ++i)
        if (SHIFTS[i] == 1) {
            shiftLeft(C[i], C[i + 1]);
            shiftLeft(D[i], D[i + 1]);
        } else {
            shiftLeftTwice(C[i], C[i + 1]);
            shiftLeftTwice(D[i], D[i + 1]);
        }
}

const int PC2[] = { 14, 17, 11, 24,  1,  5,
                    3, 28, 15,  6, 21, 10,
                    23, 19, 12,  4, 26,  8,
                    16,  7, 27, 20, 13,  2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32  };

void formKeys(char subkeys[16][48], const char C[17][28], const char D[17][28]) {
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 48; ++j)
            if (PC2[j] <= 28) {
                subkeys[i][j] = C[i + 1][PC2[j] - 1];
            } else {
                subkeys[i][j] = D[i + 1][PC2[j] % 29];
            }
}

void create_subkeys(char key[8], char subkeys[16][48])
//Step 1: Create 16 subkeys, each of which is 48-bits long.
{
    char key64[64];
    char key56[56];
    char C[17][28];
    char D[17][28];

    blockTo64(key, key64);
    key64to56(key64, key56);
    splitKey56(key56, C[0], D[0]);
    generatePairsCD(C, D);
    formKeys(subkeys, C, D);
}

//////////////////////////////////////////////     End of Step 1     ///////////////////////////////////////////////

//////////////////////////////////////////////////     Step 2     //////////////////////////////////////////////////

const int IP[] = {  58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17,  9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7   };

void applyIP(const char block64[64], char block64IP[64]) {
    for (int i = 0; i < 64; ++i)
        block64IP[i] = block64[IP[i] - 1];
}

void splitBlock64IP(const char block64IP[64], char L[32], char R[32]) {
    for (int i = 0; i < 32; ++i) {
        L[i] = block64IP[i];
        R[i] = block64IP[i + 32];
    }
}

void copyR(char Li1[32], const char Ri[32]) {
    for (int i = 0; i < 32; ++i)
        Li1[i] = Ri[i];
}

const int E[] = {   32,  1,  2,  3,  4,  5,
                    4,  5,  6,  7,  8,  9,
                    8,  9, 10, 11, 12, 13,
                    12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21,
                    20, 21, 22, 23, 24, 25,
                    24, 25, 26, 27, 28, 29,
                    28, 29, 30, 31, 32,  1  };

void expandR(const char Ri[32], char ER[48]) {
    for (int i = 0; i < 48; ++i)
        ER[i] = Ri[E[i] - 1];
}

void XOR1(const char subkeyi[48], const char ER[48], char X[48]) {
    for (int i = 0; i < 48; ++i)
        X[i] = (subkeyi[i] != ER[i]) ? '1' : '0';
}

const int S1[4][16] = { { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7 },
                        {  0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8 },
                        {  4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0 },
                        { 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 }  };

const int S2[4][16] = { { 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10 },
                        {  3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5 },
                        {  0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15 },
                        { 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 }  };

const int S3[4][16] = { { 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 },
                        { 13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1 },
                        { 13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7 },
                        {  1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 }  };

const int S4[4][16] = { {  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15 },
                        { 13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9 },
                        { 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4 },
                        {  3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 }  };

const int S5[4][16] = { {  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9 },
                        { 14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6 },
                        {  4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14 },
                        { 11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 }  };

const int S6[4][16] = { { 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 },
                        { 10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8 },
                        {  9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6 },
                        {  4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 }  };

const int S7[4][16] = { {  4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1 },
                        { 13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6 },
                        {  1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2 },
                        {  6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 }  };

const int S8[4][16] = { { 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 },
                        {  1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2 },
                        {  7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8 },
                        {  2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 }  };

void SBtoBits(int value, char SB[4]) {
    SB[0] = ((value >> 3) & 1) ? '1' : '0';
    SB[1] = ((value >> 2) & 1) ? '1' : '0';
    SB[2] = ((value >> 1) & 1) ? '1' : '0';
    SB[3] = ((value >> 0) & 1) ? '1' : '0';
}

int getRow(char b1, char b0) {
    int index = 0;
    if (b1 == '1')  ++index;
    index *= 2;
    if (b0 == '1')  ++index;
    return index;
}

int getColumn(char b3, char b2, char b1, char b0) {
    int index = 0;
    if (b3 == '1')  ++index;
    index *= 2;
    if (b2 == '1')  ++index;
    index *= 2;
    if (b1 == '1')  ++index;
    index *= 2;
    if (b0 == '1')  ++index;
    return index;
}

void calculateSB(int index, char X[48], char SB[4]) {
    int row = getRow(X[index * 6], X[index * 6 + 5]);
    int column = getColumn(X[index * 6 + 1],X[index * 6 + 2],X[index * 6 + 3],X[index * 6 + 4]);
    switch (index + 1) {
        case 1:
            SBtoBits(S1[row][column], SB);
            break;
        case 2:
            SBtoBits(S2[row][column], SB);
            break;
        case 3:
            SBtoBits(S3[row][column], SB);
            break;
        case 4:
            SBtoBits(S4[row][column], SB);
            break;
        case 5:
            SBtoBits(S5[row][column], SB);
            break;
        case 6:
            SBtoBits(S6[row][column], SB);
            break;
        case 7:
            SBtoBits(S7[row][column], SB);
            break;
        case 8:
            SBtoBits(S8[row][column], SB);
            break;
        default:
            printf("Error! index in calculateSB is out of bounds");
            exit(1);
    }
}

void transform(char X[48], char S[32]) {
    for (int i = 0; i < 8; ++i) {
        char SB[4];
        calculateSB(i, X, SB);
        S[4 * i + 0] = SB[0];
        S[4 * i + 1] = SB[1];
        S[4 * i + 2] = SB[2];
        S[4 * i + 3] = SB[3];
    }
}

const int P[] = {   16,  7, 20, 21,
                    29, 12, 28, 17,
                     1, 15, 23, 26,
                     5, 18, 31, 10,
                     2,  8, 24, 14,
                    32, 27,  3,  9,
                    19, 13, 30,  6,
                    22, 11,  4, 25  };

void permuteR(char Ri1[32], const char S[32]) {
    for (int i = 0; i < 32; ++i)
        Ri1[i] = S[P[i] - 1];
}

void f_function(char *subkeyi, char *Ri, char *Ri1) {
    char ER[48];
    char X[48];
    char S[32];
    expandR(Ri, ER);
    XOR1(subkeyi, ER, X);
    transform(X, S);
    permuteR(Ri1, S);
}

void XOR2(const char Li[32], char Ri1[32]) {
    for (int i = 0; i < 32; ++i)
        Ri1[i] = (Ri1[i] != Li[i]) ? '1' : '0';
}

void generatePairsLR(char subkeys[16][48], char L[17][32], char R[17][32]) {
    for (int i = 0; i < 16; ++i) {
        copyR(L[i + 1], R[i]);
        f_function(subkeys[i], R[i], R[i + 1]);
        XOR2(L[i], R[i + 1]);
    }
}

const int FP[] = {  40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41,  9, 49, 17, 57, 25   };

void applyFP(char cipher64[64], const char L[32], const char R[32]) {
    for (int i = 0; i < 64; ++i)
        if (FP[i] <= 32) {
            cipher64[i] = R[FP[i] - 1];
        } else {
            cipher64[i] = L[FP[i] % 33];
        }
}

void encode_block(char block[8], char subkeys[16][48], char blockHex[16], char cipherHex[16])
//Step 2: Encode each 64-bit block of data.
{
    char block64[64];
    char block64IP[64];
    char L[17][32];
    char R[17][32];
    char cipher64[64];

    blockTo64(block, block64);
    applyIP(block64, block64IP);
    splitBlock64IP(block64IP, L[0], R[0]);
    generatePairsLR(subkeys, L, R);
    applyFP(cipher64, L[16], R[16]);

    binaryToHex(block64, blockHex);
    binaryToHex(cipher64, cipherHex);
}

//////////////////////////////////////////////     End of Step 2     ///////////////////////////////////////////////

FILE* openFile(const char *file, const char *op) {
    FILE *fptr;
    if ((fptr = fopen(file, op)) == NULL) {
        printf("\nError! could not open %s\n", file);
        exit(EXIT_FAILURE);
    }
    return fptr;
}

long getFileSize(FILE *file) {
    if (fseek(file, 0L, SEEK_END)) {
        printf("\nError! fseek failed");
        exit(EXIT_FAILURE);
    }
    long file_size = ftell(file);
    rewind(file);
    return file_size;
}

void read_key(const char *keyFile, char key[8]) {

    FILE *fin = openFile(keyFile, "r");

    if (getFileSize(fin) != 8) {
        printf("\nThe key must be 8 characters long!\n");
        exit(EXIT_FAILURE);
    }

    fread(key, sizeof(char), 8, fin);

    fclose(fin);
}

///////////////////////////////////////////////     Encryption     /////////////////////////////////////////////////

void encrypt_data(const char *inputFile, const char *inputHexFile, const char *cipherHexFile, char subkeys[16][48]) {

    FILE *fin = openFile(inputFile, "r");
    FILE *fout_input = openFile(inputHexFile, "w");
    FILE *fout_cipher = openFile(cipherHexFile, "w");

    char block[9];
    char dataHex[16];
    char cipherHex[16];

    size_t block_size = fread(block, sizeof(char), 8, fin);

    while(block_size == 8) {
        encode_block(block, subkeys, dataHex, cipherHex);
        fwrite(dataHex, sizeof(char), 16, fout_input);
        fwrite(cipherHex, sizeof(char), 16, fout_cipher);
        block_size = fread(block, sizeof(char), 8, fin);
    }

    if (1 <= block_size) {
        for (int i = (int) block_size; i < 8; ++i) {
            block[i] = ' ';
        }
        encode_block(block, subkeys, dataHex, cipherHex);
        fwrite(dataHex, sizeof(char), 16, fout_input);
        fwrite(cipherHex, sizeof(char), 16, fout_cipher);
    }

    fclose(fin);
    fclose(fout_input);
    fclose(fout_cipher);
}

void des_encrypt(const char *keyFile, const char *inputFile, const char *inputHexFile, const char *cipherHexFile) {

    char key[8], subkeys[16][48];

    read_key(keyFile, key);
    create_subkeys(key, subkeys);
    encrypt_data(inputFile, inputHexFile, cipherHexFile, subkeys);
}

///////////////////////////////////////////     End of Encryption     //////////////////////////////////////////////

///////////////////////////////////////////////     Decryption     /////////////////////////////////////////////////

void generatePairsLR_decrypt(char subkeys[16][48], char L[17][32], char R[17][32]) {
    for (int i = 0; i < 16; ++i) {
        copyR(L[i + 1], R[i]);
        f_function(subkeys[15 - i], R[i], R[i + 1]);
        XOR2(L[i], R[i + 1]);
    }
}

void decrypt_block(char blockHex[16], char subkeys[16][48], char decryptedHex[16], char decrypted[8]) {

    char block64[64];
    char block64IP[64];
    char L[17][32];
    char R[17][32];
    char decrypted64[64];

    hexTo64(blockHex, block64);
    applyIP(block64, block64IP);
    splitBlock64IP(block64IP, L[0], R[0]);
    generatePairsLR_decrypt(subkeys, L, R);
    applyFP(decrypted64, L[16], R[16]);

    binaryToHex(decrypted64, decryptedHex);
    hexToText(decryptedHex, decrypted);
}

int trailing_spaces(const char blockHex[16]) {
    int crt = 14;
    int spaces = 0;
    while (blockHex[crt] == '2' && blockHex[crt + 1] == '0') {
        ++spaces;
        crt -= 2;
    }
    return spaces;
}

void decrypt_data(const char *cipherHexFile, const char *decryptedHexFile, const char *decryptedFile, char subkeys[16][48]) {

    FILE *fin = openFile(cipherHexFile, "r");
    FILE *fout_decryptedHex = openFile(decryptedHexFile, "w");
    FILE *fout_decrypted = openFile(decryptedFile, "w");

    int blocks = getFileSize(fin) / 16;
    char blockHex[16];
    char decryptedHex[16];
    char decrypted[8];

    for (int i = 0; i < blocks - 1; ++i) {
        fread(blockHex, sizeof(char), 16, fin);
        decrypt_block(blockHex, subkeys, decryptedHex, decrypted);
        fwrite(decryptedHex, sizeof(char), 16, fout_decryptedHex);
        fwrite(decrypted, sizeof(char), 8, fout_decrypted);
    }

    fread(blockHex, sizeof(char), 16, fin);
    decrypt_block(blockHex, subkeys, decryptedHex, decrypted);
    int spaces = trailing_spaces(decryptedHex);
    fwrite(decryptedHex, sizeof(char), 16 - spaces * 2, fout_decryptedHex);
    fwrite(decrypted, sizeof(char), 8 - spaces, fout_decrypted);

    fclose(fin);
    fclose(fout_decryptedHex);
    fclose(fout_decrypted);
}

void des_decrypt(const char *keyFile, const char *cipherHexFile, const char *decryptedHexFile, const char *decryptedFile) {

    char key[8], subkeys[16][48];

    read_key(keyFile, key);
    create_subkeys(key, subkeys);
    decrypt_data(cipherHexFile, decryptedHexFile, decryptedFile, subkeys);
}

///////////////////////////////////////////     End of Decryption     //////////////////////////////////////////////