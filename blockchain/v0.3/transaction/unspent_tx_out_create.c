#include "transaction.h"

/**
 * unspent_tx_out_create - allocates and initializes unspent unspent_tx_out_t
 * @block_hash: contains hash of Block for referenced transaction output
 * @tx_id: hash of transaction where the referenced transaction output
 * @out: points to the referenced transaction output
 *
 * Return: pointer to created unspent_tx_out_t upon success (or NULL)
*/
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
	unspent_tx_out_t *new_unspent;

	new_unspent = calloc(1, sizeof(unspent_tx_out_t));
	if (!new_unspent)
		return (NULL);

	memcpy(
		new_unspent->block_hash,
		block_hash,
		SHA256_DIGEST_LENGTH
	);
	memcpy(
		new_unspent->tx_id,
		tx_id,
		SHA256_DIGEST_LENGTH
	);
	memcpy(&new_unspent->out, out, sizeof(tx_out_t));

	return (new_unspent);
}
