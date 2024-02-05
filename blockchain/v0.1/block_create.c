#include <string.h>
#include <time.h>

#include "blockchain.h"

static block_t const _genesis = {
	{ /* info */
		0 /* index */,
		0, /* difficulty */
		1537578000, /* timestamp */
		0, /* nonce */
		{0} /* prev_hash */
	},
	{ /* data */
		"Holberton School", /* buffer */
		16 /* len */
	},
	"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"
	"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
	/* hash */
	/* c52c26c8b5461639635d8edf2a97d48d0c8e0009c817f2b1d3d7ff2f04515803 */
};

/**
 * add_previous - add previous block in the chain -- if there was one
 * @prev: pointer to the previous block
 * @new: the new block in the process of being created.
 *
*/
static void add_previous(block_t const *prev, block_t *new)
{
	new->info.index = prev->info.index + 1;

	memcpy(
		new->info.prev_hash,
		prev->hash,
		sizeof(prev->hash)
	);
}

/**
 * fill_data_in - actually fill the new data in
 * @new: pointer to the new block being created
 * @d: the data to be filled in
 * @len: how long it is in bytes
 *
*/
static void fill_data_in(block_t *new, int8_t const *d, uint32_t len)
{
	time((time_t *)&new->info.timestamp);

	if (len > BLOCKCHAIN_DATA_MAX)
		len = BLOCKCHAIN_DATA_MAX;

	memcpy(new->data.buffer, d, len);

	new->data.len = len;
}
/**
 * block_create - Create a new block to go in the blockchain
 * @prev: The address of the previous block in the blockchain
 * @data: The place in memory to duplicate to store in the block's data
 * @data_len: The size in bytes of the data to duplicate and store
 * Return: The address of the newly created block
*/
block_t *block_create(
	block_t const *prev, int8_t const *data, uint32_t data_len)
{
	block_t *new_block;

	new_block = calloc(1, sizeof(block_t));
	if (!new_block)
		return (NULL);

	if (prev)
		add_previous(prev, new_block);

	fill_data_in(new_block, data, data_len);

	return (new_block);
}
