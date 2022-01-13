#include <string.h>
#include <assert.h>
#include <stdlib.h>




char *Strcat(char *dest, const char *src)
{	
	char *start_dest = dest;
	char *end_dest = dest+strlen(dest);
	
	assert(src);
	assert(dest);
	strcpy(end_dest, src);
	
	return start_dest;

}

char *Strcpy(char *dest, const char *src)
{	
	while (*src)
	{
		*dest++ = *src++;
	}
	
	*dest = '\0';
	
	return dest;
}

char *Strdup(const char *source)
{	
	char *new_arr = (char*)malloc(sizeof(*source));
	
	Strcpy(new_arr ,source);
	
	return  new_arr;
}

