#include "transaction.h"

#define PARAMS_DONT_MATCH(cb) (llist_size(cb->inputs) != 1 || \
	llist_size(cb->outputs) != 1)
#define FAILS_PRELIM_CHECKS(cb) (!hash_matches(cb) || PARAMS_DONT_MATCH(cb))

static tx_in_t *tx_in, zz_in;
static tx_out_t *tx_out;

/**
 * hash_matches - verifies the transaction has the expected hash
 * @transaction: pointer to the transaction struct
 *
 * Return: 1 for yes, 0 for no.
*/
static uint32_t hash_matches(transaction_t const *transaction)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	transaction_hash(transaction, hash_buf);

	if (memcmp(hash_buf, transaction->id, SHA256_DIGEST_LENGTH) != 0)
		return (0);

	return (1);
}

static void init_zzd_in(void)
{
	memset(zz_in.tx_id, 0, SHA256_DIGEST_LENGTH);
	memset(zz_in.block_hash, 0, SHA256_DIGEST_LENGTH);
	memset(&(zz_in.sig), 0, sizeof(sig_t));
}

/**
 * coinbase_is_valid - checks whether a coinbase transaction is valid
 * @coinbase: points to the coinbase transaction to verify
 * @block_index: index of Block the coinbase transaction will belong to
 *
 * Return: 1 if the coinbase transaction is valid, and 0 otherwise
*/
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	if (!coinbase)
		return (0);

	if (FAILS_PRELIM_CHECKS(coinbase))
		return (0);

	tx_in = llist_get_node_at(coinbase->inputs, 0);
	tx_out = llist_get_node_at(coinbase->outputs, 0);
	if (memcmp(&block_index, tx_in->tx_out_hash, 4) != 0)
		return (0); /* tx_out_hash first 4 bytes check */

	if (memcmp(zz_in.block_hash, tx_in->block_hash, SHA256_DIGEST_LENGTH) != 0
	    || memcmp(zz_in.tx_id, tx_in->tx_id, SHA256_DIGEST_LENGTH) != 0 ||
	    memcmp(&zz_in.sig, &tx_in->sig, sizeof(tx_in->sig)) != 0)
		return (0);

	if (tx_out->amount != COINBASE_AMOUNT) /* output amount check */
		return (0);
	return (1);
}
