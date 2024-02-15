#include "blockchain.h"

/**
 * hash_matches_difficulty - checks if hash matches a given difficulty
 * @hash: hash to check
 * @difficulty: minimum difficulty the hash should match
 *
 * Return: 1 if the difficulty is respected, or 0 otherwise
*/
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH], uint32_t difficulty)
{
	(void)hash;
	(void)difficulty;

	return (0);
}
