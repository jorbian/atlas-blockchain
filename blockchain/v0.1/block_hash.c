#include "blockchain.h"

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
	(void)block;
	(void)hash_buf;

	return (NULL);
}
