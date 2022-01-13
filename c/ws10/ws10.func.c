#include <stdio.h>/*print*/
#include <stdlib.h>/*malloc*/

#include "ws10.h"

#define INVALID 0
#define OPTIONAL 1
#define VALID 2
#define ASCII 256

char *ItoaBase10(int num);
int AtoiBase10(char* str);
void swap(char *x, char *y);
void reverse(char *str, int length);
int IsNumericChar(char x);


/*-------------------------SelectedElements--------------------------------*/

void SelectedElements(char a1[], int size1, char a2[], int size2, char a3[], int size3)
{
	char buffer[ASCII];
	int i = 0;
	
	for (; i < 256; i++)
	{
		buffer[i] = OPTIONAL;
	}

	for (i = 0; i < size3; i++)
	{
		buffer[(unsigned char)a3[i]] = INVALID;
	}
	
	for (i = 0; i < size2; i++)
	{
		if (OPTIONAL == buffer[(unsigned char)a2[i]])
		{
			buffer[(unsigned char)a2[i]] = VALID;
		}
		
	}
	
	for (i = 0; i < size1; i++)
	{
		if (VALID == buffer[(unsigned char)a1[i]])
		{
			printf("%c, ",a1[i]);
		}
		
		
	}
	/*
	for (i = 0; i < 256; i++)
	{
		if (VALID == buffer[i])
		{
			printf("%c, ",(char)i);
		}
	}
	*/
	printf("\n");
	
}

/*-----------------------------Atoi-----------------------------------*/

int Atoi(char* str)
{
	int res = 0 ,i = 0, is_negative = 0;

 	while (str[i] == ' ')
    {
        i++;
    }
 	
 	if (str[i] == '-')
 	{
 		i++;
 		is_negative = 1;
 	}
 	
    for (; str[i] != '\0'; ++i)
    {
        if (IsNumericChar(str[i]) == 0)
        {
        	return 0;
        }
        
        res = res * 10 + str[i] - '0';
     }
 	
 	if (is_negative)
 	{
 		res = -res;
 	}
 	
 	return res;
}

/*---------------------------Itoa------------------------------------*/

char *Itoa(int value, char *string, int base)
{
	int i = 0, is_negative = 0;
	
	if (value == 0)
    {
        *string = '0';
        *(string + 1) = '\0';
        
        return string;
    }
    
    if (value < 0 && 10 == base)
    {
        value = -value;
        is_negative = 1;
    }
    
    while (value)
    {
      	int remainder = value % base;
    	
    	if (remainder > 9)
    	{
    		*(string + i) = 'a' + (remainder - 10);
    	}
    	else
    	{
    		*(string + i) = remainder + '0';
    	}
    	
    	i++;
    	value /= base;
    }
    
    if (is_negative)
    {
    	*(string + i) = '-';
    	i++;
    }
    
    *(string + i) = '\0';
    i++;
    
    reverse(string, i - 1);
    
    return string;
}

/*-------------------------IsLittleEndian---------------------------------------*/

void IsLittleEndian()
{
	unsigned short test = 1;
	char *t =(char*)&test;
	
	if (*t == 1)
	{
		printf("the system is Little Endian\n");
	}
	else 
	{
		printf("the system is not Little Endian\n");
	}
}

/*-----------------------------------------------*/

char *ItoaBase10(int num)
{
	int number_of_digits = 1;
	char *string = NULL;
	int save_num = num, is_negative = 0;
	
	if (num < 0)
	{
		num = -num;
		is_negative = 1;
	}
	
	while (save_num)
	{
		save_num /=  10;
		number_of_digits++; 
	}

	string = (char*)malloc(number_of_digits + is_negative);
	
	if (num == 0)
    {
        string[0] = '0';
        string[1] = '\0';
        return string;
    }
	
	string = string + number_of_digits + 1;
	*string = '\0';
	
	while (num)
	{
		string--;
		*string = (char)(num % 10) + '0';
		num /= 10;
	}
	
	if (is_negative)
	{
		string--;
		*string = '-';		
	}
	
	return string;
}

/*-----------------------------------------------*/

int AtoiBase10(char* str)
{

    int res = 0 ,i = 0, is_negative = 0;

 	while (str[i] == ' ')
    {
        i++;
    }
 	
 	if (*str == '-')
 	{
 		str++;
 		is_negative = 1;
 	}
 	
    for (; str[i] != '\0'; ++i)
    {
        if (IsNumericChar(str[i]) == 0)
        {
        	return 0;
        }
        
        res = res * 10 + str[i] - '0';
     }
 	
 	if (is_negative)
 	{
 		res = -res;
 	}
 	
 	return res;
}

/*---------------------------------------------------------------------*/

void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}
/*---------------------------------------------------------------------*/
void reverse(char *str, int length)
{
    int start = 0;
    int end = length -1;
    
    while (start < end)
    {
        swap(str + start, str + end);
        start++;
        end--;
    }
}
/*-------------------------------------------------*/
int IsNumericChar(char x)
{
    return (x >= '0' && x <= '9') ? 1 : 0;
}
/*--------------------------*/
void test_endian( void )
{
    int test_var = 1;
    unsigned char *test_endian = (unsigned char*)&test_var;

    if (0 == *test_endian)
    {
    	printf("big endian");
    }
    else
    {
    	printf("little endian");
    }
}



/*
char* Itoa(int num, char* string, int base)
{
	int number_of_digits = 0;
	int remainder = 0;
	int save_num = num, is_negative = 0;
	char *end_of_str = NULL;
	char *save_string = string;
	
	if (num < 0 && 10 == base)
	{
		num = -num;
		is_negative = 1;
	}
	
	while (save_num)
	{
		save_num /=  10;
		number_of_digits++; 
	}
	
		printf("%d\n",number_of_digits);
	
	end_of_str = string;
	end_of_str += (number_of_digits + is_negative);
	*end_of_str = '\0';
	
	while (num)
	{
		string--;
		remainder = num % base;
		
		if (remainder > 9)
		{
			*string = (char)remainder - 10 + 'a';
		}
		else
		{
			*string = (char)remainder + '0';
		}
		
		num /= base;
	}
	
	if (is_negative)
	{
		string--;
		*string = '-';		
	}
	
	return save_string;
	
	while(size3)
	{
		buffer[(int)a3[size3-1]] = INVALID;
		size3--;
	}
	for (; i < 256; i++)
	{
		if(buffer[i] == 4)
		{
			printf("%d",i);
		}
	}
	
	printf("\n");
	while(size2)
	{
		if (OPTIONAL == buffer[(int)a2[size2]])
		{
			buffer[(int)a2[size2-1]] = VALID;
		}
		else
		{
			buffer[(int)a2[size2-1]] = INVALID;
		}
		size2--;
	}
	
	while(size1)
	{
		if (OPTIONAL == buffer[(int)a1[size1]])
		{
			buffer[(int)a1[size1-1]] = VALID;
		}
		
		else 
		{
			buffer[(int)a1[size1-1]] = INVALID;
		}
		size1--;
	}
	
	i = 0;
	
	for (; i < 256; i++)
	{
		if (VALID == buffer[i])
		{
			printf("%c, ",(char)i);
		}
	}
}*/






