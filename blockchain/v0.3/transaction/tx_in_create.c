#include "transaction.h"

/**
 * tx_in_create - allocates and initializes a tx_in_t
 * @unspent: transaction output to be converted to transaction input
 *
 * Return: Pointer to new tx_in_t
*/
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *new_input;

	new_input = calloc(1, sizeof(tx_in_t));
	if (!new_input)
		return (NULL);

	memcpy(new_input->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(new_input->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(new_input->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);

	return (new_input);
}
