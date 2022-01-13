#include <stdio.h>  /*printf*/
#include <string.h> /*strcpy, strncpy, strcmp, strchr,
					  strcat, strncat, stdspn, strstr*/
#include <strings.h> /*strcasecpm*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include <ctype.h> /* tolower*/

char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);
int Strcmp(const char *s1, const char *s2);
void Tolower(char *str);
int Srtcasecmp(const char *str1, const char *str2);
char *Strchr(const char *string, int serch);

char *Strdup(const char *s); 
char *Strcat(char *dest, const char *src);
char *Strncat(char *dest, const char *src, size_t n);
const char* Strstr(const char* string, const char* search_value);
size_t StrSpn(const char *str1, const char *str2);
void print_until_token( char *str, const char *delim);
char *StrTok(char *str, const char *delim);

void test(int x);


/*-----test------*/
void test_Strcpy();
void test_Strncpy();
void test_Strcmp();
void test_Srtcasecmp();
void test_Strchr();
void test_Strdup();
void test_Strcat();
void test_Strncat();
void test_Strstr();
void TestStrSpn();
void test(int x);

void general_test_Srtcasecmp(const char *s1, const char *s2);
void general_test_Strcmp(const char *s1, const char *s2);
void general_test_Strncpy(const char *src, size_t n);
void general_test_Strchr(const char *string, int serch);
void general_test_Strdup(const char *source);
void general_test_Strcat(char *dest, const char *src);
void general_test_Strncat(char *dest, const char *src, size_t n);

int CheckPalindrome(char *str);
void test_CheckPalindrome();


int main()
{
	test_Strcpy();
	test_Strncpy();
	test_Strcmp();
	test_Srtcasecmp();
	test_Strchr();
	test_Strdup();
	test_Strcat();
	test_Strncat();
	test_Strstr();
	TestStrSpn();
	
	return 0;
}


/*----------------------Strcpy----------------------------*/


char *Strcpy(char *dest, const char *src)
{	
	while (*src)
	{
		*dest++ = *src++;
	}
	
	*dest = '\0';
	
	return dest;
}

void test_Strcpy()
{	
	const char str[] = "david";
    char *my_str = "";
    char *library_str = "";
    
	my_str = Strcpy(my_str, str);
  	library_str = strcpy(library_str, str);
  	
  	
  	printf("test-strcpy     >> ");
  	test(strcmp(my_str, library_str));
}
/*----------------------Strncpy----------------------------*/


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

void general_test_Strncpy(const char *src, size_t n)
{
	char *my_dest = (char *)calloc(strlen(src),1);
	char *library_dest = (char *)calloc(strlen(src),1);
	
	strncpy(my_dest, src, n);
   	Strncpy(library_dest, src, n);
	
	printf("test-strncpy    >> ");
	test(strcmp(my_dest, library_dest));
	
	free(my_dest);
	free(library_dest);
	my_dest = NULL;
	library_dest = NULL;
	
}

void test_Strncpy()
{	
   	general_test_Strncpy("abgfdc", 3); /*n<src*/
   	general_test_Strncpy("skd", 6);	/*n>src*/
   	general_test_Strncpy("", 3);  
   	general_test_Strncpy("gwkaccnvnvmdkvmvn", 0);   
   	  	 		 	
}
/*----------------------------Strcmp----------------------------------*/

