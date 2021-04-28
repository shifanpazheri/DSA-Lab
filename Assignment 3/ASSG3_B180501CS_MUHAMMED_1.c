#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
    int height;
};

struct node* getnode(int value)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=value;
    temp->right=NULL;
    temp->left=NULL;
    temp->height=0;
    return temp;
}

struct node* rotatefromright(struct node* x)//left-rotate
{
    struct node*y=x->right;
    x->right=y->left;
    y->left=x;
    return y;
}

struct node* rotatefromleft(struct node* x)//right-rotate
{
    struct node*y=x->left;
    x->left=y->right;
    y->right=x;
    return y;
}

int max(int a,int b)
{
    if (a>b) return a;
    return b;
}

int mag(int a,int b)
{
    if(a>b) return a-b;
    return b-a;
}

int height(struct node* head)
{
    if(head==NULL) return -1;
    return 1+max(height(head->left),height(head->right));
}

struct node* insert(struct node* head,struct node* temp)
{
    if(head==NULL)
    {   
        head=temp;
        return head;
    }
    if(head->data>temp->data)
    {
        head->left=insert(head->left,temp);
        if(mag(height(head->left),height(head->right))==2)
        {
            if(head->left->data>temp->data)
            {
                head=rotatefromleft(head);
            }
            else
            {
                head->left=rotatefromright(head->left);
                head->left->height=1+max(height(head->left->left),height(head->left->right));
                head=rotatefromleft(head);
            }
        }
    }
    if(head->data<temp->data)
    {
        head->right=insert(head->right,temp);
        if(mag(height(head->left),height(head->right))==2)
        {
            if(head->right->data<temp->data)
            {
                head=rotatefromright(head);
            }
            else
            {
                head->right=rotatefromleft(head->right);
                head->right->height=1+max(height(head->right->left),height(head->right->right));
                head=rotatefromright(head);
            }
        }
    }
    head->height=1+max(height(head->left),height(head->right));
    return head;
}

int getbalance(struct node* head)
{
    if(head==NULL) return -999;
    return height(head->left)-height(head->right);
}

void printtree(struct node* head)
{
    if(head==NULL)
     return;
    printf("%d",head->data);
    
    printf("( ");
    printtree(head->left);
    printf(") ");
    
    printf("( ");
    printtree(head->right);
    printf(") ");
}

void inorder(struct node* head)
{
    if(head==NULL)
    return;
    inorder(head->left);
    printf("%d\n",head->data);
    inorder(head->right);
}

int maximum(struct node* head)
{
    if(head==NULL) return -10000;
    if(head->right==NULL) return head->data;
    return maximum(head->right);
}

int minimum(struct node* head)
{
    if(head==NULL) return 10000;
    if(head->left==NULL) return head->data;
    return minimum(head->left);
}

struct node* minm(struct node* head)
{
	if(head==NULL) return head;
	if(head->left!=NULL) return minm(head->left);
	return head;
}

struct node* delete(struct node* head,int value)//study this perfectly
{
        struct node* x=head; 
        if(x==NULL)return x;
        else if (x->data>value) head->left=delete(x->left,value);
        else if (x->data<value) head->right=delete(x->right,value);
        else
        {
                if(x->left==NULL)
                {
                        struct node* temp=x->right;
                        free(x);
			x=temp;//i am using x to balance height
                   //     return x;
                }
                else if (x->right==NULL)
                {
                        struct node* temp=x->left;
                        free(x);
			x=temp;//i am using x to balance height
                 //       return x;
                }
		else
		{
                	struct node*y=minm(x->right);
                	x->data=y->data;
                	x->right=delete(x->right,y->data);
		}
        }

        // return x;
          if(x==NULL) return x;//case when x=child of the head
	  
	  x->height=1+max(height(x->left),height(x->right));

	  int balance=getbalance(x);
//	  printf("balance=%d of data=%d\n",balance,x->data);

	  if(x->left!=NULL&&balance>1&&getbalance(x->left)>=0)//equal is really imp to work the example in geeks
	  {
	//	  printf("true");
		  x=rotatefromleft(x);
	  }
	  if(x->left!=NULL&&balance>1&&getbalance(x->left)<0)
	  {
		  x->left=rotatefromright(x->left);
		  x->left->height=1+max(height(x->left->left),height(x->left->right));
		  x=rotatefromleft(x);
	  }
	  if(x->right!=NULL&&balance<1&&getbalance(x->right)<0)//equal is really imp to work the example in geeks
		  x=rotatefromright(x);
	  if(x->right!=NULL&&balance<1&&getbalance(x->right)>0)
	  {
		  x->right=rotatefromleft(x->right);
		  x->right->height=1+max(height(x->right->left),height(x->right->right));
		  x=rotatefromright(x);
	  }
	  x->height=1+max(height(x->left),height(x->right));
	  return x;
}

int bst(struct node* head)
{
    if(head==NULL) return 1;
    if(head->data>=maximum(head->left)&&head->data<minimum(head->right)&&bst(head->left)&&bst(head->right))
       {
          // printf("bst da");
           return 1;
       }
    return 0;
}

int avl(struct node* head)
{
    if(head==NULL) return 1;
    if(mag(height(head->left),height(head->right))<=1&&avl(head->left)&&avl(head->right))
       return 1;
    return 0;
}

int isavl(struct node* head)
{
    if(bst(head)&&avl(head))
       return 1;
    return 0;
}

struct node* search(struct node* head,int x)
{
    if(head==NULL) return NULL;
    if(head->data==x) return head;
    if(head->data>x) return search(head->left,x);
    if(head->data<x) return search(head->right,x);
}

int main()
{
    struct node* head=NULL;
  //  printf("heo");
    //head=insert(head,getnode(10));
    //head=insert(head,getnode(18));
    //head=insert(head,getnode(22));
    char str[10];
    int x;
    for(;;)
    {   
        scanf(" %s",str);
        if(!strcmp(str,"stop"))
        {
            break;
        }
        if(!strcmp(str,"insr"))
        {
          scanf("%d",&x);
          head=insert(head,getnode(x));
        }
        if(!strcmp(str,"delt"))
        {
	  scanf("%d",&x);
          head=delete(head,x);  
        }
        if(!strcmp(str,"pbal"))
        {
           scanf("%d",&x);
          printf("%d\n",getbalance(search(head,x)));
        }
        if(!strcmp(str,"disp"))
        {
            printf("( ");
            printtree(head);
            printf(")\n");
        }
        if(!strcmp(str,"avlc"))
        {
            printf("%d\n",isavl(head));  
        }
        if(!strcmp(str,"srch"))
        {
            scanf("%d",&x);
            struct node* y=search(head,x);
            if(y==NULL) printf("FALSE\n");
            else printf("TRUE\n");
        }
    }
  //  inorder(head);
}



