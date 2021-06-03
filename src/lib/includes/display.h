#ifndef DES_ALGORITHM_IMPLEMENTATION_IN_C_DISPLAY_H
#define DES_ALGORITHM_IMPLEMENTATION_IN_C_DISPLAY_H

void display_encrypt(const char *keyFile, const char *inputFile, const char *inputHexFile, const char *cipherHexFile);

void display_decrypt(const char *keyFile, const char *cipherHexFile, const char *decryptedHexFile, const char *decryptedFile);

#endif //DES_ALGORITHM_IMPLEMENTATION_IN_C_DISPLAY_H
