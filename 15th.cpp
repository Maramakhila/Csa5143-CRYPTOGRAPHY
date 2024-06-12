#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000

// Frequency of letters in English text (in percentage)
const double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.361, 0.150, 1.974, 0.074
};

// Function to calculate the frequency of letters in a given text
void calculateFrequencies(char *text, double *frequencies) {
    int count[ALPHABET_SIZE] = {0};
    int length = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count[tolower(text[i]) - 'a']++;
            length++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (count[i] / (double)length) * 100.0;
    }
}

// Function to compute the chi-squared statistic for a given text
double chiSquared(double *observedFrequencies) {
    double chiSquared = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double expected = englishFrequencies[i];
        double observed = observedFrequencies[i];
        chiSquared += ((observed - expected) * (observed - expected)) / expected;
    }
    return chiSquared;
}

// Function to decrypt the ciphertext with a given key
void decrypt(char *ciphertext, int key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to perform the frequency attack and print the top N possible plaintexts
void frequencyAttack(char *ciphertext, int topN) {
    double bestChiSquaredValues[topN];
    char bestPlaintexts[topN][MAX_TEXT_LENGTH];
    for (int i = 0; i < topN; i++) {
        bestChiSquaredValues[i] = 1e6; // Initialize with a large value
    }

    char decryptedText[MAX_TEXT_LENGTH];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, key, decryptedText);

        double observedFrequencies[ALPHABET_SIZE] = {0};
        calculateFrequencies(decryptedText, observedFrequencies);

        double chiSquaredValue = chiSquared(observedFrequencies);

        // Insert the current plaintext into the top N if it is among the best
        for (int i = 0; i < topN; i++) {
            if (chiSquaredValue < bestChiSquaredValues[i]) {
                for (int j = topN - 1; j > i; j--) {
                    bestChiSquaredValues[j] = bestChiSquaredValues[j - 1];
                    strcpy(bestPlaintexts[j], bestPlaintexts[j - 1]);
                }
                bestChiSquaredValues[i] = chiSquaredValue;
                strcpy(bestPlaintexts[i], decryptedText);
                break;
            }
        }
    }

    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d: %s (chi-squared: %.2f)\n", i + 1, bestPlaintexts[i], bestChiSquaredValues[i]);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    frequencyAttack(ciphertext, topN);

    return 0;
}

