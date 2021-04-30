//
//
//THIS CODE WILL NOT WORK FOR DUPLICATE EDGE CASES
//
//

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node* right;
};

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

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void minheapify(int a[],int i,int *hs)
{
	int l=2*i+1;
	int r=2*i+2;
	int smallest;
	if (l<=(*hs)-1&&a[l]<a[i])
		smallest=l;
	else smallest=i;
	if(r<=(*hs)-1&&a[r]<a[smallest])
		smallest=r;
	if(smallest!=i)
	{
		swap(&a[i],&a[smallest]);
		minheapify(a,smallest,hs);
	}
}

int findmin(int a[],int* hs)
{
	if(*hs>=1)
		return a[0];
}

int heapextractmin(int a[],int *hs)
{
	if(*hs<1)
	{
		printf("heap underflow");
		return -999;
	}
	int min=a[0];
	a[0]=a[(*hs)-1];
	(*hs)-=1;
	minheapify(a,0,hs);
	return min;
}

void heapdecreasekey(int a[],int i,int key)
{
	if(key>a[i])
		printf("new key is larger");
	a[i]=key;
	while(i>0&&a[(i-1)/2]>a[i])
	{
		swap(&a[i],&a[(i-1)/2]);
		i=(i-1)/2;
	}
}

void heapinsert(int a[],int key,int *hs)
{
	(*hs)+=1;
	a[(*hs)-1]=33000;
	heapdecreasekey(a,(*hs)-1,key);
}


int prim(struct graph a[],struct edge* head,int n)
{
	int heap[10000];
	int hs=0;
	int s[n];
	int ans=0;
	for(int i=0;i<n;i++)
	{
		s[i]=0;
	}
	s[0]=1;
	//int count=1;
	//printf("hi\n");
	struct list* p=a[0].right;
	while(p!=NULL)
	{
		heapinsert(heap,p->data,&hs);
		p=p->right;
	}
	//printf("hi\n");
	while(hs>0)
	{
		int v=0;
		int f=findmin(heap,&hs);
	//	printf("mins=%d\n",f);//very imp
		ans+=f;
		struct list* q=NULL;
		struct edge* search=head;
		while(search!=NULL)
		{
			if(search->weight==f)
			{
				if(s[(search->src)->index]==0)
				{
					v=(search->src)->index;
					q=(search->src)->right;
					break;
				}
				else if(s[(search->dest)->index]==0)
				{
					v=(search->dest)->index;
					q=(search->dest)->right;
                                        break;
				}
				else 
				{
					q=NULL;
					break;
				}
			}
			search=search->right;
		}
		while(q!=NULL)
		{
			if(s[q->index]==0)
				heapinsert(heap,q->data,&hs);
			else 
			{
				for(int i=0;i<hs;i++)
				{
					if(heap[i]==q->data)
					{
						swap(&heap[0],&heap[i]);
						int temp=heapextractmin(heap,&hs);
					}	
				}
			}
			q=q->right;
		}
		s[v]=1;
	//	count++;//no need of count
	}
	return ans;
}

struct node* getnode(int value)
{
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=value;
	temp->right=NULL;
	return temp;
}

struct node* insertlinkedlist(struct node* head,int value)
{
	struct node* temp=getnode(value);
	if(head==NULL)
	{
		head=temp;
	}
	else
	{
		struct node*p=head;
		while(p->right!=NULL)
		{
			p=p->right;
		}
		p->right=temp;
	}
	return head;
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

struct list* insert_asc(struct list* head,int index,int weight)
{
	struct list* temp=getlist(index,weight);
	if(head==NULL)
	{
		head=temp;
	}
	else if(head->data>temp->data)
	{
		temp->right=head;
		head=temp;
	}
	else
	{
		struct list* p=head;
		struct list* q=head;
		while(p!=NULL)//while inserting in sorted order check p!=NULL for last element
		{
//			printf("p=%d temp=%d q=%d\n",p->data,temp->data,q->data);
			if(p->data>temp->data)
			{
//				printf("inside p=%d temp=%d q=%d\n",p->data,temp->data,q->data);
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


void print(struct node* head)
{
	if(head==NULL)
	{
		printf("NULL");
	}
	else
	{
		struct node* p=head;
		while(p!=NULL)
		{
			printf("%d ",p->data);
			p=p->right;
		}
	}
	printf("\n");
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
	int n;
	scanf("%d",&n);
	struct graph a[n];
	struct node* value[2*n];
	struct edge* head=NULL;
	char ver;
	int x;
	struct node *p,*q;	
	for(int i=0;i<n;i++)
	{
		a[i].index=i;
		a[i].right=NULL;
	}
        
	for(int i=0;i<2*n;i++)
	{
		value[i]=NULL;
		do
		{
			scanf("%d",&x);	
			scanf("%c",&ver);
			value[i]=insertlinkedlist(value[i],x);
		}while(ver!='\n');
//		printf("value of i is %d\n",i);
//		print(value[i]);
	}

/*	for(int i=0;i<2*n;i++)
	{
		print(value[i]);
	}*/
	
//	printf("value of graph\n");

/*	a[3].right=insert_asc(a[3].right,2,12);
	a[3].right=insert_asc(a[3].right,4,22);
	a[3].right=insert_asc(a[3].right,6,24);
	a[3].right=insert_asc(a[3].right,6,18);
	printgraph(a[3].right);*/

	for(int i=0;i<n;i++)
	{
//		printf("value of i=%d top\n",i);
		p=value[i];
		q=value[i+n];
		while(p!=NULL)
		{
//	                printf("(%d,%d) ",p->data,q->data);
			a[i].right=insert_asc(a[i].right,p->data,q->data);
			head=insert_asc_edge(head,&a[i],&a[p->data],q->data);
//			printgraph(a[i].right);
//			printedge(head);
			p=p->right;
			q=q->right;
		}
//		printgraph(a[i].right);
	}

	

/*	for(int i=0;i<n;i++)
        {
                printgraph(a[i].right);
	}*/

//	printedge(head);

	printf("%d\n",prim(a,head,n));

}
