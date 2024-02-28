#include "transaction.h"

/**
 * tx_in_sign - signs transaction input, given the transaction id
 * @in: points to the transaction input structure to sign
 * @tx_id: hash of transaction the input to sign is stored in
 * @sender: private key of receiver of coins contained in transaction output
 * @all_unspent: list of all unspent transaction outputs to date
 *
 * Return: pointer to resulting signature struct (or NULL)
*/
sig_t *tx_in_sign(tx_in_t *in,
	uint8_t const tx_id[SHA256_DIGEST_LENGTH],
	EC_KEY const *sender, llist_t *all_unspent)
{
	(void)in;
	(void)tx_id;
	(void)sender;
	(void)all_unspent;

	return (NULL);
}
