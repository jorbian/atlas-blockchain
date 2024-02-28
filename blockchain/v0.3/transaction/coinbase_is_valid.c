#include "transaction.h"

/**
 * coinbase_is_valid - checks whether a coinbase transaction is valid
 * @coinbase: points to the coinbase transaction to verify
 * @block_index: index of Block the coinbase transaction will belong to
 *
 * Return: 1 if the coinbase transaction is valid, and 0 otherwise
*/
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	(void)coinbase;
	(void)block_index;

	return (0);
}
