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
	block_t *block;

	block = malloc(sizeof(block_t));
	if (!block)
		return (NULL);
	if (data_len > BLOCKCHAIN_DATA_MAX)
		data_len = BLOCKCHAIN_DATA_MAX;
	block->info.difficulty = 0;
	time((time_t *)&block->info.timestamp);
	block->info.nonce = 0;
	if (prev)
	{
		block->info.index = prev->info.index + 1;
		memset(block->data.buffer, 0, sizeof(block->data.buffer));
		memcpy(block->info.prev_hash, prev->hash, sizeof(prev->hash));
	}
	else /* genesis block is created in blockchain_create, impossible */
	{
		block->info.index = 0;
		memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	}
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(block->data.buffer, data, data_len), block->data.len = data_len;
	block->transactions = llist_create(MT_SUPPORT_FALSE); /* transaction */
	return (block);
}
