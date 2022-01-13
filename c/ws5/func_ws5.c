# include <stdio.h>  /* printf ,fseek,fopen,fclose,fread,remove,perror */
#include <string.h> /*strncmp,strlen,remove*/
#include <stdlib.h>/* exit*/
#include "ws5.h"


void InitializesTheStructure(Functions functions  [])
{	
	int i = 0;
	
	for (; i < NUMOPFUNCTIONS; i++)
	{
		functions [i].comp = Compare;
	}
	
	functions [0].str = "-remove";
	functions [1].str = "-count";
	functions [2].str = "-exit";
	functions [3].str = "<";
	functions [4].str = "";

	functions [0].func = RemoveFile;
	functions [1].func = CountLines;
	functions [2].func = Exit;
	functions [3].func = WriteFromStart;
	functions [4].func = WriteTfromEnd;
}





/*-----------------------------------------------------*/
void RemoveFile(const char* filename, const char* str)
{
	int ret;
	FILE *fp;
	fp = fopen(filename, "w");
	fclose(fp);
	
	ret = remove(filename);
	
	if (ret == 0) 
	{
      printf("File deleted successfully");
   	} 
   	else 
   	{
      printf("Error: unable to delete the file");
   	}
	
	(void)str;
}

void CountLines(const char* filename, const char* str)
{
		size_t count = 0;
		char null_buf [MAXSTR] = "";
		FILE *fd = fopen(filename, "r");
		
		if ( fd == NULL ) 
		{
			printf("0");
		}	
		
		while (NULL != fgets(null_buf, MAXSTR, fd))
		{
			count++;
		}
		
		printf("%ld", count);
		(void)str;
}

void Exit(const char* filename, const char* str)
{
		(void)filename;
		(void)str;
		exit(0);
}

void WriteFromStart(const char* filename, const char* str)
{	
	char *buffer = 0;
	long length;
	int checking_errors;
	 
	FILE *f = fopen (filename, "rb");
	ErrorOpenFile(f);

	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  length = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  buffer = (char*)malloc(length*sizeof(char));
	  
	  if (buffer)
	  {
		fread (buffer, 1, length, f);
	  }
	  else
	  {
	  	perror("Error allocating memory ");
	  }
	  
	}
	
	remove(filename);
	f = fopen (filename, "w");
	fputs(str+1, f);
	fputs(buffer, f);
	checking_errors = fclose(f);
	
	if(checking_errors == EOF)
	{
		perror("Error closing file \n");
	}
	
	free(buffer);
	buffer = NULL;
		
}

void WriteTfromEnd(const char* filename, const char* str)
{
	FILE *fd = NULL;
	
	fd = fopen(filename, "a");
	ErrorOpenFile(fd);
	fputs(str, fd);
	fclose(fd);
}
/*-----------------------------------------------------*/
void UserSelection(char *filename, Functions functions [])
{
	while (1)
	{
		char string[MAXSTR] = "";	
				
		fgets(string, MAXSTR, stdin);
		SelectFunction(filename, string, functions );
	}
}

void SelectFunction(const char* filename, const char* str, Functions functions [])
{
	int i = 0;
	
	for (; i < NUMOPFUNCTIONS; i++)
	{	
		if (functions [i].comp(str, functions [i].str))
		{
			 functions [i].func(filename, str);
			
			 break;
		}
	}
}


int Compare(const char* input, const char* expected)
{
	int result = 1;
	size_t len = strlen(expected);
	
	if(strncmp(expected, input, len))
	{
		result = 0;
	}
	
	return result;
}

void ErrorOpenFile(void *fp)
{
	if ( fp == NULL ) 
	{
    	perror ("Error opening file ");
      	exit(0);
    }
}


