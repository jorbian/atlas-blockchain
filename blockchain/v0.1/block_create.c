#include "blockchain.h"


/**
 * block_create - creates a Block structure and initializes it.
 * @prev: pointer to the previous Block in the Blockchain
 * @data: points to a memory area to duplicate in the Block’s data
 * @data_len: the number of bytes to duplicate in data
 *
 * Return: pointer to the allocated Block (or NULL on failure)
*/
block_t *block_create(
	block_t const *prev, int8_t const *data, uint32_t data_len)
{
	uint32_t i;

	block_t *new_block;

	(void)prev;

	if (!data)
		return (NULL);

	new_block = malloc(sizeof(block_t));
	if (!new_block)
		return (NULL);

	return (new_block);
}
