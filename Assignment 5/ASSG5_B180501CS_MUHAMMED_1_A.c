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

struct both
{
	int data;
	struct both* parent;
	int rank;
};

struct both* makesetboth(int x)
{
        struct both* temp=(struct both*)malloc(sizeof(struct both));
        temp->data=x;
        temp->parent=temp;
	temp->rank=0;
        return temp;
}

struct both* findsetboth(struct both* x)
{
        if(x!=x->parent)
                x->parent=findsetboth(x->parent);
        return x->parent;
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

int kruskal(struct graph a[],int n,struct edge * w)
{
	int ans=0;
	int k=0;
	struct both* disjoint[10000];
	int v1,v2;
	for(int i=0;i<n;i++)
	{
		disjoint[k++]=makesetboth(a[i].index);
	}
	struct edge*p=w;
	while(p!=NULL)
	{
		for(int i=0;i<k;i++)
		{
			if(disjoint[i]!=NULL&&disjoint[i]->data==p->src->index)
			{
				v1=p->src->index;
			}
			if(disjoint[i]!=NULL&&disjoint[i]->data==p->dest->index)
			{
				v2=p->dest->index;
			}
		}
		if(findsetboth(disjoint[v1])!=findsetboth(disjoint[v2]))
                {
			ans+=p->weight;
			struct both* t1=findsetboth(disjoint[v1]),*t2=findsetboth(disjoint[v2]);
                        if(findsetboth(disjoint[v1])->rank>=findsetboth(disjoint[v2])->rank)
                                 t1=linkboth(findsetboth(disjoint[v1]),findsetboth(disjoint[v2]));
                        else
                                 t2=linkboth(findsetboth(disjoint[v1]),findsetboth(disjoint[v2]));

        //                printf("%d\n",findsetboth(disjoint[v1])->data);
                }
		p=p->right;
	}
	return ans;
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
	}
	
	printf("value of graph\n");*/

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
	
	printf("%d",kruskal(a,n,head));

}
