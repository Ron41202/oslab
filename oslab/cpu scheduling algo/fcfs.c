#include<stdio.h>

struct s{
    int pid;
    int at;
    int bt;
    int ct,tat,wt,rt;
    int start_time;
};
int max(int x,int y)
{
    return x>y?x:y;
}
void swap(struct s *a,struct s *b)
{
    struct s temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void sort(struct s *arr,int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j].at>arr[j+1].at)
            {
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
int main()
{
    int n;
    printf("enter the no. of processes: ");
    scanf("%d",&n);
    struct s arr[n];

    printf("enter the arrival time and burst time of each process:\n");
    for(int i=0;i<n;i++)
    {
        arr[i].pid=i+1;
        scanf("%d %d",&arr[i].at,&arr[i].bt);
    }

    sort(arr,n);
    float sum_tat=0,sum_wt=0,sum_rt=0;
    float idle_time=0;
    for(int i=0;i<n;i++)
    {
        arr[i].start_time = (i==0)?arr[i].at:max(arr[i-1].ct , arr[i].at);
        arr[i].ct = arr[i].start_time + arr[i].bt ; 
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        arr[i].rt = arr[i].wt;

        sum_tat += arr[i].tat;
        sum_wt += arr[i].wt;
        sum_rt += arr[i].rt;
        idle_time += (i==0)?0:(arr[i].start_time -arr[i-1].ct);
    }
    printf("pid\tat\tbt\t ct\t tat\t wt\t rt\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n",arr[i].pid,arr[i].at,arr[i].bt,arr[i].ct,arr[i].tat,arr[i].wt,arr[i].rt);
    }
    int total_time=arr[n-1].ct-arr[0].start_time;
    printf("average tat= %f    average wt=%f   average rt=%f   throughput =%f\n",sum_tat/n,sum_wt/n,sum_rt/n,n/(float)total_time);

    printf("utilization % = %f", (total_time - idle_time)/total_time*100);
}