#include <stdio.h>
#include <stdint.h>

// Simple XOR-based block cipher encryption
uint8_t encrypt(uint8_t key, uint8_t block) {
    return key ^ block;
}

// Simple XOR-based block cipher decryption (same as encryption for XOR)
uint8_t decrypt(uint8_t key, uint8_t block) {
    return key ^ block;
}

// Function to calculate CBC MAC for a given message and key
uint8_t cbc_mac(uint8_t key, uint8_t *message, size_t length) {
    uint8_t previous_block = 0; // IV is 0
    uint8_t mac = 0;

    for (size_t i = 0; i < length; i++) {
        uint8_t current_block = message[i] ^ previous_block;
        mac = encrypt(key, current_block);
        previous_block = mac;
    }

    return mac;
}

int main() {
    uint8_t key = 0x5A; // Example key
    uint8_t X = 0xA3;   // Example one-block message

    // Step 1: Calculate MAC of the one-block message X
    uint8_t T = cbc_mac(key, &X, 1);
    printf("MAC for one-block message X: 0x%02X\n", T);

    // Step 2: Calculate CBC MAC for two-block message X || (X ? T)
    uint8_t X_XOR_T = X ^ T;
    uint8_t two_block_message[2] = {X, X_XOR_T};

    uint8_t new_mac = cbc_mac(key, two_block_message, 2);
    printf("MAC for two-block message X || (X ? T): 0x%02X\n", new_mac);

    return 0;
}

