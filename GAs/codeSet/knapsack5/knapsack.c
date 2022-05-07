#include <stdio.h>


int max(int a, int b) { 
	if (a> b)
		return a;
	else
		return b;
  }
int knapSack(int capacity, int weight[], int val[], int index)
{
    if (index == 0 || capacity == 0)// base case
        return 0;
  
    if (weight[index - 1] > capacity)//out weight
        return knapSack(capacity, weight, val, index - 1);

    else//include and exclude
        return max(
            val[index - 1]
                + knapSack(capacity - weight[index - 1], weight, val, index - 1),
            	knapSack(capacity, weight, val, index - 1));
}
  

int main()
{
    int val[] = { 4, 2, 1, 10, 1 };
    int weight[] = { 12, 2, 1, 4, 2 };
    int capacity = 5;
    int index = sizeof(val) / sizeof(val[0]);
    printf("%d", knapSack(capacity, weight, val, index));
    return 0;
}
