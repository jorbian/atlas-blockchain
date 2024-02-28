#include "blockchain.h"

/**
 * deal_with_first - branch if it's the first block in chain
 * @block: the block we're looking at.
 *
 * Return: Is it valid or not? 0 for yes -- 1 for no
*/
static int deal_with_first(block_t const *block)
{
	blockchain_t *dummy_chain;

	int is_valid;

	dummy_chain = blockchain_create();

	if (!dummy_chain)
		return (0);

	is_valid = memcmp(
		llist_get_head(dummy_chain->chain),
		block, sizeof(block_t)
	) != 0;

	blockchain_destroy(dummy_chain);

	return (is_valid);
}

/**
 * deal_with_nth - branch if it's the first block in chain
 * @block: the block we're looking at.
 * @prev_block: points to previous Block in the chain (or NULL)
 *
 * Return: Is it valid or not? 0 for yes -- 1 for no
*/
static int deal_with_nth(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	/* INDEXED WRONG?? */
	if (block->info.index != prev_block->info.index + 1)
		return (1);

	if (BAD_HASH(prev_block, hash_buf) || BAD_HASH(block, hash_buf))
		return (1);

	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);

	/* TOO BIG?? */
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	return (0);
}

/**
 * block_is_valid - verifies that a Block is valid
 * @block: points to the Block to check
 * @prev_block: points to previous Block in the chain (or NULL)
 *
 * Return: A description goes here.
*/
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	if (!block || (!prev_block && block->info.index != 0))
		return (1);

	if (block->info.index == 0)
		return (deal_with_first(block));

	return (deal_with_nth(block, prev_block));
}
