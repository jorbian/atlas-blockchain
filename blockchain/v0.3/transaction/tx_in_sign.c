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
	EC_KEY const *sender,
	llist_t *all_unspent)
{
	uint8_t pub_buf[EC_PUB_LEN];
	unspent_tx_out_t *node;

	int i;

	ec_to_pub(sender, pub_buf);

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		node = llist_get_node_at(all_unspent, i);
		if (memcmp(node->out.pub, pub_buf, EC_PUB_LEN) == 0)
		{
			ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig);
			return (&in->sig);
		}
	}
	return (NULL);
}
