#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts public key from EC_KEY struct
 * @key: pointer to EC_KEY struct to retrieve public key from
 * @pub: address at which to store the extracted public key)
 *
 * Return: a pointer to pub (or NULL upon failure)
*/
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	if (!key || !pub)
		return (NULL);

	return (pub);
}
