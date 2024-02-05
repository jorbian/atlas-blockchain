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

	memcpy(new_block, (block_t *)&_genesis, sizeof(block_t));

	llist_add_node(new_chain->chain, new_block, ADD_NODE_FRONT);

	return (new_chain);
}
