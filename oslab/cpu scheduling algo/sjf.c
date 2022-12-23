#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
struct s{
    int pid, at,bt,ct,tat,wt,rt,start_time;
};
int max(int x,int  y)
{
    return x>y?x:y;
}
int min(int x, int y)
{
    return x>y?y:x;
}
int main(){
    int n;
    scanf("%d",&n);
    struct s arr[n];
    int total_time=0,current_time=0,completed=0,idle_time=0;
    float sum_tat=0,sum_wt=0,sum_rt=0;
    bool is_completed[100]={false};
    bool is_first=true;
    int prev=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&arr[i].at,&arr[i].bt);
        arr[i].pid=i+1;
    }

    while(completed!=n)
    {
        int min_ind=-1;
        int min=INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(arr[i].at<=current_time && is_completed[i]==false)
            {
                if(arr[i].bt<min){
                    min_ind=i;
                    min=arr[i].bt;
                }
                if(arr[i].bt==min){
                    if(arr[i].at<arr[min_ind].at)
                    {
                        min_ind=i;
                        min=arr[i].bt;
                    }
                }
            }
            
        }

        if(min_ind==-1)
        {
            current_time++;
        }
        else{
            arr[min_ind].start_time = current_time;
            arr[min_ind].ct = arr[min_ind].start_time + arr[min_ind].bt;
            arr[min_ind].tat = arr[min_ind].ct - arr[min_ind].at;
            arr[min_ind].wt = arr[min_ind].tat - arr[min_ind].bt;
            arr[min_ind].rt = arr[min_ind].wt;

            sum_tat+=arr[min_ind].tat;
            sum_wt +=arr[min_ind].wt;
            sum_rt +=arr[min_ind].rt;
            idle_time += (is_first==true)?0:(arr[min_ind].start_time- arr[prev].ct);
            
            is_first=false;
            prev=min_ind;
            current_time=arr[min_ind].ct;
            completed++;
            is_completed[min_ind]=true;
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
    total_time=max_ct-min_st;
    float cpu_utilization=(float)(total_time - idle_time)/total_time*100;
    
    printf("average tat= %f    average wt=%f   average rt=%f   throughput =%f\n",sum_tat/n,sum_wt/n,sum_rt/n,n/(float)total_time);
    printf("cpu utilization=%f %",cpu_utilization);
}