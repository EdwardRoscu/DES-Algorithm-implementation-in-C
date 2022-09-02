# DES-algorithm-implementation
This is my own implementation of the Data Encryption Standard using C

This project provides functions for both the encryption and the decryption part

## General Description

For the implementation of the DES algorithm I went through the steps provided here: http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

The functions related to the DES algorithm are located in DES.c in the lib folder

The encryption function takes 2 .txt files as input for the key and the plain text and another 2 .txt files for the output of the resulted cipher in hexadecimal and the input in hexadecimal for the purpose of seeing the difference

The decryption function takes 2 .txt files as input for the key and the cipher and another 2 .txt files for the output of the deciphered plain text and the deciphered text in hexadecimal

I provided their corresponding display functions in display.c for printing the contents of the mentioned .txt files to the standard output

## Padding

This implementation uses spaces to pad the contents of input.txt before its encryption

Since we pad the input before encryption, the decryption function removes trailing spaces after decryption

## How to run

To run this project you need to set the Working directory the folder containing the src folder
