#include "blockchain.h"

/**
 * add_block - adds the next deserialized block to chain
 * @fd: pointer to the file we're reading from
 * @chain: pointer to the chain struct
 *
 * Return: Pointer to the new block (or NULL on failure)
*/
static block_t *add_block(FILE *fd, blockchain_t *chain)
{
	block_t *new_block;

	new_block = calloc(1, sizeof(block_t));

	if (new_block == NULL)
		return (NULL);

	fread(&new_block->info, sizeof(block_info_t), 1, fd);
	fread(&(new_block->data.len), sizeof(uint8_t), 4, fd);
	fread(new_block->data.buffer, sizeof(uint8_t), new_block->data.len, fd);
	fread(new_block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, fd);

	llist_add_node(chain->chain, new_block, ADD_NODE_REAR);

	return (new_block);
}

/**
 * write_blocks - Deserialize blocks from a file and add them to a blockchain
 * @fd: File descriptor of the file containing serialized blocks
 * @chain: Pointer to the blockchain where blocks will be added
 *
 * Return: Pointer to the chain (or NULL on failure)
 */
static blockchain_t *write_blocks(FILE *fd, blockchain_t *chain)
{
	uint8_t end;
	uint32_t i, size;

	char buf[4] = {0};

	fread(buf, sizeof(uint8_t), 4, fd);
	fread(buf, sizeof(uint8_t), 3, fd);
	fread(&end, sizeof(uint8_t), 1, fd);
	fread(&size, sizeof(uint32_t), 1, fd);

	for (i = 0; i < size; i++)
		if (!add_block(fd, chain))
			return (NULL);

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
 * Return: pointer to deserialized Blockchain (or NULL on failure)
*/
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fd;

	blockchain_t *blockchain;

	if (!path || (access_file(&fd, path) != 0))
		return (NULL);

	blockchain = create_new_blockchain();
	if (blockchain != NULL)
		blockchain = write_blocks(fd, blockchain);

	fclose(fd);

	return (blockchain);
}
