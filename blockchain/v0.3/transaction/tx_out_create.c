#include "../blockchain.h"
#include "transaction.h"

/**
 * tx_out_create - allocates and initializes transaction output struct
 * @amount: amount of the transaction
 * @pub: public key of the transaction receiver
 *
 * Return: pointer to transaction output on success, or NULL on failure
*/
tx_out_t *tx_out_create(uint32_t amount,
	uint8_t const pub[EC_PUB_LEN])
{
	return (NULL);
}
