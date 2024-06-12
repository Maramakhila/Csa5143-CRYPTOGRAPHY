#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to print data in hexadecimal format
void printHex(const char *title, const unsigned char *data, int len) {
    printf("%s: ", title);
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

// Function to handle errors
void handleErrors(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    // Plaintext
    unsigned char plaintext[] = "This is a test of 3DES in CBC mode.";

    // 3DES key and IV (initialization vector)
    DES_cblock key1, key2, key3, iv;
    DES_key_schedule ks1, ks2, ks3;

    // Setting up the keys (must be 8 bytes each)
    DES_string_to_key("12345678", &key1);
    DES_string_to_key("abcdefgh", &key2);
    DES_string_to_key("87654321", &key3);

    // Setting up the IV (must be 8 bytes)
    memcpy(iv, "87654321", 8);

    // Setting up the key schedules
    DES_set_key_checked(&key1, &ks1);
    DES_set_key_checked(&key2, &ks2);
    DES_set_key_checked(&key3, &ks3);

    // Padding plaintext to be a multiple of DES block size (8 bytes)
    int len = strlen((char *)plaintext);
    int paddedLen = ((len + 7) / 8) * 8;
    unsigned char *paddedPlaintext = calloc(paddedLen, sizeof(unsigned char));
    if (!paddedPlaintext) handleErrors("Failed to allocate memory for padded plaintext");
    memcpy(paddedPlaintext, plaintext, len);

    // Output buffers for ciphertext and decrypted text
    unsigned char *ciphertext = calloc(paddedLen, sizeof(unsigned char));
    unsigned char *decryptedText = calloc(paddedLen, sizeof(unsigned char));
    if (!ciphertext || !decryptedText) handleErrors("Failed to allocate memory for output buffers");

    // Encrypting in CBC mode
    DES_ede3_cbc_encrypt(paddedPlaintext, ciphertext, paddedLen, &ks1, &ks2, &ks3, &iv, DES_ENCRYPT);

    // Print the ciphertext
    printHex("Ciphertext", ciphertext, paddedLen);

    // Reset IV for decryption (must be the same as for encryption)
    memcpy(iv, "87654321", 8);

    // Decrypting in CBC mode
    DES_ede3_cbc_encrypt(ciphertext, decryptedText, paddedLen, &ks1, &ks2, &ks3, &iv, DES_DECRYPT);

    // Print the decrypted text
    printf("Decrypted text: %s\n", decryptedText);

    // Clean up
    free(paddedPlaintext);
    free(ciphertext);
    free(decryptedText);

    return 0;
}

