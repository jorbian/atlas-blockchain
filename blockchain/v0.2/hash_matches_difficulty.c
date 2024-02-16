#include "blockchain.h"

/**
 * count_leading_zeros - count the number of leading zeros in provided hash
 * @array: pointer to the hashed data
 * @size: how big the data is
 *
 * Return: How many leading zeros there were.
*/
static uint32_t count_leading_zeros(uint8_t const *array, uint32_t size)
{
	uint32_t leading_zeros = 0;
	uint32_t i, j, value;

	for (i = 0; i < size; i++)
	{
		value = array[i];

		for (j = 7; j >= 0; j--)
		{
			if ((value >> j) & 1)
				break;

			leading_zeros++;
		}
		if ((value >> j) & 1)
			break;
	}
	return (leading_zeros);
}

/**
 * hash_matches_difficulty - checks if hash matches a given difficulty
 * @hash: hash to check
 * @difficulty: minimum difficulty the hash should match
 *
 * Return: 1 if the difficulty is respected, or 0 otherwise
*/
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
	uint32_t difficulty)
{
	if (count_leading_zeros(hash, SHA256_DIGEST_LENGTH) >= difficulty)
		return (1);

	return (0);
}
