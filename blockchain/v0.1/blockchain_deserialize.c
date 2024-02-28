#include "blockchain.h"

/**
 * write_blocks - Deserialize blocks from a file and add them to a blockchain
 * @size: Number of blocks to deserialize
 * @fd: File descriptor of the file containing serialized blocks
 * @chain: Pointer to the blockchain where blocks will be added
 *
 * Return: Pointer to the updated blockchain
 */
static blockchain_t *write_blocks(uint32_t size, FILE *fd, blockchain_t *chain)
{
	block_t *block;
	uint32_t i;

	for (i = 0; i < size; i++)
	{
		block = calloc(1, sizeof(block_t));
		fread(&block->info, sizeof(block_info_t), 1, fd);
		fread(&(block->data.len), sizeof(uint8_t), 4, fd);
		fread(block->data.buffer, sizeof(uint8_t), block->data.len, fd);
		fread(block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, fd);
		llist_add_node(chain->chain, block, ADD_NODE_REAR);
	}

	return (chain);

}

/**
 * access_file - see if we can access the file
 * @fd: DOUBLE file pointer
 * @path: path of the file we're attempting to acess
 *
 * Return: 0 on sucess, -1 on failure
*/
static uint8_t access_file(FILE **fd, char const *path)
{
	*fd = fopen(path, "r");

	if (!*fd)
		return (-1);

	return (0);
}

/**
 * create_new_blockchain - allocates memory for an inits new blockchain
 *
 * Return: pointer to the new struct
*/
static blockchain_t *create_new_blockchain()
{
	blockchain_t *new_blockchain;

	new_blockchain = calloc(1, sizeof(blockchain_t));

	if (!new_blockchain)
		return (NULL);

	new_blockchain->chain = llist_create(MT_SUPPORT_FALSE);

	return (new_blockchain);
}
/**
 * blockchain_deserialize - deserializes a Blockchain from a file
 * @path: contains the path to a file to load the Blockchain from
 *
 * Return: pointer to deserialized Blockchain on success (or NULL upon failure)
*/
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fd;
	char buf[8] = {0};
	uint8_t end;
	uint32_t size;

	blockchain_t *blockchain;

	if (!path || (access_file(&fd, path) != 0))
		return (NULL);

	fread(buf, sizeof(uint8_t), 7, fd);
	fread(&end, sizeof(uint8_t), 1, fd);
	fread(&size, sizeof(uint32_t), 1, fd);
	
	blockchain = write_blocks(size, fd, blockchain);
	fclose(fd);

	return (blockchain);
}

