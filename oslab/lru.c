#include<stdio.h>
#include<limits.h>
typedef struct page{
    int ind;
    int last_used;
    int valid;
}ps;
int ispagefound(ps p[],int page)
{
    if(p[page].valid==1)
        return 1;
    return 0;
}
void update(ps p[],int page,int value,int use,int index)
{
    p[page].valid= value;
    p[page].last_used = use;
    p[page].ind = index;
}
int search(ps p[])
{
    int min=INT_MAX;
    int index;
    for(int i=0;i<20;i++)
    {
        if(p[i].valid==1)
        {
            if(p[i].last_used<min)
            {
                min=p[i].last_used;
                index=p[i].ind;
            }
        }
    }
    return index;
}
int main()
{
    int no_of_ref;
    scanf("%d",&no_of_ref);
    int ref_string[no_of_ref];
    for(int i=0;i<no_of_ref;i++)
    {
        scanf("%d",&ref_string[i]);
    }
    int no_of_frames;
    scanf("%d",&no_of_frames);
    int frames[no_of_frames];
    for(int i=0;i<no_of_frames;i++)
    {
        frames[i]=-1;
    }
    struct page p[20];
    for(int i=0;i<20;i++)
    {
        p[i].valid=0;
        //p[i].last_used=INT_MAX;
    }
    int current=0,flag=1,page_fault=0;

    for(int i=0;i<no_of_ref;i++)
    {
        if(!ispagefound(p,ref_string[i]))
        {
            page_fault++;
            if(flag==1)
            {
                update(p,ref_string[i],1,i,current);
                frames[current]=ref_string[i];
                current++;
                if(current==no_of_frames)
                {
                    current=0;
                    flag=0;
                }
            }
            else
            {
                int lru_no=search(p);
                update(p,frames[lru_no],0,i,lru_no);
                frames[lru_no]=ref_string[i];
               // current=(current+1)%no_of_frames;
                update(p,ref_string[i],1,i,lru_no);
            }
        }
        else
            p[ref_string[i]].last_used = i;
    }
    printf("%d",page_fault);
    return 0;
}