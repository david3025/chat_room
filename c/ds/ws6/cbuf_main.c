#include <stdio.h>/*print*/

#include "cbuf.h"

void TestCBWrite();
void TestCBRead();
char CBRemove(cbuff_t *cbuff);
void CBPrint(cbuff_t *cbuff);
void PrintTest(int result);

int main()
{
	
	TestCBRead();
	TestCBWrite();

	return 0;
}

void TestCBWrite()
{
	int result = 1;

	cbuff_t *cb1 = CBCreate(7);
	cbuff_t *cb2 = CBCreate(4);
	cbuff_t *cb3 = CBCreate(7);
	
	result *= (CBWrite(cb1,"12345",3) == 3);
	result *= (CBWrite(cb2,"12345",6) == 4);
	result *= (CBWrite(cb3,"12345",5) == 5);
	
	result *= (CBFreeSpace(cb1) == 4);
	result *= (CBFreeSpace(cb2) == 0);
	result *= (CBFreeSpace(cb3) == 2);
	
	result *= (CBWrite(cb2,"12345",6) == 0);
	
	result *= (CBBufsiz(cb1) == CBBufsiz(cb3));
	result *= (CBBufsiz(cb2) == 4);
	
	result *= (CBRemove(cb2) == '1');
	result *= (CBFreeSpace(cb2) == 1);
	
	CBDestroy(cb1);
	CBDestroy(cb2);
	CBDestroy(cb3);
	
	PrintTest(result);
	
}

void TestCBRead()
{
	int result = 1;
	cbuff_t *cb1 = CBCreate(4), *cb2 = CBCreate(4);
	char buf1[5], buf2[5];
	
	CBWrite(cb1,"1234",4);
	CBWrite(cb2,"1234",4);

	result *= (CBRead(cb1, buf1, 4) == 4);/*____*/
	result *= (CBWrite(cb1,buf1,4) == 4);/*1234*/
	
	
	result *= (CBRead(cb2, buf2, 3) == 3);/*__4*/
	
	CBRemove(cb1);/*_234*/
	result *= (CBWrite(cb1,buf2 + 1,4) == 1);
	result *= (CBWrite(cb1,"end",5) == 0);
	
	CBDestroy(cb1);
	CBDestroy(cb2);
	
	PrintTest(result);	
}

void PrintTest(int result)
{
	if(result)
	{
		printf("Success\n");		
	}
	else
	{
		printf("Fails\n");				
	}
}

