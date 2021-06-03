#ifndef DES_ALGORITHM_IMPLEMENTATION_IN_C_DES_H
#define DES_ALGORITHM_IMPLEMENTATION_IN_C_DES_H

void des_encrypt(const char *keyFile, const char *inputFile, const char *inputHexFile, const char *cipherHexFile);

void des_decrypt(const char *keyFile, const char *cipherHexFile, const char *decryptedHexFile, const char *decryptedFile);

#endif //DES_ALGORITHM_IMPLEMENTATION_IN_C_DES_H
