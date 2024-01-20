#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"
#include "key_gen.h"

/**
 * ec_save - saves existing EC key pair to disk.
 * @key: points to EC_KEY pair to be saved on disk
 * @folder: path to the folder in which to save the keys
 *
 * Return: 1 or 0 upon success or failure
*/
int ec_save(EC_KEY *key, char const *folder)
{
	(void)key;
	uint64_t i;

	char key_file_path[2][MAX_PATH_LEN];

	for (i = 0; i < 2; i++)
	{
		snprintf(
			key_file_path[i],
			MAX_PATH_LEN,
			"%s/%s",
			folder, key_file_names[i]
		);
		printf("%s\n", key_file_path[i]);
	}
	return (0);
}

int main()
{
	char *folder = ".";

	ec_save(NULL, folder);

	return (0);
}