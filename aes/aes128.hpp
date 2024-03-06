#ifndef __AES128_HPP__
#define __AES128_HPP__

#include <cstdint>

void aes_128_enc(uint8_t *, const uint8_t *key);
void aes_128_dec(uint8_t *data, const uint8_t *key);

#endif // __AES128_HPP__
