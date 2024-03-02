#include "transaction.h"

#define INPUTS 0
#define OUTPUTS 1
#define HASH 2

static uint32_t dims[3];
static uint32_t item_size[2] = {
	(TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH),
	(SHA256_DIGEST_LENGTH)
};
static uint32_t buffer_offset;

/**
 * calculate_dimensions - calculates the overall dimensions of txn
 * @txn: pointer to the transaction struct fed into wrapper.
 *
*/
static void calculate_dimensions(transaction_t const *txn)
{
	dims[INPUTS] = llist_size(txn->inputs);
	dims[OUTPUTS] = llist_size(txn->outputs);
	dims[HASH] = (
		(dims[INPUTS] * item_size[INPUTS]) +
		(dims[OUTPUTS] * item_size[OUTPUTS])
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

	buffer_offset = 0;

	if (!transaction || !hash_buf)
		return (NULL);

	calculate_dimensions(transaction);

	buf_to_hash = malloc(dims[2]);
	if (!buf_to_hash)
		return (NULL);

	for (i = 0; i < dims[INPUTS]; i++)
	{
		this_input = llist_get_node_at(transaction->inputs, i);
		memcpy(buf_to_hash + buffer_offset,
			this_input,
			item_size[INPUTS]);
		buffer_offset += item_size[INPUTS];
	}
	for (i = 0; i < dims[1]; i++)
	{
		this_output = llist_get_node_at(transaction->outputs, i);
		memcpy(buf_to_hash + buffer_offset,
			this_output->hash,
			item_size[OUTPUTS]);
		buffer_offset += item_size[OUTPUTS];
	}
	SHA256(buf_to_hash, dims[2], hash_buf);
	free(buf_to_hash);

	return (hash_buf);
}
