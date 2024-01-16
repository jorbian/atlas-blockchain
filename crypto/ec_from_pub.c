#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_from_pub - creates EC_KEY struct given public key
 * @pub: public key to be converted
 *
 * Return: pointer to EC_KEY struct (or NULL upon failure)
*/
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	return (NULL);
}
