#include "blockchain.h"
#include "transaction.h"

/**
 * transaction_create - creates a transaction
 * @sender: private key of the transaction sender
 * @receiver: contains the public key of transaction receiver
 * @amount: amount to send
 * @all_unspent: all unspent outputs to date
 *
 * Return: pointer to transaction (or NULL)
*/
transaction_t *transaction_create(
	EC_KEY const *sender,
	EC_KEY const *receiver,
	uint32_t amount, llist_t *all_unspent)
{
	(void)sender;
	(void)receiver;
	(void)amount;
	(void)all_unspent;

	return (NULL);
}
