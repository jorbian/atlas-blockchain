#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

static const EC_POINT *point;
static const EC_GROUP *group;

/**
 * read_key - read the actual contents of the key
 * @key: pointer to EC_KEY struct to retrieve public key from
 *
 * Return: 1 upon failure, 0 upon sucess
*/
static uint32_t read_key(EC_KEY const *key)
{
	point = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);

	if (!point || !group)
		return (1);

	return (0);
}

/**
 * extract_public_key - wrapper for the EC_POINT_point2oct function
 * @pub: address at which to store the extracted public key)
 *
 * Return: 1 upon failure, 0 upon sucess
*/
static uint32_t extract_public_key(uint8_t pub[EC_PUB_LEN])
{
	uint64_t length;

	length = EC_POINT_point2oct(
		group, point,
		POINT_CONVERSION_UNCOMPRESSED,
		pub, EC_PUB_LEN, NULL
	);

	if (length != EC_PUB_LEN)
		return (1);

	return (0);
}

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

	if (read_key(key))
		return (NULL);

	if (extract_public_key(pub))
		return (NULL);

	return (pub);
}
