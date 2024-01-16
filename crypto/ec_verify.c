#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_verify - verifies signature of bytes using EC_KEY public key
 * @key: EC_KEY struct containing public key used to verify signature
 * @msg: points to the msglen characters to verify the signature of
 * @msglen: whatever the length of msg len is
 * @sig: points to signature to be checked
 *
 * Return: return 1 if the signature is valid, and 0 otherwise
*/
int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
sig_t const *sig
)
{
	(void)key;
	(void)msg;
	(void)msglen;
	(void)sig;

	return (0);
}
