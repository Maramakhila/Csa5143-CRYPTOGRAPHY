#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26

// Function to multiply two matrices
void matrixMultiply(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += a[i][j] * b[j];
        }
        result[i] %= MOD;
    }
}

// Function to find the modular inverse of a number modulo m using the extended Euclidean algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

// Function to find the inverse of a 2x2 matrix modulo 26
void findMatrixInverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int determinant = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    determinant = (determinant % MOD + MOD) % MOD;
    int invDet = modInverse(determinant, MOD);

    inverse[0][0] = (key[1][1] * invDet) % MOD;
    inverse[0][1] = (-key[0][1] * invDet + MOD) % MOD;
    inverse[1][0] = (-key[1][0] * invDet + MOD) % MOD;
    inverse[1][1] = (key[0][0] * invDet) % MOD;
}

// Function to encrypt plaintext using the Hill cipher
void encrypt(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int length = strlen(plaintext);
    int block[MATRIX_SIZE], result[MATRIX_SIZE];

    for (int i = 0; i < length; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < length) {
                block[j] = toupper(plaintext[i + j]) - 'A';
            } else {
                block[j] = 'X' - 'A'; // Padding with 'X'
            }
        }

        matrixMultiply(key, block, result);

        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = result[j] + 'A';
        }
    }
    ciphertext[length] = '\0';
}

// Function to decrypt ciphertext using the Hill cipher
void decrypt(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inverseKey[MATRIX_SIZE][MATRIX_SIZE];
    findMatrixInverse(key, inverseKey);

    int length = strlen(ciphertext);
    int block[MATRIX_SIZE], result[MATRIX_SIZE];

    for (int i = 0; i < length; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = toupper(ciphertext[i + j]) - 'A';
        }

        matrixMultiply(inverseKey, block, result);

        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i + j] = result[j] + 'A';
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[100] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    char ciphertext[100];
    int key[MATRIX_SIZE][MATRIX_SIZE] = { {9, 4}, {5, 7} };

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    char decryptedtext[100];
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}

