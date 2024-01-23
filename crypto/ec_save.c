#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"


/**
 * ec_save - saves existing EC key pair to disk.
 * @key: points to EC_KEY pair to be saved on disk
 * @folder: path to the folder in which to save the keys
 *
 * Return: 1 or 0 upon success or failure
*/
int ec_save(EC_KEY *key, char const *folder)
{
	if (!key || !folder || !test_path(folder))
		return (1);

	return (1);
}
