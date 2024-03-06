#include "base32.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void print_hex(const uint8_t *data, const int &len) {
    for (auto i = 0; i < len; i++) {
        printf("0x%02x ", data[i]);
    }
    printf("\n");
}

void print_str(const uint8_t *data, const int &len) {
    for (auto i = 0; i < len; i++) {
        printf("%c ", data[i]);
    }
    printf("\n");
}

int main() {
    int size, new_size, ret;
    size = 32;
    vector<uint8_t> data(size);
    for (auto i = 0; i < size; i++) {
        data[i] = rand() % 256;
    }
    print_hex(data.data(), size);

    new_size = base32_calculate_size(size, true);
    vector<uint8_t> b32(new_size);
    ret = base32_enc(data.data(), size, b32.data());
    printf("encoded size: %d %d\n", ret, new_size);
    print_str(b32.data(), ret);

    new_size = base32_calculate_size(ret, false);
    vector<uint8_t> b32_inv(new_size);
    ret = base32_dec(b32.data(), ret, b32_inv.data());
    printf("decoded size: %d %d\n", ret, new_size);
    print_hex(b32_inv.data(), ret);

    return 0;
}
