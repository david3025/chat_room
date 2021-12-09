#include <stdio.h>
#include <stdlib.h>/*malloc*/

int* plusOne(int* digits, int digitsSize, int* returnSize);
void print_array(int arr[], int size);

int main(){
    int digits[] = {1,2,3}, *new;
    int* returnSize;
    new = plusOne(digits,3,returnSize);
    print_array(new,*returnSize);
    return 0;
}
int* plusOne(int* digits, int digitsSize, int* returnSize) 
{
    int carry = 1, i = digitsSize;
    int* ret = (int*)malloc(sizeof(int)*(digitsSize+1));
    while (i > 0) {
        ret[i] = (digits[i-1]+carry)%10;
        carry = (digits[i-1]+carry)/10;
        i--;
    }
    if (!ret[1]) 
    { 
        // size increased 1, set the first digit
        ret[0] = 1;
        *returnSize = digitsSize+1;
        return ret;
    }
    else 
    {
        *returnSize = digitsSize;
        return ret+1;
    }
}

void print_array(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d,", arr[i]);
    }
}

