#ifndef DES_ALGORITHM_IMPLEMENTATION_IN_C_CONVERT_H
#define DES_ALGORITHM_IMPLEMENTATION_IN_C_CONVERT_H

void blockTo64(char block[8], char block64[64]);

void binaryToHex(char binary[64], char hex[16]);

void hexTo64(const char blockHex[16], char block64[64]);

void hexToText(char decryptedHex[16], char decrypted[8]);

#endif //DES_ALGORITHM_IMPLEMENTATION_IN_C_CONVERT_H
