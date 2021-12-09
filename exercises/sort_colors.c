#include <stdio.h>
#include <stdlib.h>/*malloc,free*/

/*------------------------------------*/

int max_of_array(int arr[], int size);
void sort_colors(int arr[], int size);
void print_array(int arr[], int size);

/*------------------------------------*/

int main()
{
    int array[7] = {0,1,0,3,2,1,1};
    sort_colors(array,7);
    print_array(array,7);
      
   return 0;
}

/*------------------------------------*/

int max_of_array(int arr[], int size)
{
    int max = 0, i = 0;
    for(; i < size; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
void sort_colors(int arr[], int size)
{
    int n = max_of_array(arr, size) + 1;
    int *ptr = (int*) malloc(n * sizeof(int));
    int i = 0, index = 0, count = 0;
    
    for(; i < size; i++)
    {
        ptr[arr[i]]++;
    }
    
    i = 0;
    
    for(; i <= n; i++)
    {
        count = ptr[i];
        
        while(count)
        {
            arr[index] = i;
            count --;
            index ++;
        }
    }
    free(ptr);
}

void print_array(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d,", arr[i]);
    }
    
}

