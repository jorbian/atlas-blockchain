#include "../blockchain.h"
#include "transaction.h"

/**
 * transaction_hash - computes the ID (hash) of a transaction
 * @transaction: transaction to compute the hash of
 * @hash_buf: buffer in which to store the computed hash
 *
 * Return: a pointer to hash_buf
*/
uint8_t *transaction_hash(
	transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	return (NULL);
}
