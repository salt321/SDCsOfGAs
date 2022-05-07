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


    int val[] = { 70, 20 , 30 , 100 , 50 ,10, 70, 90, 130, 150 };
    int weight[] = { 4, 2 , 1 , 6 , 2 , 20, 3, 5, 7, 8};
    int capacity = 5;
    int index = sizeof(val) / sizeof(val[0]);
    printf("%d", knapSack(capacity, weight, val, index));
    return 0;
}
