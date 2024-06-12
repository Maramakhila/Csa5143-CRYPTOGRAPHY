#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

void encrypt(char *plaintext, int *keyStream, int keyStreamLength, char *ciphertext) {
    int i, shift;
    for (i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            shift = keyStream[i % keyStreamLength];
            if (isupper(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
            } else {
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

void decrypt(char *ciphertext, int *keyStream, int keyStreamLength, char *plaintext) {
    int i, shift;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            shift = keyStream[i % keyStreamLength];
            if (isupper(ciphertext[i])) {
                plaintext[i] = ((ciphertext[i] - 'A' - shift + 26) % 26) + 'A';
            } else {
                plaintext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[MAX_LENGTH] = "send more money";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyStreamLength = sizeof(keyStream) / sizeof(keyStream[0]);
    char ciphertext[MAX_LENGTH];
    char decryptedText[MAX_LENGTH];

    encrypt(plaintext, keyStream, keyStreamLength, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Now we decrypt the ciphertext to obtain "cash not needed"
    char newCiphertext[MAX_LENGTH] = "ciphertext_from_previous_step"; // Replace with the actual ciphertext from previous step
    char newPlaintext[MAX_LENGTH] = "cash not needed";
    int newKeyStream[MAX_LENGTH];
    int i;

    // Calculate the new key stream
    for (i = 0; i < strlen(newCiphertext); i++) {
        if (isalpha(newCiphertext[i]) && isalpha(newPlaintext[i])) {
            if (isupper(newCiphertext[i])) {
                newKeyStream[i] = (newCiphertext[i] - newPlaintext[i] + 26) % 26;
            } else {
                newKeyStream[i] = (newCiphertext[i] - newPlaintext[i] + 26) % 26;
            }
        } else {
            newKeyStream[i] = 0; // Space or non-alphabetic characters do not contribute to the key
        }
    }

    printf("New key stream: ");
    for (i = 0; i < strlen(newCiphertext); i++) {
        printf("%d ", newKeyStream[i]);
    }
    printf("\n");

    // Decrypt using the new key stream
    decrypt(newCiphertext, newKeyStream, strlen(newCiphertext), decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

