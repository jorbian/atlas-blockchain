#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_load - loads an EC_KEY pair from disk.
 * @folder: path to folder from which to load keys
 *
 * Return: pointer EC_KEY pair (or NULL upon failure)
*/
EC_KEY *ec_load(char const *folder)
{
	(void)folder;

	return (NULL);
}
