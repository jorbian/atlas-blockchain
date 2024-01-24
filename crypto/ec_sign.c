#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_sign - signs bytes using EC_KEY private key
 * @key: EC_KEY struct containing public key used to verify signature
 * @msg: points to the msglen characters to verify the signature of
 * @msglen: whatever the length of msg len is
 * @sig: points to signature to be checked
 *
 * Return: return 1 if the signature is valid, and 0 otherwise
*/
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen,
sig_t *sig)
{
	uint32_t sig_len = 0;

	if (!key || !msg || !sig)
		return (NULL);

	if (!ECDSA_sign(0, msg, msglen, sig->sig, &sig_len, (EC_KEY *)key))
	{
		sig->len = 0;
		return (NULL);
	}
	sig->len = (uint8_t)sig_len;

	return (sig->sig);
}
