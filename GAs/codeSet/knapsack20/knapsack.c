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

    int val[] = {10,20,30,300,40,60,70,80,90,150,30,50,30,100,250,150,70,90,10,60 };
    int weight[] = {3,2,3,4,5,6,7,8,9,8,20,30,19,60,7,45,32,8,12,19 };
    int capacity = 5;
    int index = sizeof(val) / sizeof(val[0]);
    printf("%d", knapSack(capacity, weight, val, index));
    return 0;
}
