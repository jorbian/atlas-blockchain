#ifndef KEY_GEN_H
#define KEY_GEN_H

#define MAX_PATH_LEN 1025

/**
 * key_file_num - storing indecies used to find keyfiles
 * @define: asdf adfs
 * @include: asdf
 * @undef: asdf
*/
enum key_file_num
{
	#define KEY_FILE(a, b) a,
		#include "key_file.def"
	#undef KEY_FILE
};

const char *key_file_names[] = {
	#define KEY_FILE(a, b) b,
		#include "key_file.def"
	#undef KEY_FILE
};

#endif
