#include <stdio.h>
#include <string.h>

// Function to decode the ciphertext using a predefined mapping
void decodeCiphertext(const char *ciphertext, const char *mapping) {
    int length = strlen(ciphertext);
    char plaintext[length + 1];
    
    // Decode the ciphertext
    for (int i = 0; i < length; i++) {
        char ch = ciphertext[i];
        if (ch >= ' ' && ch <= '~') {
            plaintext[i] = mapping[ch - ' '];
        } else {
            plaintext[i] = ch;
        }
    }
    plaintext[length] = '\0';
    
    printf("Decoded plaintext:\n%s\n", plaintext);
}

int main() {
    const char ciphertext = "53‡‡†305))6;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡8†83(88)5†;46(;88*96*?;8)‡(;485);5†2:‡(;4956*2(5—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    
    
    const char mapping = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !\"#$%&'()+,-./:;<=>?@[\\]^_`{|}~";

    decodeCiphertext(ciphertext, mapping);

    return 0;
}
