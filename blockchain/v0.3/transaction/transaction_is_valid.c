#include "blockchain.h"
#include "transaction.h"

/**
 * transaction_is_valid - checks whether transaction is valid
 * @transaction: points to the transaction to verify
 * @all_unspent: list of all unspent transaction outputs
 *
 * Return: 1 if the transaction is valid, and 0 otherwise
*/
int transaction_is_valid(transaction_t const *transaction,
	llist_t *all_unspent)
{
	(void)transaction;
	(void)all_unspent;

	return (0);
}
