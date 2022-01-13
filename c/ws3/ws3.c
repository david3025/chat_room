#include <stdio.h> /*printf*/
#include <string.h>/*strlen*/
#include <stdlib.h>/*calloc*/
#include <ctype.h> /* tolower*/
#include <assert.h>/*assert*/
#include <math.h>/*log*/


size_t CountEnvpElements(char **);
char *StrdupTolower(const char *);
char **CopyingEnvp(char **envp);
void PrintAllStings(char **ToStrings);
void FreePtrToPtr(char **ToStrings);




int Josephus(int per);
int Math_Josephus(int size);
void TestJosephus(int per);
void SuperTestJosephus();

void DataType();

/*---------------------------------------------------------------------*/

int main(int argc, char *argv[], char *envp[])
{ 
	
	
	char **mycopy = CopyingEnvp (envp);
	PrintAllStings(mycopy);
	FreePtrToPtr(mycopy);
	
	free(mycopy);
	mycopy = NULL;
	
	
	assert(argc != 0 && argv != 0);
	return 0;
}

/*------------------------print_2D_array-------------------------------*/

void print_2D_array(int *arr, int m, int n)
{
    int i , j;
    
    for (i = 0; i < m; i++)
    {
      for (j = 0; j < n; j++)
      {
        printf("%d ", *(arr + i * n + j));
      }
	}
}
/*-----------------------------CopyingEnvp ------------------------------*/

char **CopyingEnvp(char **envp)
{
	int index = 0; 
	int LengthEnvp = CountEnvpElements(envp);
	char **MyEnvp = (char**)malloc(sizeof(char*) * LengthEnvp+1);
	

	while (index < LengthEnvp)
	{
		MyEnvp[index] = StrdupTolower(envp[index]);
		
		index++;
	}
	
	return MyEnvp;
}

void PrintAllStings(char **ToStrings)
{	
	while (*ToStrings)
	{
		printf("%s\n",*ToStrings);
		
		++ToStrings;
	}
}

void FreePtrToPtr(char **ToStrings)
{
	while (*ToStrings)
	{
		free(*ToStrings);
		*ToStrings = NULL;
		
		++ToStrings;
	}
}

size_t CountEnvpElements(char **envp)
{
	size_t elements = 0;
	
	while (*envp)
	{
		elements++;
		envp++;
	}
	return elements;
}


char *StrdupTolower(const char *src)
{
 	char *str = (char *)malloc(sizeof(char)*(strlen(src)+1));
 	char *save_first_element = str;
	
	while (*src)
	    {
		*str = tolower(*src);
		str++;
		src++;
	    }
	    
	    *str = '\0';
	
	return save_first_element;
}


/*-----------------------Josephus-----------------------*/

int Josephus(int per)
{
	int CurrentSoldier = 1;
	int PreviouSoldier = 0;
	int flag = 1;
	int index = 0;
	int *a = (int*)malloc(sizeof(int) * per);
	
	for( ; index < per; index++)
	{
		a[index] = index+1;

	}
	
	index = 0;
	
	while(CurrentSoldier != PreviouSoldier)
	{
		for( ;index < per; index++)
		{
			if(a[index] != 0)
			{
				if(flag == 0)
				{
					a[index] = 0;
					flag = 1;
				}
				else
				{
					PreviouSoldier = CurrentSoldier;
					CurrentSoldier = a[index];
					flag = 0;
				}
			}
		}
		
		index = 0;
	}
	
	free(a);
	a = NULL;
	
	return CurrentSoldier;
}

int Math_Josephus(int size)
{
	int max_pow = 1;
	int diff = 0;
	int winner = 0;
	
	while (max_pow * 2 <= size)
	{
		max_pow *= 2;
	}
	
	diff = size - max_pow;
	winner = 2 * diff + 1;
	
	return winner;
}

void TestJosephus(int per)
{	
	if(Math_Josephus(per) == Josephus(per))
	{
		printf("success\n");
	}
	else
	{
		printf("failure\n");		
	}
}

void SuperTestJosephus()
{
	TestJosephus(100);
	TestJosephus(1);
	TestJosephus(128);
	printf("\n<< Just a moment, I think ..... >> \n");
	TestJosephus(100000000);
}

	
void DataType()
{		


	printf("size signed char is %lu\n",sizeof(signed char));
	printf("size char is %lu\n",sizeof(char));
	printf("size unsigned char is %ld\n",sizeof(unsigned char));	
	printf("size short is %lu\n",sizeof(short));
	printf("size short int is %lu\n",sizeof(short int));
	printf("size unsigned short int is %lu\n",sizeof(unsigned short int));				
	printf("size signed short int is %lu\n",sizeof(signed short int));			
	printf("size signed short is %lu\n",sizeof(signed short));
	printf("size unsigned short is %lu\n",sizeof(unsigned short));	
	printf("size int is %lu\n",sizeof(int));
	printf("size signed int is %lu\n",sizeof(signed int));
	printf("size unsigned int is %lu\n",sizeof(unsigned int));
	printf("size float is %lu\n",sizeof(float));
	printf("size long int is %lu\n",sizeof(long int));
	printf("size signed long int is %lu\n",sizeof(signed long int));	
	printf("size double is %lu\n",sizeof(double));
	printf("size long is %lu\n",sizeof(long));
	printf("size size_t is %lu\n",sizeof(size_t));				
	printf("size signed long  is %lu\n",sizeof(signed long));

}




































/*--------------------------------------------------------

void DataType()
{
 	char *DataTypes[] = {"char","signed char","unsigned char","short",
 	"signed short","unsigned short","int","signed int","unsigned int",
 	"short int","signed short int","unsigned short int","long int",
 	"signed long int","unsigned long int","float","double","long double"};
 	
 	size_t MemorySize[] = {sizof(char),sizof(signed char),
 	sizof(unsigned char),sizof(short),sizof(signed short),sizof(unsigned short,
 	sizof(int),sizof(signed int),sizof(unsigned int),sizof(short int),
 	sizof(signed short int),sizof(unsigned short int),sizof(long int),
 	sizof(signed long int),sizof(unsigned long int),sizof(float),
 	sizof(double),sizof(long double)};
 	 
 	int i = 0;
 	
 	for( ; i < 18; i++)
 	{
 		printf("the size of %s is %lu byte\n", DataTypes[i], MemorySize[i]);
 	}
 	
 	printf("\n%lu", sizeof(DataTypes));
 	 
}

*/





