#include "base64.hpp"
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

    new_size = base64_calculate_size(size, true);
    vector<uint8_t> b64(new_size);
    ret = base64_enc(data.data(), size, b64.data());
    printf("encoded size: %d %d\n", ret, new_size);
    print_str(b64.data(), ret);

    new_size = base64_calculate_size(ret, false);
    vector<uint8_t> b64_inv(new_size);
    ret = base64_dec(b64.data(), ret, b64_inv.data());
    printf("decoded size: %d %d\n", ret, new_size);
    print_hex(b64_inv.data(), ret);

    return 0;
}
