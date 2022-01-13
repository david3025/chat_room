#include <stddef.h>
#include <stdio.h>
#include <ctype.h>


char *Strncpy(char *dest, const char *src, size_t n)
{	
	char *const_dest = dest;
	
	if (NULL == dest)
	{
		return NULL;
	}
	
	while (*src && n )
	{
		*dest = *src;
		
		dest++;
		src++;
		n--;
	}
	
	while (n)
	{
		*dest= '\0';
		dest++;
		n--;
	}
	*dest = '\0';
	
	return const_dest;
	
}

int Srtcasecmp(const char *str1, const char *str2)
{	
	int result = 0;
	
	while (*str1 || *str2 )
	{       
	
		int str1_lower = tolower(*str1);
		int str2_lower = tolower(*str2);
			
		if (str1_lower != str2_lower)
		{
			result = str1_lower - str2_lower;
			break;
		}
		str1++;
		str2++;
	}

	return result;
}

char *Strchr(const char *string, int serch)
{	
	char *find = NULL;
	
	while (string)
	{
		if (*string == serch)
		{	
			find = (char *)string; 
			break;
		} 
			
		string++;
	}
	
	return find;
}
size_t StrSpn(const char *str1, const char *str2)
{
	int Counts_common = 0;	
	
	while (*str1)
	{
		if(Strchr(str2, *str1))
		{
			Counts_common++;
		}
		str1++;
	}
	
	return Counts_common;
}



