#ifndef KEY_GEN_H
#define KEY_GEN_H

#include <openssl/ssl.h>
#include <openssl/sha.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/ecdsa.h>
#include <openssl/bio.h>

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_PATH_LEN 1025

#define PRIVATE 1
#define PUBLIC 0
#define NUM_KEYS 2

typedef EC_KEY *(*load_func)(FILE *, EC_KEY **, pem_password_cb *, void *);

static const char *key_file_names[] = {
	#define KEY_FILE(a, b, c) b,
		#include "key_file.def"
	#undef KEY_FILE
};

#ifdef __GNUC__
__extension__
#endif

static const load_func key_load_functions[] = {
	#define KEY_FILE(a, b, c) PEM_read_EC##c,
		#include "key_file.def"
	#undef KEY_FILE
};

#endif
