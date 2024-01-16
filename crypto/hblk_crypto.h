#ifndef HBLK_CRYPTO_H
#define HBLK_CRYPTO_H

#include <stdlib.h>
#include <stdint.h>

#include <openssl/ssl.h>
#include <openssl/sha.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/ecdsa.h>
#include <openssl/bio.h>

#define EC_PUB_LEN 255
#define MAX_SIG_LEN 72

#define PUB_FILENAME "key.pem"
#define PRI_FILENAME "key_priv.pem"

#define EC_CURVE NID_secp256k1
/**
 * struct sig_s - EC Signature structure
 * @data: Signature buffer.
 * @len: length of the signature stores in data
 */
typedef struct sig_s
{
	uint8_t data[MAX_SIG_LEN];
	uint8_t len;
} sig_t;


uint8_t *sha256(int8_t const *s, size_t len,
	uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);
int ec_save(EC_KEY *key, char const *folder);
EC_KEY *ec_load(char const *folder);
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
	size_t msglen, sig_t *sig);
int ec_verify(EC_KEY const *key, uint8_t const *msg,
	size_t msglen, sig_t const *sig);

#endif
