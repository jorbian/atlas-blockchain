#include "transaction.h"

/**
 * tx_in_create - allocates and initializes a tx_in_t
 * @unspent: transaction output to be converted to transaction input
 *
 * Return: Pointer to new tx_in_t
*/
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	(void)unspent;

	return (NULL);
}
