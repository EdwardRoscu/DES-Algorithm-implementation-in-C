#include "lib/includes/DES.h"
#include "lib/includes/display.h"

const char *keyFile = "src/txt/inputs/key.txt";
const char *cipherHexFile = "src/txt/cipherHex.txt";

const char *inputFile = "src/txt/inputs/input.txt";
const char *inputHexFile = "src/txt/outputs/inputHex.txt";
const char *decryptedHexFile = "src/txt/outputs/decryptedHex.txt";
const char *decryptedFile = "src/txt/outputs/decrypted.txt";

int main() {

    des_encrypt(keyFile, inputFile, inputHexFile, cipherHexFile);
    display_encrypt(keyFile, inputFile, inputHexFile, cipherHexFile);

    des_decrypt(keyFile, cipherHexFile, decryptedHexFile, decryptedFile);
    display_decrypt(keyFile, cipherHexFile, decryptedHexFile, decryptedFile);

    return 0;
}