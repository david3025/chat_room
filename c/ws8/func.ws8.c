#include <stdio.h> /* printf,sprintf */
#include <string.h> /* malloc, free */ 
#include <stdlib.h> /* strcpy strct */
#include "ws8.h"


void AddInt(object *objs, int add);
void PrintInt(object *objs);
void FreeInt(object *objs);

void AddFloat(object *objs, int number);
void PrintFloat(object *objs);
void FreeFloat(object *objs);

void AddString(object *objs, int add);
void PrintString(object *objs);
void FreeString(object *objs);


void AddToAllobjects(object objs[], int number)
{
	int i = 0;
	
	for (i = 0; i < SUM_OF_OBJECT; i++)
	{
		objs[i].Add(objs + i, number);
	}
}

void PrintAllobjects(object *objs)
{
	int i = 0;
	
	for (i = 0; i < SUM_OF_OBJECT; i++)
	{
		objs[i].Print(&objs[i]);
	}
	
	printf("\n");
}

void FreeAllobjects(object *objs)
{
	int i = 0;
	
	for (i = 0; i < SUM_OF_OBJECT; i++)
	{
		objs[i].Free(&objs[i]);
	}
}

/*----------------------------------------------*/

void CreateIntobject(object *objs, int input)
{
	(*objs).data = (void *)(size_t)input;
	(*objs).Print = PrintInt;
	(*objs).Add = AddInt;
	(*objs).Free = FreeInt;
}

void AddInt(object *objs, int add)
{
	*(int *)(&(*objs).data) += add;
}

void PrintInt(object *objs)
{
	printf("%d,", (int)(long)((*objs).data));
}

void FreeInt(object *objs)
{
	(void) objs;
}

/*----------------------------*/

void CreateFloatObject(object *objs, float input)
{
	(*objs).data = (void *)(size_t)input;
	(*objs).Add = AddFloat;
	(*objs).Print = PrintFloat;
	(*objs).Free = FreeFloat;
}

void AddFloat(object *objs, int number)  /*?*/
{
	*((float *)(&(*objs).data)) += (float)number;
}

void PrintFloat(object *objs)
{
	printf("%f,", *((float *)(&(*objs).data)));
}

void FreeFloat(object *objs)
{
	(void) objs;
}

/*----------------------------*/
void CreateStringobject(object *objs, char *str)
{
	(*objs).data = malloc(sizeof(char) * strlen(str) + 1);
	strcpy((char *)((*objs).data), str);
	(*objs).Add = AddString;
	(*objs).Print = PrintString;
	(*objs).Free = FreeString;
}

void AddString(object *objs, int add)
{
	char *duplication, text[10];
	size_t string_len = strlen((*objs).data);
	size_t text_len;
	
	sprintf(text, "%d", add);
	text_len = strlen(text);
	
	duplication = (char *)malloc( (string_len + text_len + 1) * sizeof(char) );
	
	strcpy(duplication, (char *)(*objs).data);
	strncat(duplication, text, strlen(text));

	free((*objs).data);
	
	(*objs).data = duplication;
}

void PrintString(object *objs)
{
	printf("%s,", (char *)(*objs).data);
}

void FreeString(object *objs)
{
	free((*objs).data);
}

/*----------------------------*/


