#include <sys/stat.h>

#include "hblk_crypto.h"

/**
 * ec_save - saves public and private key pair to disk
 * @key: key struct containing public and private keys
 * @folder: the path
 * Return: 1 on success, else 0
*/
int ec_save(EC_KEY *key, char const *folder)
{
	(void)key;
	(void)folder;

	return (0);
}
