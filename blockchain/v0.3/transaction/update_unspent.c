#include "blockchain.h"
#include "transaction.h"

/**
 * update_unspent - updates list of all unspent transaction outputs
 * @transactions: list of validated transactions
 * @block_hash: Hash of validated Block with transaction
 * @all_unspent: current list of unspent transaction outputs
 *
 * Return: a new list of unspent transaction outputs
*/
llist_t *update_unspent(
	llist_t *transactions,
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	llist_t *all_unspent)
{
	(void)transactions;
	(void)block_hash;
	(void)all_unspent;

	return (NULL);
}
