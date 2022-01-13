#include "ws9.h"

#define WORD 8

long DupCharToLong(char num);

/*-----------------------------------*/

void *Memset(void *dest, int c, size_t n)
{
	char *destination = dest;
	long *destination_long = NULL;
	long dup_char = DupCharToLong((char)c);
	
	while ((0 != (long)destination % WORD) && n)
	{
		*destination = (char)c;
		destination++;
		n--;
	}
	
	destination_long = (long*)destination;
	
	while (n >= WORD)
	{
		*destination_long++ = dup_char;
		n = n - WORD;
	}
	
	destination = (char*)destination_long;
	
	while (n)
	{
		*destination =(char)c;
		destination++;
		n--;
	}
	
	return dest;
}

/*----------------------------------------------------*/

void *Memcpy(void *dest, const void * src, size_t n)
{
    char *destination =(char *)dest;
    char *source =(char *)src;
 	long *destination_long = NULL;
 	long *source_long = NULL;   
	
	while (((long)destination % WORD != 0) && n)
	{
		*destination++ = *source++;
		n--;
	}
	
	source_long = (long*)source;	
	destination_long = (long*)destination;
		
	while (n / WORD)
	{
		*destination_long++ = *source_long++;
		n = n - WORD;
	}
	
	destination = (char*)destination_long;
	source = (char*)source_long;
	
	while (n)
	{
		*destination++ = *source++;
		n--;
	}
	
	return dest;
}

/*-------------------------------*/

void *Memmove(void *dest, const void *src, size_t n)
{
	char *source =(char *)src;
    char *destination =(char *)dest;
 	long *destination_long = NULL;
 	long *source_long = NULL;      
    
  	if((destination < source + n) && (source < destination))
    {
        destination += n - 1;
        source += n - 1;
        
        while (((long)destination % WORD != 0) && n)
		{
			*destination-- = *source--;
			n--;
		}
		
		destination_long = (long*)destination;
		source_long = (long*)source;
		
		while (n / WORD)
		{
			destination_long--;
			source_long--;
			*destination_long = *source_long;
			n -= WORD;
		}
		
		destination = (char*)destination_long;
		source = (char*)source_long;
		
		while (n)
		{
			*destination-- = *source--;
			n--;
		}  
        
    }
    else
    {
        Memcpy(destination, source, n);
    }
    return dest;
}
/*---------------------------------------*/

long DupCharToLong(char num)
{
	long result = 0;
	size_t i = 0;
	
	for (; i < WORD; i++)
	{
		result <<= WORD;
		result |= num;
	}
	
	return result;
}

	

void *DupChar(long *dest, int c)
{
    unsigned int index;
    unsigned char *memory = (unsigned char*)dest, value = c;

    for (index = 0; index < WORD; index++)
        memory[index] = value;

    return memory;
}



