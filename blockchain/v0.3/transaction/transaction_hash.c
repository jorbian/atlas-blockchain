#include "transaction.h"

static uint32_t dims[3];
static uint32_t buffer_offset = 0;

static void calculate_dimensions(transaction_t const *txn)
{
	dims[0] = llist_size(txn->inputs);
	dims[1] = llist_size(txn->outputs);
	dims[2] = (
		(dims[0] * TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH) +
		(dims[1] * SHA256_DIGEST_LENGTH)
	);
}

/**
 * transaction_hash - computes the ID (hash) of a transaction
 * @transaction: transaction to compute the hash of
 * @hash_buf: buffer in which to store the computed hash
 *
 * Return: a pointer to hash_buf
*/
uint8_t *transaction_hash(
	transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	uint8_t *buf_to_hash;
	uint32_t i;
	tx_in_t *this_input;
	tx_out_t *this_output;

	if (!transaction || !hash_buf)
		return (NULL);

	calculate_dimensions(transaction);

	buf_to_hash = malloc(dims[2]);
	if (!buf_to_hash)
		return (NULL);

	for (i = 0; i < dims[0]; i++)
	{
		this_input = llist_get_node_at(transaction->inputs, i);
		memcpy(buf_to_hash + buffer_offset,
			this_input,
			TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH);
		buffer_offset += TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH;
	}
	for (i = 0; i < dims[1]; i++)
	{
		this_output = llist_get_node_at(transaction->outputs, i);
		memcpy(buf_to_hash + buffer_offset,
			this_output->hash,
			SHA256_DIGEST_LENGTH);
		buffer_offset += SHA256_DIGEST_LENGTH;
	}
	SHA256(buf_to_hash, dims[2], hash_buf);
	free(buf_to_hash);

	return (hash_buf);
}
