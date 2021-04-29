#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int data;
	struct node* sibling;
	struct node* parent;
	struct node* child;
	int degree;
	struct node* add;
};

void swap(struct node**x,struct node**y)
{
	struct node* temp=*x;
	*x=*y;
	*y=temp;
}

void swapint(int *x,int *y)
{
	int temp=*x;
	*x=*y;
	*y=temp;
}

struct node* binomialheapminimum(struct node* h)
{
	struct node* y=NULL;
	struct node* x=h;
	int min=35000;
	while(x!=NULL)
	{
		if(x->data<min)
		{
			min=x->data;
			y=x;
		}
		x=x->sibling;
	}
	return y;
}

struct node* link (struct node* x,struct node* y)
{
	y->sibling=x->child;
	x->child=y;
	y->parent=x;
	return x;
}

struct node* binomialheapmerge(struct node*p,struct node*q)
{
	if(p==NULL)
		return q;
	else if(q==NULL)
		return p;
	else
	{
		if((p->degree)<=(q->degree))
		{
			p->sibling=binomialheapmerge(p->sibling,q);
			return p;
		}
		else
		{
			q->sibling=binomialheapmerge(q->sibling,p);
			return q;
		}
	}
}

struct node* binomiallink(struct node* y,struct node* z)
{
	y->parent=z;
	y->sibling=z->child;
	z->child=y;
	z->degree=z->degree+1;
	return z;
}

struct node* binomialheapunion(struct node* h1,struct node* h2)
{
	struct node* h=(struct node*)malloc(sizeof(struct node));
	h=binomialheapmerge(h1,h2);
	if(h==NULL)
		return h;
	struct node* prevx=NULL;
	struct node* x=h;
	struct node* nextx=x->sibling;
	while(nextx!=NULL)
	{
		if(x->degree!=nextx->degree||(nextx->sibling!=NULL&&nextx->sibling->degree==x->degree))
		{
			prevx=x;
			x=nextx;
		}
		else
		{	
			if(x->data<=nextx->data)
			{
				x->sibling=nextx->sibling;
				x=binomiallink(nextx,x);
			}
			else
			{
				if(prevx==NULL)
				{
					h=nextx;
				}
				else
				{
					prevx->sibling=nextx;
				}
				x=binomiallink(x,nextx);
				x=nextx;
			}
		}
	nextx=x->sibling;
	}
	return h;
}

struct node* binomialheapinsert(struct node* h,int x,int pos,struct node* a[])
{
	struct node* hh=(struct node*)malloc(sizeof(struct node));
	a[pos]=hh;
	hh->parent=hh->sibling=hh->child=NULL;
	hh->degree=0;
	hh->add=a[pos];
	hh->data=x;
	h=binomialheapunion(h,hh);
	return h;
}

struct node* binomialheapextractmin(struct node** h,struct node* a[])
{
	struct node* x=binomialheapminimum(*h);
	struct node* y=*h;
	struct node* z=NULL;
	/*if(*h==x&&x->child==NULL)
	{
		*h=(*h)->sibling;
		return x;
	}*/
	/*else if((*h)->sibling!=NULL&&(*h)->sibling==x) 
	{
		(*h)->sibling=x->child;
		x->child->parent=NULL;
		(*h)->sibling->sibling=x->sibling;
		return x;
	}*/
	{
	while(y!=x)
	{
		z=y;
		y=y->sibling;
	}
	if(z!=NULL)
		z->sibling=x->sibling;
	else
		*h=x->sibling;
	struct node* hh=NULL;
	struct node *prev=NULL;
	struct node* next=x->child;
	struct node*current=x->child;
	while(current!=NULL)
	{
		current->parent=NULL;
		next=current->sibling;
		current->sibling=prev;
		prev=current;
		current=next;
	}
	hh=prev;
	//check
        /*while(prev!=NULL)
	{
		printf("values of child %d \n",prev->data);
		prev=prev->sibling;
	}*/
	//check
	for(int i=0;i<999;i++)
	{
		if(a[i]!=NULL&&a[i]->data==x->data)
		{	
			a[i]=NULL;
			break;
		}
	}
	*h=binomialheapunion(*h,hh);
	}
	return x;
}

