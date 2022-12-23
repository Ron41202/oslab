#include<stdio.h>
#include<math.h>
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
    int totSeekTime=0;
    for(int i=0;i<n;i++)
    {
        totSeekTime = totSeekTime + fabs(t[i] - curHead);
        curHead = t[i];
    }

    printf("\ntotal seek time =%d\n",totSeekTime);
    return 0;
}