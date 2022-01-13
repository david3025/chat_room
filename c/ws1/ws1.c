

#include <stdio.h>


/*-------------hello-------------------*/

void print_hello()
{
	char hello[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6F, 0x20,
			 0x77, 0x6F, 0x72, 0x6c, 0x64, 0X21, 0x22};

	printf("\n%s\n\n",hello);

}


/*------------ten_pow------------------*/

double ten_pow(int n)
{
	double res = 1 ,base = 10;
	if (n < 0)
	{
	base = 1/10;
	n = -n;
	}
	while(n>0)
	{
	res = res*base;
	--n;
	}
	return res;
}

void test_ten_pow(int value,int expect){

	if(ten_pow(value) == expect)
	{
	printf("ten_pow >> sucsess\n");
	}
	else
	{
	printf("ten_pow >> failure\n");
	}
}

void super_test_ten_pow()
{
	test_ten_pow(2,100);
	test_ten_pow(-5,0.00001);
	test_ten_pow(0,1);
	printf("\n");
}

/*-----------flips--------------*/

int flips_num(int number)
{
	int res = 0;
	while (number != 0)
	{
		res = res * 10 + number % 10;
		number /= 10;
	}
	return res;

}


void test_flips_num(int value ,int expect)
{
	if (flips_num(value) == expect)
	{
		printf("flip >> sucsess\n");
	}
	else
	{
		printf("flip >> failure\n");
	}
}

void super_test_flips_num()
{
	test_flips_num(-1234,-4321);
	test_flips_num(234,432);
	test_flips_num(1234,4321);
	printf("\n");
}


/*-------------swap-----------------*/


void my_swap(int *x,int *y){

	int temp = *x;
	*x = *y;
	*y = temp;
}


void test_my_swap(int x, int y){
	
	
	int old_x = x, old_y = y;
	my_swap(&x, &y);
	if((x == old_y) && (y == old_x))
	{
	printf("swap >> success\n");
	}
	else
	{
	printf("swap >> failure\n");
	}
}






int main() 
{
	
	printf("\n----------test!-------\n\n");
	print_hello();
	super_test_ten_pow();
	super_test_flips_num();
	test_my_swap(4,6);

	return 0;
}


