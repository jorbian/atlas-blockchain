#include <stdio.h>
#include <string.h>

#include "blockchain.h"

/**
 * allocate_memory - allocate memory for blockchain itself and first block
 * @block: DOUBLE POINTER to the first block in the new chain
 * @chain: pointer to the chain structure
 *
 * Return: Pointer to the freshly allocted struct
*/
static blockchain_t *allocate_memory(block_t **block, blockchain_t *chain)
{
	chain = calloc(1, sizeof(blockchain_t));

	if (chain != NULL)
	{
		*block = calloc(1, sizeof(block_t));
		if (*block != NULL)
			return (chain);

		return (NULL);
	}
	return (NULL);

}
/**
 * fill_in_block - fills in the inital info for the first block
 * @first_block: pointer to the first blcok
*/
static void fill_in_block(block_t *first_block)
{
	first_block->info.index = 0;
	first_block->info.difficulty = 0;
	first_block->info.timestamp = 1537578000;
	first_block->info.nonce = 0;
	first_block->data.len = 16;

	snprintf(
		(char *)first_block->hash,
		SHA256_DIGEST_LENGTH,
		"%s", GENESIS_HASH
	);
	memset(first_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(first_block->data.buffer, "Holberton School", 16);
}

/**
 * blockchain_create - creates a Blockchain struct, and initializes it.
 *
 * Return: block chain with at least one block.
*/
blockchain_t *blockchain_create(void)
{
	block_t *new_block = NULL;

	blockchain_t *new_chain = NULL;

	new_chain = allocate_memory(&new_block, new_chain);
	if (!new_chain)
		return (NULL);

	new_chain->chain = llist_create(MT_SUPPORT_FALSE);

	fill_in_block(new_block);

	llist_add_node(new_chain->chain, new_block, ADD_NODE_FRONT);

	return (new_chain);
}
