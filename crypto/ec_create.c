#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/pem.h>

#include "hblk_crypto.h"

/**
 * ec_create - creates a new EC key pair.
 *
 * Return: pointer to EC_KEY (or NULL upon failure)
*/
EC_KEY *ec_create(void)
{
	EC_KEY *new_ec_key = NULL;

	OpenSSL_add_all_algorithms();

	new_ec_key = EC_KEY_new_by_curve_name(EC_CURVE);

	EC_KEY_set_asn1_flag(new_ec_key, OPENSSL_EC_NAMED_CURVE);

	if (!(EC_KEY_generate_key(new_ec_key)))
		return (NULL);

	return (new_ec_key);
}
