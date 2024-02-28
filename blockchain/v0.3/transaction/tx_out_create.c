#include "transaction.h"

/**
 * tx_out_create - allocates and initializes transaction output struct
 * @amount: amount of the transaction
 * @pub: public key of the transaction receiver
 *
 * Return: pointer to transaction output on success, or NULL on failure
*/
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *tx_change = NULL;

	tx_change = calloc(1, sizeof(tx_out_t));
	if (!tx_change)
		return (NULL);

	tx_change->amount = amount;

	memcpy(tx_change->pub, pub, EC_PUB_LEN);

	SHA256(
		(const unsigned char *)tx_change,
		sizeof(tx_change->amount) + EC_PUB_LEN,
		tx_change->hash
	);
	return (tx_change);
}
