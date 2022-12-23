#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct s{
    int pid,at,bt,ct,tat,wt,rt,start_time;
};
int max(int a,int b)
{
    return a>b?a:b;
}
void swap(struct s a,struct s b)
{
    struct s temp=a;
    a=b;
    b=temp;
}
void sort(int n,struct s arr[])
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j].at>arr[j+1].at)
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
int min(int x, int y)
{
    return x>y?y:x;
}
int main()
{
    int n;
    scanf("%d",&n);
    struct s arr[n];
    int sum_tat=0,sum_wt=0,sum_rt=0,current_time=0,completed=0,index=0,idle_time=0,tq;
    bool visited[100]={false},is_first=true;
    int bt_remaining[n],q[100];
    int f=0,r=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&arr[i].at,&arr[i].bt);
        arr[i].pid=i+1;
    }
    scanf("%d",&tq);
    sort(n,arr);
    for(int i=0;i<n;i++)
    {
        bt_remaining[i]=arr[i].bt;
    }
    q[f]=0;
    visited[0]=true;
    while(completed!=n)
    {
        index=q[f];
        f++;
        
        if(bt_remaining[index]==arr[index].bt)
        {
            arr[index].start_time=max(current_time,arr[index].at);
            idle_time += (is_first==true)?0:(arr[index].start_time - current_time);
            current_time=arr[index].start_time;
            is_first=false;
        }
        if(bt_remaining[index]-tq>0)
        {
            bt_remaining[index] -= tq;
            current_time += tq;
        }
        else
        {
            current_time += bt_remaining[index];
            bt_remaining[index]=0;

            arr[index].ct=current_time;
            arr[index].tat=arr[index].ct-arr[index].at;
            arr[index].wt=arr[index].tat - arr[index].bt;
            arr[index].rt = arr[index].start_time - arr[index].at;

            sum_tat +=arr[index].tat;
            sum_wt +=arr[index].wt;
            sum_rt +=arr[index].rt;

            completed++;
        }

        for (int i = 1; i < n; i++)
        {
            if(bt_remaining[i]>0 && visited[i]==false && arr[i].at<=current_time)
            {
                q[++r]=i;
                visited[i]=true;
            }
        }

        if(bt_remaining[index]>0)
        {
            q[++r]=index;
        }
        if(f>r)
        {
            for(int i=1;i<n;i++)
            {
                if(bt_remaining[i]>0 )
                {
                    q[++r]=i;
                    visited[i]=true;
                    break;
                }
            }
        }
    }
    printf("pid\tat\tbt\tct\ttat\twt\trt\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",arr[i].pid,arr[i].at,arr[i].bt,arr[i].ct,arr[i].tat,arr[i].wt,arr[i].rt);
    }
    int max_ct=INT_MIN;
    int min_st=INT_MAX;
    for(int i=0;i<n;i++)
    {
        max_ct=max(max_ct,arr[i].ct);
        min_st=min(min_st,arr[i].start_time);
    }
    int total_time=max_ct-min_st;
    float cpu_utilization=(float)(total_time - idle_time)/total_time*100;
    
    printf("average tat= %f    average wt=%f   average rt=%f   throughput =%f\n",(float)sum_tat/n,(float)sum_wt/n,(float)sum_rt/n,n/(float)total_time);
    printf("cpu utilization=%f",cpu_utilization);
}