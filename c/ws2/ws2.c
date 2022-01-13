# include <stdio.h> /* printf */
# include <stdlib.h> /* malloc */

void my_int_swap(int *x,int *y);
void swap_size_t(size_t *x ,size_t *y);
void swap_ptr_size_t(size_t **x ,size_t **y);
void swap_ptr_by_swap_size_t(size_t **x ,size_t **y);
void test_swap_ptr_by_swap_size_t();
void test_my_int_swap(int x, int y);
void test_swap_size_t(size_t x ,size_t y) ;
void test_swap_ptr_size_t();

int *copy_array(int *array ,int size);
int test_copy_array(int *array ,int size); 
void super_test_copy_array();
int * copy_array_index(int arr[], int size);

size_t Strlen(char *ptr);
void test_Strlen(char *ptr ,size_t expected);
void super_test_Strlen();

int Strcmp(const char  *s1 ,const char  *s2);
void test_Strcmp(const char  *s1 ,const char  *s2 , int expected);
void super_test_Strcmp();

void print_arr(int *arr ,int size);





int main()
{	
	/*
	super_test_Strlen();
	super_test_Strcmp();
	super_test_copy_array();
	test_swap_ptr_size_t();
	*/
	test_swap_ptr_by_swap_size_t();
	return 0;   
}

/*-----------------swap----------------------*/

void my_int_swap(int *x, int *y)
{	
	int temp = *x;
	
	*x = *y;
	*y = temp;
}

void swap_size_t(size_t *x ,size_t *y)  
{	
	size_t temp = *x;
	
	*x = *y;
	*y = temp;
}

void swap_ptr_size_t(size_t **x ,size_t **y)  
{	
	size_t temp = **x;
	
	**x = **y;
	**y = temp;
}


void swap_ptr_by_swap_size_t(size_t **x ,size_t **y) 
{
	 swap_size_t(*x, *y);
}

void test_swap_ptr_by_swap_size_t()
{
	size_t a = 5, b = 6;
	size_t *x = &a, *y = &b;
	size_t **A = &x, **B = &y;
	size_t OLD_a = a, OLD_b = b;
	
	swap_ptr_by_swap_size_t(A, B);
	
	if ( b == OLD_a && a == OLD_b )
	{
	printf("swap >> success\n");
	}
	else
	{
	printf("swap >> failure\n");
	}
	
} 

void test_my_int_swap(int x, int y){
	
	
	int old_x = x, old_y = y;
	my_int_swap(&x, &y);
	if((x == old_y) && (y == old_x))
	{
	printf("swap >> success\n");
	}
	else
	{
	printf("swap >> failure\n");
	}
}

void test_swap_size_t(size_t x ,size_t y) 
{	
	size_t old_x = x ,old_y = y;
	
	swap_size_t(&x, &y);
	
	if((x == old_y) && (y == old_x))
	{
		printf("swap >> success\n");
	}
	else
	{
		printf("swap >> failure\n");
	}
}

void test_swap_ptr_size_t()
{	
	size_t x = 0, y = 0;
	size_t *p1, *p2;
	
	printf ("\n");
	
	x = 1;
	y = 2;
	p1 = &x;
	p2 = &y;
	
	swap_ptr_size_t(&p1, &p2);
	
	printf ("success\n");
}

/*---------------------strlen--------------------------*/

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

void test_Strlen(char  *ptr ,size_t  expected)

{	
	if(Strlen(ptr) == expected)
	{	
		printf("succeeded\n");
	}
	else
	{	
		printf("fails\n");
	}
}

void super_test_Strlen()
{	
	char *a; 

	test_Strlen(a="hello" ,5);
	test_Strlen(a="" ,0);
	test_Strlen(a="\0" ,0);
	test_Strlen(a="1234" ,4);
	test_Strlen(a="test my strlen" ,14);
}

/*---------------------strcmp----------------------------*/

int Strcmp(const char *s1, const char *s2){
   
    for (;*s1 && *s2 && (*s1 == *s2); s1++, s2++)
    {
    	/* do nothing*/
    }
    
    return *s1 - *s2;
}

void test_Strcmp(const char *s1, const char *s2, int expected)
{
	if(Strcmp(s1, s2) == expected || ( Strcmp(s1, s2) * expected > 0 ) )
	
	{	
		printf("succeeded\n");
	}
	else
	{
		printf("fails\n");
	}
}

void super_test_Strcmp()
{	
	char *ptr1, *ptr2;	
	test_Strcmp(ptr1 = "" ,ptr2 = "" , 0);
	test_Strcmp(ptr1 = "abcd" ,ptr2 = "abcd" , 0);
	test_Strcmp(ptr1 = "abcd" ,ptr2 = "ABCD" , 2);
	test_Strcmp(ptr1 = "\0" ,ptr2 = "a" , -2);
	test_Strcmp(ptr1 = "A" ,ptr2 = "ABCD" , -2);
	test_Strcmp(ptr1 = "121" ,ptr2 = "345" , -2);
	test_Strcmp(ptr1 = "0" ,ptr2 = "0" , 0);
}

/*---------------copy_array------------------------*/

int * copy_array_index(int arr[], int size)
{
	
	int *new_arr = (int*)malloc(size* sizeof(int));
	int i;
	for (i = 0; i < size; i++)
	{
		new_arr[i] = arr[i];
	}
	
	return new_arr;
}

int test_copy_array(int *array ,int size) 
{	
	int *new_arr = copy_array_index(array ,size);
	int result = 1;
	int index = 0;
	
	while (index != size )
	{	
		if(new_arr[index] != array[index])
		{
			result = 0;
			
			break ;
		}
		
		index++;
	}
	
	free(new_arr);
	new_arr = NULL;

	return result;
}

void super_test_copy_array()
{	
	int arr[] = {1,2,3,4,5,6};
	int test = test_copy_array(arr ,6);
	
	if(test)
	{	
		printf("succeeded\n");
	}
	else
	{	
		printf("fails\n");
	}
	
}

void print_arr(int *arr ,int size)
{	
	while(size)
	{	
		printf("%d," ,*arr);
		arr++;
		size--;
	}
	
	printf("\n");
}









