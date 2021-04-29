#include<stdio.h>
#include<stdlib.h>
struct nor
{
	int data;
	struct nor* parent;
};

struct union_rank
{
	int data;
	int rank;
	struct union_rank* parent;
};

struct path
{
	int data;
	struct path* parent;
};

struct both
{
	int data;
	struct both* parent;
	int rank;
};

struct nor* makesetnor(int x)
{
	struct nor* temp=(struct nor*)malloc(sizeof(struct nor));
	temp->data=x;
	temp->parent=temp;
	return temp;
}

struct union_rank* makesetunion_rank(int x)
{
        struct union_rank* temp=(struct union_rank*)malloc(sizeof(struct union_rank));
        temp->data=x;
        temp->parent=temp;
	temp->rank=0;
        return temp;
}

struct path* makesetpath(int x)
{
        struct path* temp=(struct path*)malloc(sizeof(struct path));
        temp->data=x;
        temp->parent=temp;
        return temp;
}

struct both* makesetboth(int x)
{
        struct both* temp=(struct both*)malloc(sizeof(struct both));
        temp->data=x;
        temp->parent=temp;
	temp->rank=0;
        return temp;
}

struct nor* findsetnor(struct nor* x)
{
	if(x!=x->parent)
		return findsetnor(x->parent);
}

struct union_rank* findsetunion_rank(struct union_rank* x)
{
        if(x!=x->parent)
                return findsetunion_rank(x->parent);
}

struct path* findsetpath(struct path* x)
{
        if(x!=x->parent)
                x->parent=findsetpath(x->parent);
        return x->parent;
}

struct both* findsetboth(struct both* x)
{
        if(x!=x->parent)
                x->parent=findsetboth(x->parent);
        return x->parent;
}

struct nor* linknor(struct nor* x,struct nor* y)
{
	y->parent=x;
	return x; 
}

struct union_rank* linkunion_rank(struct union_rank* x,struct union_rank* y)
{
	if(x->rank>=y->rank)
	{
		y->parent=x;
		if(x->rank==y->rank)
			x->rank++;
		return x;
	}
	else
	{
		x->parent=y;
		return y;
	}
}

struct path* linkpath(struct path* x,struct path* y)
{
        y->parent=x;
        return x;
}

struct both* linkboth(struct both* x,struct both* y)
{
        if(x->rank>=y->rank)
        {
                y->parent=x;
                if(x->rank==y->rank)
                        x->rank++;
                return x;
        }
        else
        {
                x->parent=y;
                return y;
        }
}


int main()
{
	struct nor* a[999];
	struct union_rank* b[999];
	struct path* c[999];
	struct both* d[999];
	int count1=0,count2=0,count3=0,count4=0;
	for(int i=0;i<999;i++)
	{
		a[i]=NULL;
		b[i]=NULL;
		c[i]=NULL;
		d[i]=NULL;
	}
	int k=0,x,flag=0;
	int x1,x2,flag1,flag2,v1,v2;
	char check;
	for(;;)
	{
		scanf(" %c",&check);
		if(check=='s')
			break;
		switch(check)
		{
			case 'm':scanf("%d",&x);
				 flag=0;
				 for(int i=0;i<999;i++)
				 {
					 if(a[i]!=NULL&&a[i]->data==x)
					 {
						 printf("PRESENT\n");
						 flag=1;
					 }
				 }
				 if(flag==1)
				 	 break;
			         a[k]=makesetnor(x);
			         b[k]=makesetunion_rank(x);
			         c[k]=makesetpath(x);
			         d[k]=makesetboth(x);
			         k++;
			 	 printf("%d\n",x);
			         break;
			case 'f':scanf("%d",&x);
				 flag=0;
				 int i;
				 for(i=0;i<999;i++)
				 {
					// if(a[i]!=NULL)
					// printf("%d ",a[i]->data);
					 if(a[i]!=NULL&&a[i]->data==x)
					 {
					//	 printf("YES IT IS");
						 flag=1;
						 break;
					 }
				 }
				 if(flag==0)
				 {
					 printf("NOT FOUND\n");
					 break;
				 }
				 printf("%d ",findsetnor(a[i])->data);
				 printf("%d ",findsetunion_rank(b[i])->data);
				 printf("%d ",findsetpath(c[i])->data);
				 printf("%d\n",findsetboth(d[i])->data);
				 break;
			case 'u':scanf("%d %d",&x1,&x2);
				 flag1=0;
				 flag2=0;
				 v1=0;
				 v2=0;
				 for(i=0;i<999;i++)
                                 {
                                        // if(a[i]!=NULL)
                                        // printf("%d ",a[i]->data);
                                         if(a[i]!=NULL&&a[i]->data==x1)
                                         {
                                        //       printf("YES IT IS");
                                                 v1=i;
						 flag1=1;
                                         }
					 if(a[i]!=NULL&&a[i]->data==x2)
					 {
						 v2=i;
						 flag2=1;
					 }
                                 }
				 if(flag1==0||flag2==0)
				 {
					 printf("ERROR\n");
					 break;
				 }
				 if(findsetnor(a[v1])!=findsetnor(a[v2]))
				 {
					 struct nor* t1=findsetnor(a[v1]),*t2=findsetnor(a[v2]);
					 t1=linknor(findsetnor(a[v1]),findsetnor(a[v2]));
					 printf("%d ",findsetnor(a[v1])->data);
				 }
				 else printf("%d ",findsetnor(a[v1])->data);

				 if(findsetunion_rank(b[v1])!=findsetunion_rank(b[v2]))
                                 {
					 struct union_rank* t1=findsetunion_rank(b[v1]),*t2=findsetunion_rank(b[v2]);
					 if(findsetunion_rank(b[v1])->rank>=findsetunion_rank(b[v2])->rank)
                                         	 t1=linkunion_rank(findsetunion_rank(b[v1]),findsetunion_rank(b[v2]));
					 else
                                                 t2=linkunion_rank(findsetunion_rank(b[v1]),findsetunion_rank(b[v2]));

					 printf("%d ",findsetunion_rank(b[v1])->data);
                                 }
                                 else printf("%d ",findsetunion_rank(b[v1])->data);

				 if(findsetpath(c[v1])!=findsetpath(c[v2]))
                                 {
					 struct path* t1=findsetpath(c[v1]),*t2=findsetpath(c[v2]);
                                         t1=linkpath(findsetpath(c[v1]),findsetpath(c[v2]));
                                         printf("%d ",findsetpath(c[v1])->data);
                                 }
                                 else printf("%d ",findsetpath(c[v1])->data);

				 if(findsetboth(d[v1])!=findsetboth(d[v2]))
                                 {
					 struct both* t1=findsetboth(d[v1]),*t2=findsetboth(d[v2]);
                                         if(findsetboth(d[v1])->rank>=findsetboth(d[v2])->rank)
                                                 t1=linkboth(findsetboth(d[v1]),findsetboth(d[v2]));
                                         else
                                                 t2=linkboth(findsetboth(d[v1]),findsetboth(d[v2]));

                                         printf("%d\n",findsetboth(d[v1])->data);
                                 }
                                 else printf("%d\n",findsetboth(d[v1])->data);
		}
	}
	for(int i=0;i<k;i++)
	{
		printf("%d\n",a[i]->data);
		printf("%d %d\n",b[i]->data,b[i]->rank);
		printf("%d\n",c[i]->data);
		printf("%d %d\n",d[i]->data,d[i]->rank);
	}
}
