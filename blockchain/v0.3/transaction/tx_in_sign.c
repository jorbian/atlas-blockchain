#include "../blockchain.h"
#include "transaction.h"

/**
 * tx_in_sign - signs transaction input, given the transaction id
 * @in: points to the transaction input structure to sign
 * @tx_id: contains hash of transaction the input to sign is stored in
 * @sender:
 * @all_unspent:
 *
 * Return: pointer to resulting signature struct (or NULL)
*/
sig_t *tx_in_sign(tx_in_t *in,
	uint8_t const tx_id[SHA256_DIGEST_LENGTH],
	EC_KEY const *sender, llist_t *all_unspent)
{
	return (NULL);
}
