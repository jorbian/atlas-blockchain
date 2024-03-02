#include "transaction.h"


/**
 * input_selector - function to select inputs
 * @input_list: input list
 * @all_unspent: the list of all the unspent outputs to date
 * @amount: the amount to send
 * @key_in: sender public key
 * Return: balance for the transaction
 */
static uint32_t input_selector(
	llist_t *input_list, llist_t *all_unspent,
	uint32_t amount, uint8_t key_in[EC_PUB_LEN])
{
	tx_in_t *tx_in_curr;
	unspent_tx_out_t *usp;
	int i, diff;
	uint32_t balance = 0;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		usp = llist_get_node_at(all_unspent, i);
		diff = memcmp(usp->out.pub, key_in, EC_PUB_LEN);
		if (diff == 0)
		{
			tx_in_curr = tx_in_create(usp);
			llist_add_node(input_list, tx_in_curr, ADD_NODE_REAR);
			balance += usp->out.amount;
			if (balance >= amount)
				break;
		}
	}
	return (balance);
}


/**
 * tx_init - create and initialize transaction_t
 *
 * Return: pointer to transaction_t (or NULL)
 */
static transaction_t *tx_init(void)
{
	transaction_t *new_transaction;

	new_transaction = malloc(sizeof(transaction_t));
	if (new_transaction == NULL)
		return (NULL);

	new_transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	if (!new_transaction->inputs)
		goto overall_failure;

	new_transaction->outputs = llist_create(MT_SUPPORT_FALSE);
	if (!new_transaction->outputs)
		goto output_alloc_fail;

	return (new_transaction);

output_alloc_fail:
	llist_destroy(new_transaction->inputs, 0, NULL);

overall_failure:
	free(new_transaction);

	return (NULL);
}

/**
 * transaction_create - creates a transaction
 * @sender: private key of the transaction sender
 * @receiver: contains the public key of transaction receiver
 * @amount: amount to send
 * @all_unspent: all unspent outputs to date
 *
 * Return: pointer to transaction (or NULL)
*/
transaction_t *transaction_create(
	EC_KEY const *sender,
	EC_KEY const *receiver,
	uint32_t amount, llist_t *all_unspent)
{
	transaction_t *new_transaction = NULL;
	tx_out_t *tx_out;
	tx_in_t *tx_in;
	uint8_t key_in[EC_PUB_LEN], key_out[EC_PUB_LEN];
	int i;
	uint32_t balance = 0;

	ec_to_pub(sender, key_in);
	ec_to_pub(receiver, key_out);

	new_transaction = tx_init();
	if (new_transaction == NULL)
		return (NULL);

	balance = input_selector(
		new_transaction->inputs,
		all_unspent, amount, key_in
	);
	if (balance < amount) /* if not enough to proceed the transaction */
		goto abort_txn_initilization;

	tx_out = tx_out_create(amount, key_out); /* create outputs */
	llist_add_node(new_transaction->outputs, tx_out, ADD_NODE_REAR);
	if (balance > amount) /* extra action for sending back the difference */
	{
		tx_out = tx_out_create(balance - amount, key_in);
		llist_add_node(new_transaction->outputs, tx_out, ADD_NODE_REAR);
	}
	transaction_hash(new_transaction, new_transaction->id);
	/* sign the inputs with computed hash */
	for (i = 0; i < llist_size(new_transaction->inputs); i++)
	{
		tx_in = llist_get_node_at(new_transaction->inputs, i);
		if (tx_in_sign(tx_in, new_transaction->id, sender, all_unspent) == 0)
			goto abort_txn_initilization;
	}
	return (new_transaction);

abort_txn_initilization:
	llist_destroy(new_transaction->inputs, 0, NULL);
	llist_destroy(new_transaction->outputs, 0, NULL);
	free(new_transaction);

	return (NULL);
}

