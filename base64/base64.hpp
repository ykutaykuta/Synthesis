#ifndef __BASE64_HPP__
#define __BASE64_HPP__

#include <cstdint>

size_t base64_calculate_size(const size_t &in_size, const bool &is_enc);
size_t base64_enc(const uint8_t *in, const size_t &in_size, uint8_t *out);
size_t base64_dec(const uint8_t *in, const size_t &in_size, uint8_t *out);

#endif // __BASE64_HPP__
