#include<stdio.h>
#include<math.h>
void swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
      for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j],& arr[j + 1]);
}
int main()
{
    int n;
    scanf("%d",&n);
    int t[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&t[i]);
    }
    int curHead;
    scanf("%d",&curHead);
    bubbleSort(t,n);
    int totSeekTime= (t[n-1] - t[0]) + fabs(curHead - t[0]);
    printf("total seek time = %d",totSeekTime);
    return 0;
}