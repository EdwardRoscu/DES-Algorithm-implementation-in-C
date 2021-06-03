#include <stdio.h>
#include <stdlib.h>

#include "includes/display.h"

void print_file_contents(const char *file) {

    FILE *fptr;
    if ((fptr = fopen(file,"r")) == NULL) {
        printf("\nError! could not open %s\n", file);
        exit(EXIT_FAILURE);
    }

    printf("\n%s :\n", file);

    char c = (char) fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = (char) fgetc(fptr);
    }
    putchar('\n');

    fclose(fptr);
}

void display_encrypt(const char *keyFile, const char *inputFile, const char *inputHexFile, const char *cipherHexFile) {
    printf("\n\nEncryption\n\n");
    print_file_contents(keyFile);
    print_file_contents(inputFile);
    print_file_contents(inputHexFile);
    print_file_contents(cipherHexFile);
}

void display_decrypt(const char *keyFile, const char *cipherHexFile, const char *decryptedHexFile, const char *decryptedFile) {
    printf("\n\nDecryption\n\n");
    print_file_contents(keyFile);
    print_file_contents(cipherHexFile);
    print_file_contents(decryptedHexFile);
    print_file_contents(decryptedFile);
}