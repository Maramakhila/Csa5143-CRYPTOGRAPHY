#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b; 
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to check if 'a' is valid
int isValidA(int a) {
    return gcd(a, 26) == 1;
}

// Function to encrypt using affine cipher
void encrypt(char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((a * (plaintext[i] - base) + b) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    do {
        printf("Enter a value for a (must be coprime with 26): ");
        scanf("%d", &a);
        if (!isValidA(a)) {
            printf("Invalid value for a. It must be coprime with 26.\n");
        }
    } while (!isValidA(a));

    printf("Enter a value for b: ");
    scanf("%d", &b);

    encrypt(plaintext, a, b, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

