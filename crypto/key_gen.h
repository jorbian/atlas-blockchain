#ifndef KEY_GEN_H
#define KEY_GEN_H

#define MAX_PATH_LEN 1025

#define PRIVATE 0
#define PUBLIC 1
#define NUM_KEYS 2

const char *key_file_names[] = {
	#define KEY_FILE(a, b) b,
		#include "key_file.def"
	#undef KEY_FILE
};

#endif
