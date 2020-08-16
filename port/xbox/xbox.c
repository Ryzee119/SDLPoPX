#include "common.h"
#include <stdio.h>

size_t strnlen (const char *s, size_t maxlen){
	size_t i;
	for (i = 0; i < maxlen; ++i)
		if (s[i] == '\0')
			break;
	return i;
}

int _access (const char *__name, int __type){
	(void)__type;
	FILE* fp = fopen(__name, "rb");
	if(fp){
		fclose(fp);
		return 1;
	}
	return -1;
}