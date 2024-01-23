#include <sys/stat.h>

#include "hblk_crypto.h"
/**
 * write_private - writes private key to a file
 * @key: struct containing the key
 * @folder: the path to save the file
 * Return: 1 on success, else 0
*/
static int write_private(EC_KEY *key, char const *folder)
{
	FILE *fp;
	int written = 0;
	size_t path_len = strlen(folder) + strlen("/key.pem") + 3;
	char *priv_path = malloc(sizeof(char) * (path_len));
	char *file_name = "key.pem";

	snprintf(priv_path, path_len, "%s/%s", folder, file_name);
	fp = fopen(priv_path, "w");
	if (!fp)
		printf("failed to open file\n");
	written = PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
	fclose(fp);
	free(priv_path);
	return (written > 0 ? 1 : 0);
}
/**
 * write_public - writes public key to a file
 * @key: struct containing the key
 * @folder: the path to save the file
 * Return: 1 on success, else 0
*/
static int write_public(EC_KEY *key, char const *folder)
{
	FILE *fp;
	size_t path_len = strlen(folder) + strlen("/key_pub.pem") + 3;
	char *pub_path = malloc(sizeof(char) * (path_len));
	char *file_name = "key_pub.pem";
	int written = 0;

	snprintf(pub_path, path_len, "%s/%s", folder, file_name);
	fp = fopen(pub_path, "w");
	if (!fp)
		printf("failed to open file\n");
	written = PEM_write_EC_PUBKEY(fp, key);
	fclose(fp);
	free(pub_path);
	return (written > 0 ? 1 : 0);
}
/**
 * handle_path - checks if the path exists, creates it if not
 * @folder: the path
 * Return: 1 on success else 0
*/
static int handle_path(char const *folder)
{
	struct stat st = {0};

	if (stat((char *)folder, &st) == -1)
	{
		if (mkdir((char *)folder, 0777) == -1)
		{
			perror("mkdir");
			return (0);
		}
	}
	return (1);
}
/**
 * ec_save - saves public and private key pair to disk
 * @key: key struct containing public and private keys
 * @folder: the path
 * Return: 1 on success, else 0
*/
int ec_save(EC_KEY *key, char const *folder)
{
	if (!key)
		return (0);

	handle_path(folder);

	if (!write_private(key, folder) || !write_public(key, folder))
		return (0);

	return (1);
}
