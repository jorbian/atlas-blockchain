#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include "hblk_crypto.h"

/**
 * sha256 - computes hash of a sequence of bytes
 * @s: sequence of bytes to be hashed
 * @len: number of bytes to hash in s
 * @digest: place to put the hash
 *
 * Return: a pointer to digest
*/
uint8_t *sha256(const int8_t *s, size_t len,
	uint8_t digest[SHA256_DIGEST_LENGTH]
)
{
	SHA256_CTX sha256Context;

	if (
		(!SHA256_Init(&sha256Context)) ||
		(!SHA256_Update(&sha256Context, s, len)) ||
		(!SHA256_Final(digest, &sha256Context))
	)
		return (NULL);

	return (digest);
}

