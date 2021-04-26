#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int data;
	struct node * left;
	struct node * right;
};

struct node * getnode(int x)
{
	struct node * temp=(struct node *)malloc(sizeof(struct node));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

struct node * insert(struct node *head,int k)
{
	struct node *temp=getnode(k);
	struct node *y=NULL;
	struct node *x=head;
	if(head==NULL) head=temp;
	else
	{
	      while(x!=NULL)
	      {
	  	  y=x;
		  if(x->data>=k) x=x->left;
		  else x=x->right;
	      }
	      if(y->data>=k) y->left=temp;
	      else y->right=temp;
	}
	return head;
}

struct node * search(struct node * head,int k)
{
	if(head==NULL) return NULL;
	if(head->data==k) return head;
	if(head->data>=k) 
		return search(head->left,k);
	else
		return search(head->right,k);
}

void minimum(struct node *head)
{
	if(head==NULL) 
	{
		printf("NIL\n");
		return;
	}
	if(head->left!=NULL)
		minimum(head->left);
	else
		printf("%d\n",head->data);
}

/*struct node* parent(struct node* head,struct node* z)
{
        struct node* x=head;
        if(head==NULL)
                return NULL;
        if(head==z) return NULL;
        while(x!=NULL&&x->left!=z&&x->right!=z)
              {
               //   y=x;
                  if(x->data>=z->data) x=x->left;
                  else x=x->right;
              }
        return x;
}*/

void maximum(struct node *head)
{
        if(head==NULL) 
	{
		printf("NIL\n");
		return;
	}
        if(head->right!=NULL)
                maximum(head->right);
        else
                printf("%d\n",head->data);
}

struct node* maxm(struct node* head)
{
	if(head==NULL) return head;
	if(head->right!=NULL)
		return maxm(head->right);
	else return head;
}

struct node* minm(struct node* head)
{
        if(head==NULL) return head;
        if(head->left!=NULL) return minm(head->left);
        else return head;
}


struct node* pred(struct node* head, struct node* x)
{
    if(x->left!= NULL)
        return maxm(x->left);

    struct node *predecessor=NULL;

    while (head!=NULL)
    {
        if (x->data>head->data)
        {
            predecessor=head;
            head=head->right;
        }
        else if (x->data < head->data)
            head=head->left;
        else
           break;
    }
    return predecessor;
}

struct node* succ(struct node* head, struct node* x)
{
    if(x->right!= NULL)
        return minm(x->right);

    struct node *successor=NULL;

    while (head!=NULL)
    {
        if (x->data<head->data)
        {
            successor=head;
            head=head->left;
        }
        else if (x->data > head->data)
            head=head->right;
        else
           break;
    }
    return successor;
}

struct node* delete(struct node* head,int value)//study this perfectly
{
	struct node* x=head; 
	if(x==NULL)return x;
	else if (x->data>value) head->left=delete(x->left,value);
	else if (x->data<value) head->right=delete(x->right,value);
	else
	{
		if(head->left==NULL)
		{
			struct node* temp=x->right;
			free(x);
			return temp;
		}
		else if (head->right==NULL)
		{
			struct node* temp=x->left;
                        free(x);
                        return temp;
		}
		struct node*y=minm(x->right);
		x->data=y->data;
		x->right=delete(x->right,y->data);
	}
	return x;
}

void inorder(struct node *head)
{
	if(head==NULL) return;
	inorder(head->left);
	printf("%d ",head->data);
	inorder(head->right);
}

void preorder(struct node *head)
{
        if(head==NULL) return;
        printf("%d ",head->data);
	preorder(head->left);
        preorder(head->right);
}

void postorder(struct node *head)
{
        if(head==NULL) return;
        postorder(head->left);
        postorder(head->right);
	printf("%d ",head->data);
}

int main()
{
	struct node * head=NULL;
	char s[10];
	int x;
	for(;;)
	{      
		scanf(" %s",s);
		if(!strcmp(s,"stop")) 
			break;
		if(!strcmp(s,"insr"))
		{
			scanf("%d",&x);
			head=insert(head,x);
		}
		if(!strcmp(s,"inor"))
		{
			inorder(head);
			printf("\n");
		}
		if(!strcmp(s,"prer"))
		{
			preorder(head);
			printf("\n");
		}
		if(!strcmp(s,"post"))
		{
			postorder(head);
			printf("\n");
		}
		if(!strcmp(s,"minm"))
		{
			minimum(head);
		}
		if(!strcmp(s,"maxm"))
		{
			maximum(head);
		}
		if(!strcmp(s,"delt"))
		{
			scanf("%d",&x);
                        struct node * node=search(head,x);
                        if(node!=NULL)
			{
				head=delete(head,node->data);
			}
			else
                                printf("NULL\n");
		}
		if(!strcmp(s,"srch"))
		{
			scanf("%d",&x);
			if(search(head,x)!=NULL) printf("FOUND");
			else printf("NOT FOUND");
			printf("\n");
		}
		if(!strcmp(s,"pred"))
		{
			scanf("%d",&x);
			struct node * node=search(head,x);
			if(node!=NULL&&node->data!=minm(head)->data)
                 		printf("%d\n",pred(head,node)->data);
			else if(node!=NULL&&node->data==minm(head)->data)
				printf("%d\n",-1);
			else
				printf("NULL\n");
		}
		if(!strcmp(s,"succ"))
		{
			scanf("%d",&x);
                        struct node * node=search(head,x);
                        if(node!=NULL&&node->data!=maxm(head)->data)
                                printf("%d\n",succ(head,node)->data);
                        else if(node!=NULL&&node->data==maxm(head)->data)
                                printf("%d\n",-1);
                        else
                                printf("NULL\n");
		}
	}
}
