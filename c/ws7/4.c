#include <stddef.h>
#include <string.h>


char* Strncat(char* destination, const char* source, size_t num)
{
	char* ptr = destination + strlen(destination);
 
   while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }
 
    *ptr = '\0';
 
    return destination;
}


size_t Strlen(char  *ptr)
{	
	size_t count = 0;
	
	while (*ptr)
	
	{	
		count++;
		ptr++;
	}
	
	return count;
}

const char* Strstr(const char* string, const char* search)
{
	int search_len = strlen(search);
    while (*string != '\0')
    {
        if ((*string == *search) && !(strncmp(string, search, search_len))) {
        	return string;
        }
        string++;
    }
 
    return NULL;
}


