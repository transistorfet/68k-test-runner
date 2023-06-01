
#include <string.h>


char *strcpy(char *dest, const char *src)
{
	char *ret = dest;

	for (; *src != '\0'; src++, dest++)
		*dest = *src;
	*dest = '\0';
	return ret;
}

