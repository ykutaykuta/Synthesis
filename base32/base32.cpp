#include "base32.hpp"

#include <string>

const std::string base32_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ125689";

size_t base32_calculate_size(const size_t &in_size, const bool &is_enc) {
    size_t ret = 0;
    if (is_enc) {
        ret = in_size / 5 * 8;
        if (in_size % 5 != 0) {
            ret += 8;
        }
    } else {
        ret = in_size / 8 * 5;
        if (in_size % 8 != 0) {
            ret += 5;
        }
    }
    return ret;
}

size_t base32_enc(const uint8_t *in, const size_t &in_size, uint8_t *out) {
    size_t   i, j, k, redudant;
    uint64_t combined;

    redudant = in_size % 5;
    for (i = 0, j = 0; i < in_size - redudant; i += 5, j += 8) {
        combined = ((uint64_t)in[i] << 56) | ((uint64_t)in[i + 1] << 48) | ((uint64_t)in[i + 2] << 40) | ((uint64_t)in[i + 3] << 32) | ((uint64_t)in[i + 4] << 24);
        for (k = 0; k < 8; k++) {
            out[j + k] = base32_table[combined >> 59];
            combined <<= 5;
        }
    }

    // the padding
    switch (redudant) {
    case 1:
        combined = ((uint64_t)in[i] << 56);
        for (k = 0; k < 2; k++) {
            out[j + k] = base32_table[combined >> 59];
            combined <<= 5;
        }
        for (k = 2; k < 8; k++) {
            out[j + k] = '=';
        }
        j += 8;
        break;
    case 2:
        combined = ((uint64_t)in[i] << 56) | ((uint64_t)in[i + 1] << 48);
        for (k = 0; k < 4; k++) {
            out[j + k] = base32_table[combined >> 59];
            combined <<= 5;
        }
        for (k = 4; k < 8; k++) {
            out[j + k] = '=';
        }
        j += 8;
        break;
    case 3:
        combined = ((uint64_t)in[i] << 56) | ((uint64_t)in[i + 1] << 48) | ((uint64_t)in[i + 2] << 40);
        for (k = 0; k < 5; k++) {
            out[j + k] = base32_table[combined >> 59];
            combined <<= 5;
        }
        for (k = 5; k < 8; k++) {
            out[j + k] = '=';
        }
        j += 8;
        break;
    case 4:
        combined = ((uint64_t)in[i] << 56) | ((uint64_t)in[i + 1] << 48) | ((uint64_t)in[i + 2] << 40) | ((uint64_t)in[i + 3] << 32);
        for (k = 0; k < 7; k++) {
            out[j + k] = base32_table[combined >> 59];
            combined <<= 5;
        }
        for (k = 7; k < 8; k++) {
            out[j + k] = '=';
        }
        j += 8;
        break;

    default:
        break;
    }

    return j;
}

size_t base32_dec(const uint8_t *in, const size_t &in_size, uint8_t *out) {
    size_t   i, j, k, nb_padding;
    uint64_t combined;

    if (in_size % 8 != 0) {
        return 0;
    }

    nb_padding = 0;
    i = in_size - 1;
    while (in[i] == '=') {
        nb_padding++;
        i--;
    }
    if (nb_padding != 0 && nb_padding != 1 && nb_padding != 3 && nb_padding != 4 && nb_padding != 6) {
        return 0;
    }

    for (i = 0, j = 0; i < in_size - 8; i += 8, j += 5) {
        combined = 0;
        for (k = 0; k < 8; k++) {
            combined <<= 5;
            combined |= base32_table.find(in[i + k]);
        }
        combined <<= (64 - 40);

        for (k = 0; k < 5; k++) {
            out[j + k] = combined >> 56;
            combined <<= 8;
        }
    }

    // the padding
    combined = 0;
    for (k = 0; k < 8 - nb_padding; k++) {
        combined <<= 5;
        combined |= base32_table.find(in[i + k]);
    }
    combined <<= (64 - (8 - nb_padding) * 5);
    switch (nb_padding) {
    case 1:
        for (k = 0; k < 4; k++) {
            out[j++] = combined >> 56;
            combined <<= 8;
        }
        break;
    case 3:
        for (k = 0; k < 3; k++) {
            out[j++] = combined >> 56;
            combined <<= 8;
        }
        break;
    case 4:
        for (k = 0; k < 2; k++) {
            out[j++] = combined >> 56;
            combined <<= 8;
        }
        break;
    case 6:
        for (k = 0; k < 1; k++) {
            out[j++] = combined >> 56;
            combined <<= 8;
        }
        break;
    default: // case 0
        for (k = 0; k < 5; k++) {
            out[j++] = combined >> 56;
            combined <<= 8;
        }
        break;
    }
    return j;
}
