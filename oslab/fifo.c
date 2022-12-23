#include<stdio.h>

typedef struct page{
    int valid;
}ps;
int ispagefound(ps p[],int page)
{
    if(p[page].valid==1)
        return 1;
    return 0;
}
void update(ps p[],int page,int value)
{
    p[page].valid= value;
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
    }
    int current=0,flag=1,page_fault=0;

    for(int i=0;i<no_of_ref;i++)
    {
        if(!ispagefound(p,ref_string[i]))
        {
            page_fault++;
            if(flag==1)
            {
                update(p,ref_string[i],1);
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
                update(p,frames[current],0);
                frames[current]=ref_string[i];
                current=(current+1)%no_of_frames;
                update(p,ref_string[i],1);
            }
        }
    }
    printf("%d",page_fault);
    return 0;
}