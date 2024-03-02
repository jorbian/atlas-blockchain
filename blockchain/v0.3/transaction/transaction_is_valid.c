#include "transaction.h"

#define IN 0
#define OUT 1

static uint32_t sum[2];
static tx_in_t *tx_in;
static unspent_tx_out_t *uns_out;

/**
 * verify_key - verfies the given key with a particular node
 * @transaction: pointer to the transaction_
 *
 * Return: 1 for valid, 0 for invalid
*/
static uint32_t verify_key(transaction_t const *transaction)
{
	EC_KEY *uns_key;

	int j;

	uns_key = ec_from_pub(uns_out->out.pub); /* sig verify */

	j = ec_verify(uns_key, transaction->id, SHA256_DIGEST_LENGTH, &tx_in->sig);

	EC_KEY_free(uns_key);

	if (j == 0)
		return (0);

	return (1);
}

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

static uint32_t walk_inputs(
	transaction_t const *transaction,
	llist_t *all_unspent)
{
	int i, j, size_usp;

	size_usp = llist_size(all_unspent);

	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		tx_in = llist_get_node_at(transaction->inputs, i);
		for (j = 0; j < size_usp; j++)
		{
			uns_out = llist_get_node_at(all_unspent, j);
			if (memcmp(uns_out->out.hash, tx_in->tx_out_hash, SHA256_DIGEST_LENGTH) == 0
				&& memcmp(uns_out->tx_id, tx_in->tx_id, SHA256_DIGEST_LENGTH) == 0 &&
				memcmp(uns_out->block_hash, tx_in->block_hash, SHA256_DIGEST_LENGTH)
				== 0)
				break;
		}
		if (j == size_usp)
			return (0);

		if (!verify_key(transaction))
			return (0);

		sum[IN] += uns_out->out.amount;
	}
	return (1);
}

/**
 * transaction_is_valid - checks whether transaction is valid
 * @transaction: points to the transaction to verify
 * @all_unspent: list of all unspent transaction outputs
 *
 * Return: 1 if the transaction is valid, and 0 otherwise
*/
int transaction_is_valid(
	transaction_t const *transaction,
	llist_t *all_unspent)
{
	int i;

	if (!transaction || !all_unspent)
		return (0);

	if (!hash_matches(transaction))
		return (0);

	walk_inputs(transaction, all_unspent);

	for (i = 0; i < llist_size(transaction->outputs); i++)
		sum[OUT] += ((tx_out_t *)llist_get_node_at(transaction->outputs, i))->amount;

	if (sum[IN] != sum[OUT])
		return (0);

	return (1);
}
