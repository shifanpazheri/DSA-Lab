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

void swap(struct heap *a,struct heap *b)
{
	struct heap temp=*a;
	*a=*b;
	*b=temp;
}

void minheapify(struct heap a[],int i,int *hs)
{
	int l=2*i+1;
	int r=2*r+2;
	int smallest;
	if(l<=(*hs)-1&&a[l].data<a[i].data)
	{
		smallest=l;
	}
	else smallest=i;
	if(r<=(*hs)-1&&a[r].data<a[smallest].data)
	{
		smallest=r;
	}
	if(smallest!=i)
	{
		swap(&a[i],&a[smallest]);
		minheapify(a,smallest,hs);
	}
}

struct heap extractmin(struct heap a[],int *hs)
{
	struct heap *temp=(struct heap *)malloc(sizeof(struct heap));
	(*temp).data=-999;
	(*temp).index=-999;
	if(*hs<=0)
	{
		printf("NO ELEMENT PRESENT\n");
		return *temp;
	}
	struct heap min=a[0];
	a[0]=a[(*hs)-1];
	(*hs)-=1;
	minheapify(a,0,hs);
	return min;
}

void decreasekey(struct heap a[],int i,int key)
{
	if(a[i].data<key)
	{
		printf("new is big\n");
		return;
	}
	a[i].data=key;
	while(i>0&&a[i].data<a[(i-1)/2].data)
	{
		swap(&a[i],&a[(i-1)/2]);
		i=(i-1)/2;
	}
}

void heapinsert(struct heap a[],int *hs,int pos,int key)
{
	(*hs)+=1;
	a[(*hs-1)].data=34000;
	a[(*hs)-1].index=pos;
	decreasekey(a,(*hs)-1,key);
}

int min(int a,int b)
{
	if(a>b) return b;
	return a;
}

void dijkstra(struct graph a[],struct edge* head,int n,int s)
{
	int d[n];
	struct heap value[9999];
	int hs=0;
	struct heap *v=(struct heap *)malloc(sizeof(struct heap));
	for(int i=0;i<n;i++)
	{
		d[i]=32999;
		heapinsert(value,&hs,i,d[i]);
	}
	d[s]=0;
	decreasekey(value,s,d[s]);
	while(hs>0)
	{
		*v=extractmin(value,&hs);
		struct list* p=a[v->index].right;
		while(p!=NULL)
		{
			int w=p->index;
			d[w]=min(d[w],d[v->index]+p->data);
			decreasekey(value,w,d[w]);
			p=p->right;
		}
	}
	for(int i=0;i<n;i++)
		printf("%d %d\n",i,d[i]);
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
	int x,y,z,s;
	scanf("%d %d",&n,&m);
	struct graph a[n];
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
	scanf("%d",&s);
	//printf("source=%d\n",s);
	/*for(int i=0;i<n;i++)
	{
		printgraph(a[i].right);
	}*/
	//printedge(head);
	dijkstra(a,head,n,s);
}

