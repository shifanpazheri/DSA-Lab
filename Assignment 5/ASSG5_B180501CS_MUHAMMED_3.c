#include<stdio.h>
#include<stdlib.h>

struct graph
{
	int index;
	struct list* right;
};

struct list
{
	int index;
	int data;
	struct list* right;
};

struct edge
{
        int weight;
        struct graph* src;
        struct graph* dest;
        struct edge* right;
};

struct heap
{
	int index;
	int data;
};

int min(int a,int b)
{
	if(a>b) return b;
	return a;
}

int bellmanford(struct graph a[],struct edge* head,int n)
{
	struct heap value[10000];
//	printf("n=%d\n",n);
	for(int k=0;k<n;k++)// my additional fitting->remove in case of timeout
	{//incase of negative cycle it exit as soon as it see one cycle
//	printf("present k=%d\n",k);
	for(int i=0;i<n;i++)	
	{
		value[i].data=32999;
		value[i].index=i;
	}
	value[k].data=0;//make k=0 incase of timeout
	for(int i=0;i<n-1;i++)
	{
		struct edge* p=head;
		while(p!=NULL)
		{
			if(p->dest->index!=k)//make k=0 incase of timeout
			{
				value[(p->dest)->index].data=min(value[(p->dest)->index].data,value[(p->src)->index].data+p->weight);
			}
			p=p->right;
		}
	}
/*	for(int i=0;i<n;i++)
	{
		printf("index=%d data=%d\n",value[i].index,value[i].data);
	}*/
	struct edge* p=head;
        while(p!=NULL)
        {
	//	printf("dest=%d sum=%d\n",value[(p->dest)->index].data,value[(p->src)->index].data+p->weight);
                if(value[(p->dest)->index].data>value[(p->src)->index].data+p->weight)
		{
		//	printf("dest=%d sum=%d\n",value[(p->dest)->index].data,value[(p->src)->index].data+p->weight);
			return 0;
		}
		p=p->right;
        }
	}
	return 1;
}


struct list* getlist(int pos,int data)
{
	struct list* temp=(struct list*)malloc(sizeof(struct list));
	temp->index=pos;
	temp->data=data;
	temp->right=NULL;
	return temp;
}

struct edge* getedge(struct graph* s,struct graph* d,int value)
{
	struct edge* temp=(struct edge*)malloc(sizeof(struct edge));
	temp->src=s;
	temp->dest=d;
	temp->weight=value;
	return temp;
}

struct list* insertlist(struct list* head,int index,int weight)
{
	struct list* temp=getlist(index,weight);
//	printf("temp->index=%d weight=%d\n",temp->index,temp->data);
	if(head==NULL)
	{
		head=temp;
	}
	else
	{
		temp->right=head;
		head=temp;
	}
	return head;
}

struct edge* insert_asc_edge(struct edge* head,struct graph*src,struct graph* dest,int data)
{
	struct edge* temp=getedge(src,dest,data);
	if(head==NULL)
	{
		head=temp;
	}
	else if(head->weight>temp->weight)
	{
		temp->right=head;
		head=temp;
	}
	else
	{

		struct edge* p=head;
		struct edge* q=head;
		while(p!=NULL)//while inserting in sorted order check p!=NULL for last element
		{
			if(p->weight>temp->weight)
			{
				temp->right=p;
				q->right=temp;
				break;
			}
			q=p;
			p=p->right;//don't forget
		}
		p=q;
		if(p->right==NULL)
		{
			p->right=temp;
		}
	}
	return head;
}

void printgraph(struct list* head)
{
        if(head==NULL)
        {
                printf("NULL");
        }
        else
        {
                struct list* p=head;
                while(p!=NULL)
                {
                        printf("(%d,%d) ",p->index,p->data);
			p=p->right;
                }
        }
        printf("\n");
}

void printedge(struct edge* head)
{
	if(head==NULL)
		printf("NULL\n");
	else
	{
		struct edge* p=head;
		while(p!=NULL)
		{
			printf("(src=%d,dest=%d,wt=%d) \n",p->src->index,p->dest->index,p->weight);//don't print head details we should print p details
			p=p->right;
		}
	}
	printf("\n");
}

int main()
{
	int n;//no.of vertex
	int m;//no.of edge
	int x,y,z;
	scanf("%d %d",&n,&m);
	struct graph a[10000];//make this a large value more than n or segmentation fault occur
	for(int i=0;i<n;i++)
	{
		a[i].index=i;
		a[i].right=NULL;
	}
	struct edge* head=NULL;
	for(int i=0;i<m;i++)
        {
                scanf("%d %d %d",&x,&y,&z);
                a[x].right=insertlist(a[x].right,y,z);
                head=insert_asc_edge(head,&a[x],&a[y],z);
        }
/*	for(int i=0;i<n;i++)
	{
		printgraph(a[i].right);
	}*/
//	printedge(head);

	if(bellmanford(a,head,n)==1||m==0)
		printf("-1");
	else printf("1");
}
