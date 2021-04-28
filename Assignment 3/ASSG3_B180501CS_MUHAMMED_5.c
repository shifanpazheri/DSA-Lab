#include<stdio.h>

void linearinsert(int a[],int m,int k)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+i)%m;
        if(a[j]==-999)
        {
            a[j]=k;
            return;
        }
    }
}

void quadinsert(int a[],int m,int k,int c1,int c2)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+c1*i+c2*i*i)%m;
        if(a[j]==-999)
        {
            a[j]=k;
            return;
        }
    }
}
int primeb(int x)
{
    if(x==2) return 1;
    if(x==3) return 2; 
    int i,j;
    for(i=x-1;i>=1;i--)
    {
        for(j=2;j<i;j++)
        {
           // printf("i=%d j=%d\n",i,j);
            if(i%j==0) 
            {
                j++;
         //       printf("breaked\n");
                break;
            }
        }
        j--;
       // printf("out i=%d j=%d\n",i,j);
        if(i%j!=0) return i;
    }
}
void doubleinsert(int a[],int m,int k,int r)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+i*(r-k%r))%m;
        //j=j%m;
       // printf("r=%d i=%d k=%d val=%d\n",r,i,k,k%m+(r-k%r));
    //    printf("k=%d and j=%d\n",k,j);
        if(a[j]==-999)
        {
            a[j]=k;
            return;
        }
    }
}

void lineardelete(int a[],int m,int k)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+i)%m;
        if(a[j]==k)
        {
            a[j]=-666;
            return;
        }
    }
}

void quaddelete(int a[],int m,int k,int c1,int c2)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+c1*i+c2*i*i)%m;
        if(a[j]==k)
        {
            a[j]=-666;
            return;
        }
    }
}

void doubledelete(int a[],int m,int k,int r)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+i*(r-k%r))%m;
        //j=j%m;
       // printf("r=%d i=%d k=%d val=%d\n",r,i,k,k%m+(r-k%r));
    //    printf("k=%d and j=%d\n",k,j);
        if(a[j]==k)
        {
            a[j]=-666;
            return;
        }
    }
}

int linearsearch(int a[],int m,int k)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+i)%m;
        if(a[j]==k)
        {
            return 1;
        }
        if(a[j]==-999)
        {
            return -1;
        }
    }
    return -1;
}

int quadsearch(int a[],int m,int k,int c1,int c2)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+c1*i+c2*i*i)%m;
        if(a[j]==k)
        {
            return 1;
        }
        if(a[j]==-999)
        {
            return -1;
        }
    }
    return -1;
}

int doublesearch(int a[],int m,int k,int r)
{
    for(int i=0;i<m;i++)
    {
        int j=((k%m)+i*(r-k%r))%m;
        //j=j%m;
       // printf("r=%d i=%d k=%d val=%d\n",r,i,k,k%m+(r-k%r));
    //    printf("k=%d and j=%d\n",k,j);
        if(a[j]==k)
        {
            return 1;
        }
        if(a[j]==-999)
        {
            return -1;
        }
    }
    return -1;
}

int main()
{
    char type;
    int m,c1,c2;
    scanf("%c",&type);
    scanf("%d",&m);
    if(type=='b')
    {
        scanf("%d %d",&c1,&c2);
    }
    int a[m],k,r;
    if(type=='c')
       r=primeb(m);
    //printf("%d",r);
    for(int i=0;i<m;i++)
    {
        a[i]=-999;
    }
    char c;
    for(;;)
    {
        scanf("%c",&c);
        if(c=='T') break;
        switch(c)
        {
            case 'i':scanf("%d",&k);
                     switch(type)
                     {
                        case 'a':linearinsert(a,m,k);
                                break;
                        case 'b':quadinsert(a,m,k,c1,c2);
                                break;
                        case 'c':doubleinsert(a,m,k,r);
                                break;
                     }
                     break;
            case 's':scanf("%d",&k);
                     switch(type)
                     {
                        case 'a':printf("%d\n",linearsearch(a,m,k));
                                break;
                        case 'b':printf("%d\n",quadsearch(a,m,k,c1,c2));
                                break;
                        case 'c':printf("%d\n",doublesearch(a,m,k,r));
                                break;
                     }
                     break;
            case 'p':for(int i=0;i<m;i++)
                    {   
                        printf("%d ",i);
                        printf("(");
                        if(a[i]!=-999&&a[i]!=-666)
                        {
                            printf("%d",a[i]);
                        }
                        printf(")\n");
                    }
                     break;
            case 'd':scanf("%d",&k);
                    switch(type)
                    {
                        case 'a':lineardelete(a,m,k);
                                break;
                        case 'b':quaddelete(a,m,k,c1,c2);
                                break;
                        case 'c':doubledelete(a,m,k,r);
                                break;
                    }
                    break;
        }
    }
}

