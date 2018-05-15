#include "ladon.h"

void *zmemccpy(void *dst, const void *src, int c, size_t count)
{
	char *a = (char*)dst;
	const char *b = (const char *)src;
	while (count--)
	{
		*a++ = *b;
		if (*b == c)
		{
			return (void *)a;
		}
		b++;
	}
	return 0;
}

char *zstrncpy(char *dest, const char *src, size_t n) {

	zmemccpy(dest, src, 0, n);
	return dest;
}