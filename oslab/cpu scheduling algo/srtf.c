#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct s{
    int pid,at,bt,ct,tat,wt,rt,start_time;
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
        scanf("%d%d",&arr[i].at,&arr[i].bt);
        arr[i].pid=i+1;
        is_remaining[i]=arr[i].bt;
    }

    while(completed!=n)
    {
        int min_ind=-1;
        int min=INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(arr[i].at<=current_time && is_completed[i]==false)
            {
                if(is_remaining[i]<min)
                {
                    min=is_remaining[i];
                    min_ind=i;
                }
                if(is_remaining[i]==min)
                {
                    if(arr[i].at<arr[min_ind].at)
                    {
                        min=is_remaining[i];
                        min_ind=i;
                    }
                }
            }
        }

        if(min_ind==-1)
        {
            current_time++;
        }
        else
        {
            if(is_remaining[min_ind]==arr[min_ind].bt)
            {
                arr[min_ind].start_time = current_time;
                idle_time += (is_first==true)?0:(arr[min_ind].start_time - prev);  
                is_first=false;  
            }
            is_remaining[min_ind] --;
            current_time++;
            prev=current_time;
            if(is_remaining[min_ind]==0)
            {
                arr[min_ind].ct=current_time;
                arr[min_ind].tat=arr[min_ind].ct-arr[min_ind].at;
                arr[min_ind].wt=arr[min_ind].tat-arr[min_ind].bt;
                arr[min_ind].rt=arr[min_ind].start_time-arr[min_ind].at;

                sum_tat += arr[min_ind].tat;
                sum_wt +=arr[min_ind].wt;
                sum_rt +=arr[min_ind].rt;
                is_completed[min_ind]=true;
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