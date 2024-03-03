#include <string.h>
#include <time.h>

#include "blockchain.h"

/**
 * block_create - Create a new block to go in the blockchain
 * @prev: The address of the previous block in the blockchain
 * @data: The place in memory to duplicate to store in the block's data
 * @data_len: The size in bytes of the data to duplicate and store
 * 
 * Return: The address of the newly created block
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

	new_block->info.difficulty = 0;
	new_block->info.nonce = 0;
	new_block->info.index = 0;

	time((time_t *)&new_block->info.timestamp);

	memset(new_block->hash, 0, SHA256_DIGEST_LENGTH);
	memset(new_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	if (prev)
	{
		new_block->info.index = prev->info.index + 1;
		memset(new_block->data.buffer, 0, sizeof(new_block->data.buffer));
		memcpy(new_block->info.prev_hash, prev->hash, sizeof(prev->hash));
	}
	memcpy(new_block->data.buffer, data, data_len);

	new_block->data.len = data_len;
	new_block->transactions = llist_create(MT_SUPPORT_FALSE);

	return (new_block);
}
