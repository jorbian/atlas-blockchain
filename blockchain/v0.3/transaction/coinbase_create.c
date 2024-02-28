#include "../blockchain.h"
#include "transaction.h"

/**
 * coinbase_create - creates a coinbase transaction
 * @receiver: public key of miner, who will receive coinbase coins
 * @block_index: index of Block transaction will belong to
 *
 * Return: pointer to transaction upon success (or NULL)
*/
transaction_t *coinbase_create(
	EC_KEY const *receiver,
	uint32_t block_index)
{
	return (NULL);
}
