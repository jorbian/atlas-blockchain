#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hblk_crypto.h"

/**
 * ec_from_pub - creates EC_KEY struct given public key
 * @pub: public key to be converted
 *
 * Return: pointer to EC_KEY struct (or NULL upon failure)
*/
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	const EC_GROUP *ec_group;

	EC_POINT *ec_point;
	EC_KEY *ec_key;

	if (!pub)
		return (NULL);

	ec_key = EC_KEY_new_by_curve_name(EC_CURVE);
	ec_group = EC_KEY_get0_group(ec_key);
	ec_point = EC_POINT_new(ec_group);

	if (!ec_point)
		goto no_point;

	if (
		(!EC_POINT_oct2point(ec_group, ec_point, pub, EC_PUB_LEN, NULL)) ||
		(!EC_KEY_set_public_key(ec_key, ec_point))
	)
		goto failure;

	EC_POINT_free(ec_point);

	return (ec_key);

failure:
	EC_POINT_free(ec_point);

no_point:
	EC_KEY_free(ec_key);
	return (NULL);
}
