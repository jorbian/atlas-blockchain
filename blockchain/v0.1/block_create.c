#include <string.h>
#include <time.h>

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
	block_t *new_block;

	new_block = calloc(1, sizeof(block_t));
	if (!new_block)
		return (NULL);

	if (data_len > BLOCKCHAIN_DATA_MAX)
		data_len = BLOCKCHAIN_DATA_MAX;
	time((time_t *)&new_block->info.timestamp);

	memcpy(new_block->data.buffer, data, data_len);
	new_block->data.len = data_len;

	if (prev)
	{
		new_block->info.index = prev->info.index + 1;
		memcpy(new_block->info.prev_hash, prev->hash, sizeof(prev->hash));
	}

	return (new_block);
}
