#include "base64.hpp"
#include <string>

const std::string base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t base64_calculate_size(const size_t &in_size, const bool &is_enc) {
    size_t ret = 0;
    if (is_enc) {
        ret = in_size / 3 * 4;
        if (in_size % 3 != 0) {
            ret += 4;
        }
    } else {
        ret = in_size / 4 * 3;
        if (in_size % 4 != 0) {
            ret += 3;
        }
    }
    return ret;
}

size_t base64_enc(const uint8_t *in, const size_t &in_size, uint8_t *out) {
    size_t   i, j, k, redudant;
    uint32_t combined;

    redudant = in_size % 3;
    for (i = 0, j = 0; i < in_size - redudant; i += 3, j += 4) {
        combined = (in[i] << 24) | (in[i + 1] << 16) | (in[i + 2] << 8);

        for (k = 0; k < 4; k++) {
            out[j + k] = base64_table[combined >> 26];
            combined <<= 6;
        }
    }

    // the padding
    switch (redudant) {
    case 1:
        combined = (in[i] << 24);
        for (k = 0; k < 2; k++) {
            out[j++] = base64_table[combined >> 26];
            combined <<= 6;
        }
        for (k = 2; k < 4; k++) {
            out[j++] = '=';
        }
        break;
    case 2:
        combined = (in[i] << 24) | (in[i + 1] << 16);
        for (k = 0; k < 3; k++) {
            out[j++] = base64_table[combined >> 26];
            combined <<= 6;
        }
        for (k = 3; k < 4; k++) {
            out[j++] = '=';
        }
        break;

    default:
        break;
    }

    return j;
}

size_t base64_dec(const uint8_t *in, const size_t &in_size, uint8_t *out) {
    size_t   i, j, k, nb_padding;
    uint32_t combined;

    if (in_size % 4 != 0) {
        return 0;
    }

    nb_padding = 0;
    i = in_size - 1;
    while (in[i] == '=') {
        nb_padding++;
        i--;
    }
    if (nb_padding != 0 && nb_padding != 1 && nb_padding != 2) {
        return 0;
    }

    for (i = 0, j = 0; i < in_size - 4; i += 4, j += 3) {
        combined = 0;
        for (k = 0; k < 4; k++) {
            combined <<= 6;
            combined |= base64_table.find(in[i + k]);
        }
        combined <<= (32 - 24);

        for (k = 0; k < 3; k++) {
            out[j + k] = combined >> 24;
            combined <<= 8;
        }
    }

    // the padding
    combined = 0;
    for (k = 0; k < 4 - nb_padding; k++) {
        combined <<= 6;
        combined |= base64_table.find(in[i + k]);
    }
    combined <<= (32 - (4 - nb_padding) * 6);
    switch (nb_padding) {
    case 1:
        for (k = 0; k < 2; k++) {
            out[j++] = combined >> 24;
            combined <<= 8;
        }
        break;
    case 2:
        for (k = 0; k < 1; k++) {
            out[j++] = combined >> 24;
            combined <<= 8;
        }
        break;
    default: // case 0
        for (k = 0; k < 3; k++) {
            out[j++] = combined >> 24;
            combined <<= 8;
        }
        break;
    }
    return j;
}
