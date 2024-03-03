#include <openssl/sha.h>

#include "blockchain.h"

static uint8_t *temp_buffer;
static size_t new_len, tx_size;

static void copy_hash(transaction_t **tx_temp, block_t const **block)
{
	size_t i;

	for (i = 0; i < tx_size; i++, new_len += SHA256_DIGEST_LENGTH)
	{
		tx_temp = llist_get_node_at(*block->transactions, i);
		memcpy(temp_buffer + new_len, *tx_temp->id, SHA256_DIGEST_LENGTH);
	}
}

/**
 * block_hash - computes the hash of a Block
 * @block: points to the Block to be hashed
 * @hash_buf: where the resulting hash must be stored
 *
 * Return: pointer to the newly allocated hash_buf (or NULL on failure)
*/
uint8_t *block_hash(block_t const *block,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	transaction_t *tx_temp;

	if (!block)
		return (NULL);

	new_len = (sizeof(block->info) + block->data.len);
	if (block->transactions)
		tx_size = llist_size(block->transactions);

	temp_buffer = calloc(1, (new_len + (SHA256_DIGEST_LENGTH * tx_size)));
	if (!temp_buffer)
		return (NULL);

	memcpy(temp_buffer, block, new_len);

	copy_hash(tx_temp, block);

	sha256(temp_buffer, new_len, hash_buf);

	free(temp_buffer);

	return (hash_buf);
}
