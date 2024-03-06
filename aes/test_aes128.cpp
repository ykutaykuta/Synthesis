#include "aes128.hpp"
#include <iostream>

using namespace std;

void print_data(const uint8_t *data) {
    for (auto i = 0; i < 16; i++) {
        printf("0x%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t data[16];
    uint8_t key[16];

    for (auto i = 0; i < 16; i++) {
        data[i] = rand() % 256;
        key[i] = rand() % 256;
    }

    printf("key: ");
    print_data(key);
    printf("origin_data: ");
    print_data(data);

    aes_128_enc(data, key);
    printf("encrypted_data: ");
    print_data(data);

    aes_128_dec(data, key);
    printf("decrypted_data: ");
    print_data(data);

    return 0;
}
