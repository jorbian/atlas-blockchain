#include "transaction.h"

/**
 * calculate_hash_size - calculate the needed size of hash buffer
 * @txn: pointer to the transaction struct
 *
 * Return: Whatever size ends up being needed.
*/
static uint32_t calculate_hash_size(transaction_t const *txn)
{
	return (
		(llist_size(txn->inputs) * TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH) +
		(llist_size(txn->outputs) * SHA256_DIGEST_LENGTH)
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
	uint32_t buf_to_hash_len, buffer_offset = 0, input_qty, output_qty;
	uint32_t index;
	tx_in_t *this_input;
	tx_out_t *this_output;

	if (!transaction || !hash_buf)
		return (NULL);

	buf_to_hash = malloc(calculate_hash_size(transaction));
	if (!buf_to_hash)
		return (NULL);

	for (index = 0; index < input_qty; index++)
	{
		this_input = llist_get_node_at(transaction->inputs, index);
		memcpy(buf_to_hash + buffer_offset,
			this_input,
			TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH);
		buffer_offset += TX_IN_HASH_QTY * SHA256_DIGEST_LENGTH;
	}
	for (index = 0; index < output_qty; index++)
	{
		this_output = llist_get_node_at(transaction->outputs, index);
		memcpy(buf_to_hash + buffer_offset,
			this_output->hash,
			SHA256_DIGEST_LENGTH);
	}
	SHA256(buf_to_hash, buf_to_hash_len, hash_buf);
	free(buf_to_hash);

	return (hash_buf);
}
