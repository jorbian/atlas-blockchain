#include "transaction.h"

static transaction_t *new_coinbase;
static tx_in_t *tx_in;
static tx_out_t *tx_out;
static uint8_t pub_key[EC_PUB_LEN];

/**
 * allocate_memory_for_structs - allocated memory for needed structs
 *
 * Return: 1 if memory was allocated, 0 if it was not
*/
static uint32_t allocate_memory_for_structs(void)
{
	new_coinbase = calloc(1, sizeof(transaction_t));
	if (!new_coinbase)
		goto about_cb_creation;

	tx_in = calloc(1, sizeof(tx_in_t));
	if (!tx_in)
		goto tx_inputs_alloc_failure;

	tx_out = tx_out_create(COINBASE_AMOUNT, pub_key);

	if (tx_out != NULL)
		return (1);

	free(tx_in);

tx_inputs_alloc_failure:
	free(new_coinbase);

about_cb_creation:
	return (0);
}

static void init_parameter_struct(llist_t **param_list, void **host)
{
	*param_list = llist_create(MT_SUPPORT_FALSE);
	llist_add_node(*param_list, (llist_node_t *)*host, ADD_NODE_REAR);
}

/**
 * coinbase_create - creates a coinbase transaction
 * @receiver: public key of miner, who will receive coinbase coins
 * @block_index: index of Block transaction will belong to
 *
 * Return: pointer to transaction upon success (or NULL)
*/
transaction_t *coinbase_create(
	EC_KEY const *receiver,
	uint32_t block_index)
{
	if (!receiver || !ec_to_pub(receiver, pub_key))
		return (NULL);

	if (!allocate_memory_for_structs())
		return (NULL);

	memcpy(tx_in->tx_out_hash, &block_index, 4);

	init_parameter_struct(&(new_coinbase->inputs), (void **)&tx_in);
	init_parameter_struct(&(new_coinbase->outputs), (void **)&tx_out);

	if (!transaction_hash(new_coinbase, new_coinbase->id))
		goto abort_cb_creation;

	return (new_coinbase);

abort_cb_creation:
	llist_destroy(new_coinbase->inputs, 0, NULL);
	free(tx_in);
	llist_destroy(new_coinbase->outputs, 0, NULL);
	free(tx_out);
	free(new_coinbase);
	return (NULL);
}
