#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
struct s{
    int pid,at,bt,ct,tat,wt,rt,start_time,priority;
};
int max(int x,int  y)
{
    return x>y?x:y;
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
    int is_remaining[n],current_time=0,sum_tat=0,sum_wt=0,sum_rt=0,prev=0,completed=0,idle_time=0;
    bool is_completed[100]={false},is_first=true;
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",&arr[i].at,&arr[i].bt,&arr[i].priority);
        arr[i].pid=i+1;
        is_remaining[i]=arr[i].bt;
    }

    while(completed!=n)
    {
        int ind=-1;
        int max=INT_MIN;
        for(int i=0;i<n;i++)
        {
            if(arr[i].at<=current_time && is_completed[i]==false)
            {
                if(arr[i].priority>max)
                {
                    max=arr[i].priority;
                    ind=i;
                }
                if(arr[i].priority==max)
                {
                    if(arr[i].at<arr[ind].at)
                    {
                        max=arr[i].priority;
                        ind=i;
                    }
                }
            }
        }

        if(ind==-1)
        {
            current_time++;
        }
        else
        {
            if(is_remaining[ind]==arr[ind].bt)
            {
                arr[ind].start_time = current_time;
                idle_time += (is_first==true)?0:(arr[ind].start_time - prev);  
                is_first=false;  
            }
            is_remaining[ind] --;
            current_time++;
            prev=current_time;
            if(is_remaining[ind]==0)
            {
                arr[ind].ct=current_time;
                arr[ind].tat=arr[ind].ct-arr[ind].at;
                arr[ind].wt=arr[ind].tat-arr[ind].bt;
                arr[ind].rt=arr[ind].start_time-arr[ind].at;

                sum_tat += arr[ind].tat;
                sum_wt +=arr[ind].wt;
                sum_rt +=arr[ind].rt;
                is_completed[ind]=true;
                completed++;
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