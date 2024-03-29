#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"
#include "key_gen.h"

static char path_buff[NUM_KEYS][MAX_PATH_LEN];

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
 * bad_folder_path - checks if the path exists, creates it if not
 * @folder: folder the key files are eventually supposed to go into
 *
 * Return: 1 on success else 0
*/
static int bad_folder_path(char const *folder)
{
	struct stat st = {0};

	if (
		(folder == NULL) ||
		(stat((char *)folder, &st) == -1)
	)
		return (1);

	return (0);
}

/**
 * read_key -read the key of the specified typevalue
 * @key: the key being read from
 * @type_value: index of the key type that needs to be read
 *
 * Return: If there was some type of error reading it.
*/
static uint32_t read_key(EC_KEY *key, uint32_t type_value)
{
	FILE *input_file;

	uint32_t exit_status = 0;

	input_file = fopen(key_file_names[type_value], "r");

	if (input_file == NULL)
		return (1);

	if (type_value == 1)
	{
		if (!PEM_read_EC_PUBKEY(input_file, &key, NULL, NULL))
			exit_status = 1;
	}
	else
	{
		if (!PEM_read_ECPrivateKey(input_file, &key, NULL, NULL))
			exit_status = 1;
	}
	fclose(input_file);

	return (exit_status);
}
/**
 * ec_load - loads an EC_KEY pair from disk.
 * @folder: path to folder from which to load keys
 *
 * Return: pointer EC_KEY pair (or NULL upon failure)
*/
EC_KEY *ec_load(char const *folder)
{
	EC_KEY *key;

	uint32_t i;

	if (bad_folder_path(folder))
		return (NULL);

	generate_file_paths(folder);

	key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (!key)
		return (NULL);

	for (i = 0; i < NUM_KEYS; i++)
		if (read_key(key, i))
		{
			EC_KEY_free(key);
			return (NULL);
		}
	return (key);
}
