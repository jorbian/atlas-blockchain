#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_create - creates a new EC key pair.
 *
 * Return: pointer to EC_KEY (or NULL upon failure)
*/
EC_KEY *ec_create(void)
{
	EC_KEY *myecc = NULL;
	EVP_PKEY *pkey = NULL;

	int eccgrp;

	OpenSSL_add_all_algorithms();

	eccgrp = OBJ_txt2nid("secp521r1");

	myecc = EC_KEY_new_by_curve_name(eccgrp);

	EC_KEY_set_asn1_flag(myecc, OPENSSL_EC_NAMED_CURVE);

	if (!(EC_KEY_generate_key(myecc)))
		return (NULL);

	pkey = EVP_PKEY_new();
	if (!EVP_PKEY_assign_EC_KEY(pkey, myecc))
		return (NULL);

	return (myecc);
}
