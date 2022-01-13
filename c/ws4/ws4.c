#include <stdio.h>/* printf, scanf*/
#include <stdlib.h>/* system, exit */

#define ESC 27
#define CHAR 256

void Empty();
void FuncT();
void FuncESC();
void TorAIF();
void TorAswitch();
void arr();


int main() 
{	
	TorAswitch();
	
	return 0;
}

void Empty()
{

}

void FuncT()
{
	printf("T pressed\n");	
}

void FuncA()
{
	printf("A pressed\n");	
}

void FuncESC()
{
	system("stty icanon echo");
	
	exit(0);
	
}

void TorAIF()
{
	unsigned char key = 0;
	
	system("stty -icanon -echo");
	
	while(ESC != key)
	{	
		scanf("%c", &key);
		
		if('T' == key)
		{
			printf("T pressed\n");
		}
		
		if('A' == key)
		{
			printf("A pressed\n");
		}
	}
	
	system("stty icanon echo");
	exit(0);
}

void TorAswitch()
{
	system("stty -icanon -echo");
	
	while(1)
	{	
		unsigned char key = scanf("%c", &key);
		
		scanf("%c", &key);
		
		switch (key)
	   {
		   case 'T': printf("T pressed\n");
		   			break;
				   
		   case 'A': printf("A pressed\n");
					break;
				    
		   case ESC: system("stty icanon echo");
		  			exit(0);
		  default:
		  			break; 
	   }
	 }
}

void arr()
{
	int i = 0;
	void (*arr_ptr_fun[CHAR])();
	
	for( ; i < CHAR; i++)
	{
		arr_ptr_fun[i] = Empty;
	}
	
	arr_ptr_fun['T'] = FuncT;
	arr_ptr_fun['A'] = FuncA;
	arr_ptr_fun[ESC] = FuncESC;
	
	system("stty -icanon -echo");
	
	while(1)
	{	
		unsigned char key = '\0'; 
		
		scanf("%c", &key); 
		arr_ptr_fun[key]();
	}
}