int Strcmp(const char *s1, const char *s2)
{
	int difference;
	
	while(*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
   	
   	difference = *s1 - *s2;
   	
    return difference;
}

void general_test_Strcmp(const char *s1, const char *s2)
{	
	int Comparison;
	int my_result= Strcmp(s1, s2);
	int expected_result = strcmp(s1, s2);
	
	Comparison = expected_result == my_result;
	printf("test-Strcmp     >> ");
	
	test(!Comparison);
}

void test_Strcmp()
{
	general_test_Strcmp("a", "Rhtea");
	general_test_Strcmp("befsbfrgwr", "123");
	general_test_Strcmp("&$", "");
	general_test_Strcmp("5+4 = 9", "  ");
	

}


/*---------------------Srtcasecmp-------------------------*/

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

void general_test_Srtcasecmp(const char *s1, const char *s2)
{	
	int Comparison;
	int my_result= Strcmp(s1, s2);
	int expected_result = strcmp(s1, s2);
	
	Comparison = expected_result == my_result;
	printf("test-Strncmp     >> ");
	
	test(!Comparison);
}

void test_Srtcasecmp()
{
	general_test_Srtcasecmp("a", "Rhtea");
	general_test_Srtcasecmp("befsbfrgwr", "123");
	general_test_Srtcasecmp("&$", "");
	general_test_Srtcasecmp("5+4 = 9", "  ");
	

}

/*-------------------Strchr---------------------------*/

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

void general_test_Strchr(const char *string, int serch)
{
	char * my_result = Strchr(string, serch);
	char * expected_result = strchr(string, serch);
	
	int result = expected_result - my_result;
	
	printf("test-Strchr     >> ");
	test(!result);
}



void test_Strchr()
{
	general_test_Strchr("1KS3Dr4", 'd');
	general_test_Strchr("1234", '5');
	general_test_Strchr("1a34", 'A');	
}

		
/*--------------------Strdup--------------------------*/	


char *Strdup(const char *source)
{	
	char *new_arr = (char*)malloc(sizeof(*source));
	
	Strcpy(new_arr ,source);
	
	return  new_arr;
}

void general_test_Strdup(const char *source)
{
	char* new_arry = Strdup(source);
	
	printf("test-Strdup     >> ");
	test( strcmp(new_arry, source) );
	
	free(new_arry);
	new_arry = NULL;
}

void test_Strdup()
{
	general_test_Strdup("cvsfvsfa");
	general_test_Strdup("");
	general_test_Strdup("0");
}



/*---------------------Strcat-------------------------*/


char *Strcat(char *dest, const char *src)
{	
	char *start_dest = dest;
	char *end_dest = dest+strlen(dest);
	
	assert(src);
	assert(dest);
	Strcpy(end_dest, src);
	
	return start_dest;

}

void general_test_Strcat(char *dest, const char *src)
{
	int Comparison;
	int total_length = strlen(dest) + strlen(src);
	char *my_target = (char *)calloc(total_length, 1);
	char *library_target = (char *)calloc(total_length, 1);
	
	assert(my_target);
	assert(library_target);
	
	strcpy(my_target, dest);
	strcpy(library_target, dest);
	
	Strcat(my_target, src);
	strcat(library_target, src);
	
	Comparison = strcmp(my_target, library_target);
	printf("test-strcat     >> ");
	test(Comparison);

	free(my_target);
	free(library_target);
	my_target = NULL;
	library_target = NULL;
}

void test_Strcat()
{
	general_test_Strcat("vmfkdlm", "");
	general_test_Strcat("A&h", "dfbrgbrtbesegtrrtb");
}


/*--------------------Strncat-------------------------*/

char *Strncat(char *dest, const char *src, size_t n)
{	
	
	size_t dest_len = strlen(dest);
	char *dest_end = dest + dest_len;
	Strncpy(dest_end,src,n);
	
	return dest;

}

void general_test_Strncat(char *dest, const char *src, size_t n)
{
	int Comparison;
	int total_length = strlen(dest) + strlen(src);
	char *my_target = (char *)calloc(total_length, 1);
	char *library_target = (char *)calloc(total_length, 1);
	
	assert(my_target);
	assert(library_target);
	
	strcpy(my_target, dest);
	Strncat(my_target, src, n);
	
	strcpy(library_target, dest);
	strncat(library_target, src,n);
	
	Comparison = strcmp(my_target, library_target);
	printf("test-strncat     >> ");
	test(Comparison);

	free(my_target);
	free(library_target);
	my_target = NULL;
	library_target = NULL;
}

void test_Strncat()
{
	general_test_Strncat("vmfkdlm", "",3);	/* n> src*/
	general_test_Strncat("A&h", "dfbrgbrtbesegtrrtb",4); /* n< src*/
	general_test_Strncat("", "",0);
}


/*------------------------strstr--------------------------------*/


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

void test_Strstr()
{
	char s1[] = "abcdefg";
    char s2[] = "efg";
    char* expected_result;
	char* my_result;
  
	my_result = (char *)strstr(s1, s2);
    expected_result = (char *)Strstr(s1, s2);

	printf("test-strstr     >> ");	
    test(expected_result != my_result);
}

/*------------------------strspn--------------------------------*/

size_t StrSpn(const char *str1, const char *str2)
{
	int Counts_common = 0;	
	
	while (*str1)
	{
		if(strchr(str2, *str1))
		{
			Counts_common++;
		}
		str1++;
	}
	
	return Counts_common;
}

void TestStrSpn()
{
	int expected_result = strspn("12345", "123");
	int my_result = StrSpn("12345", "123");
	
	printf("test-strspn     >> ");
	test(expected_result != my_result);
}

/*------------------------strtok--------------------------------

void print_until_token( char *str, const char *delim)
{
	while (*str != *strchr(str, *delim) )
	{	printf("%c", *str);
		str++;
	}
}

char *StrTok(char *str, const char *delim)
{	
	while (*str)
	{
		print_until_token(str, delim);
		str++;
	}
}*/

/*-----------------------------test------------------------------------*/

void test(int check)
{
	if(check)
	{
		printf("fails\n");
	}
	else
	{
		printf("success\n");
	}

}

/*---------------------CheckPalindrome--------------------------*/

int CheckPalindrome(char *str)
{	
	int res = 1;
	int left_index = strlen(str)-1;
	int right_index = 0;
	
	
	while (right_index > left_index)
	{
		if(tolower(str[right_index]) != tolower(str[left_index]))
		{
			res = 0;
			break ;
		}
		
		right_index--;
		left_index++;
	}
	return res;
}


void test_CheckPalindrome()
{
	
	char a[] = "Adhbhda";
	
	if(CheckPalindrome(a))
	{  
    	printf(" The function works ");  
    }
	else
	{  
   	 	printf(" The function failed ");  
	}
	
		
}

	
	
	















