 #include "blockchain.h"

/**
 * block_is_valid - verifies that a Block is valid
 * @block: points to the Block to check
 * @prev_block: points to previous Block in the chain (or NULL)
 * @all_unspent: unspent blocks
 *
 * Return: A description goes here.
*/
int block_is_valid(block_t const *block, block_t const *prev_block,
	llist_t *all_unspent)
{
	(void)block;
	(void)prev_block;
	(void)all_unspent;

	return (-1);
}
