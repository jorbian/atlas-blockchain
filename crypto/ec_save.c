#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "hblk_crypto.h"
#include "key_gen.h"

static char path_buff[NUM_KEYS][MAX_PATH_LEN];

/**
 * write_keys - does the actual writting of the keys
 * @key: struct containing the key
 *
*/
static void write_keys(EC_KEY *key)
{
	FILE *fp;

	uint64_t i;

	for (i = 0; i < NUM_KEYS; i++)
	{
		fp = fopen(path_buff[i], "w");
		if (!fp)
			continue;

		switch (i)
		{
			case PRIVATE:
				PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
				break;
			case PUBLIC:
				PEM_write_EC_PUBKEY(fp, key);
				break;
			default:
				continue;
		}
		fclose(fp);
	}
}

/**
 * test_path - checks if the path exists, creates it if not
 * @folder: folder the key files are eventually supposed to go into
 *
 * Return: 1 on success else 0
*/
static int test_path(char const *folder)
{
	struct stat st = {0};

	if (stat((char *)folder, &st) == -1)
		if (mkdir((char *)folder, 0777) == -1)
			return (0);

	return (1);
}

/**
 * generate_file_paths - generate the designated file paths for folder
 * @folder: folder the key files are eventually supposed to go into
 *
*/
static void generate_file_paths(const char *folder)
{
	uint64_t i;

	for (i = 0; i < NUM_KEYS; i++)
	{
		snprintf(
			path_buff[i],
			MAX_PATH_LEN,
			"%s/%s",
			folder, key_file_names[i]
		);
	}
}

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

	generate_file_paths(folder);

	write_keys(key);

	return (0);
}