void binomialheapdecreasekey(struct node* h,struct node**x,int k,struct node* a[])
{
	if(k>(*x)->data&&k!=35000)
	{
		printf("-1\n");
		return;
	}
	(*x)->data=(*x)->data-k;
	struct node* y=*x;
	struct node* z=y->parent;
	int v1,v2;
	while(z!=NULL&&y->data<z->data)
	{
		for(int i=0;i<999;i++)
		{
			if(a[i]!=NULL&&a[i]==y)
				v1=i;
			if(a[i]!=NULL&&a[i]==z)
				v2=i;
		}
		struct node* temp=a[v1];
		a[v1]=a[v2];
		a[v2]=temp;
/*		swap(&y->child,&z->child);
		swap(&y->sibling,&z->sibling);
		swap(&y->parent,&z->parent);*/
//		swapint(&y->degree,&z->degree);
		swapint(&y->data,&z->data);
	//	swap(&y,&z);
		y=z;
		z=z->parent;
	}
}

int main()
{
	struct node* a[999];
	int n;
	scanf("%d",&n);
	char string[10];
	struct node* h=NULL;
	int pos,value;
	for(int i=0;i<999;i++)
	{
		a[i]=NULL;
	}

	for(;;)
	{
		scanf(" %s",string);
		if(!strcmp(string,"stop"))
		{
			break;
		}
		if(!strcmp(string,"insr"))
		{
			scanf("%d %d",&pos,&value);
			if(a[pos]==NULL&&pos<n)
			{
				h=binomialheapinsert(h,value,pos,a);
			}
			else
			{
				printf("-1\n");
			}
		}
		if(!strcmp(string,"min"))
		{
			if(h!=NULL)
				printf("%d\n",(binomialheapminimum(h))->data);
			else printf("-1\n");
		}
		if(!strcmp(string,"tc"))
		{
			int count=0;
			struct node* temp=h;
			while(temp!=NULL)
			{
				temp=temp->sibling;
				count++;
			}
			printf("%d\n",count);
		}
		if(!strcmp(string,"extr"))
		{
			if(h!=NULL)
				printf("%d\n",binomialheapextractmin(&h,a)->data);
			else printf("-1\n");
		}
		if(!strcmp(string,"roots"))
		{
			struct node* final=h;
        		while(final!=NULL)
        		{
                		printf("%d ",final->data);
				final=final->sibling;
        		}
		}
		if(!strcmp(string,"decr"))
		{
			int pos,k;
			scanf("%d %d",&pos,&k);
			if(a[pos]!=NULL)
				binomialheapdecreasekey(h,&a[pos],k,a);//bcuz a[i] contain address of that key
			else printf("-1\n");
		}
		if(!strcmp(string,"del"))
		{
			int pos;
			scanf("%d",&pos);
			if(a[pos]!=NULL)
			{
				printf("%d\n",a[pos]->data);
				binomialheapdecreasekey(h,&a[pos],35000,a);//bcuz a[i] contain address of that key
				struct node* simply=binomialheapextractmin(&h,a);
			}
                        else printf("-1\n");
		}
		if(!strcmp(string,"check"))
		{
			for(int i=0;i<n;i++)
        		{
                		if(a[i]!=NULL)
                		{
                        		printf("i=%d,value,pointed=%d\n ",i,a[i]->data);
                		}
        		}
		}
	}
	/*for(int i=0;i<n;i++)
	{
		if(a[i]!=NULL)
		{
			printf("%d ",a[i]->data);
		}
	}*/
	/*struct node* final=h;
	while(final!=NULL)
	{
		printf("%d ",final->data);
		final=final->sibling;
	}*/
}
