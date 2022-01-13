#include <stddef.h>


int Strcmp(const char *s1, const char *s2){
   
    for (;*s1 && *s2 && (*s1 == *s2); s1++, s2++)
    {
    	/* do nothing*/
    }
    
    return *s1 - *s2;
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

char* Strncat(char* destination, const char* source, size_t num)
{
	char* ptr = destination + Strlen(destination);
 
   while (*source != '\0' && num--) {
        *ptr++ = *source++;
    }
 
    *ptr = '\0';
 
    return destination;
}
