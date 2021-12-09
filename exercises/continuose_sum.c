#include <stdio.h>
#include <limits.h>/*INT_MIN*/

int max_continuous_sub(int arr[], int size);

int main()
{
    int array[6] = {3,-2,3,-4,1};
    int result = max_continuous_sub(array, 6);
    printf("%d",result);
    return 0;
}

int max_continuous_sub(int arr[], int size)
{
    int max = INT_MIN, total = arr[0] , i = 1;
    
    for(; i < size; i++)
    {
        if(arr[i] > total & total < 0)
        {
            total = 0;
        }
        
        total += arr[i];
        
        if(total > max)
        {
            max = total;
        }
    }
    return max;
}

