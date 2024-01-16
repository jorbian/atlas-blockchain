#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_create - creates a new EC key pair.
 *
 * Return: pointer to EC_KEY (or NULL upon failure)
*/
EC_KEY *ec_create(void)
{
	EC_KEY *new_key;

	new_key = EC_KEY_new();
	if (new_key == NULL)
		return (NULL);

	return (new_key);
}
