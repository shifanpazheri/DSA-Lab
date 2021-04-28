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

int height(struct node* head)
{
    if(head==NULL) return -1;
    return 1+max(height(head->left),height(head->right));
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

struct node* scanparenthesis(struct node* head)
{
    scanf(" (");
    int x;
    if(scanf("%d",&x))
    {
        head=getnode(x);
        head->left=scanparenthesis(head->left);
        head->right=scanparenthesis(head->right);
    }
    scanf(" )");
    return head;
}

void inorder(struct node* head)
{
    if(head==NULL)
    return;
    inorder(head->left);
    printf("%d\n",head->data);
    inorder(head->right);
}

int main()
{
    struct node* head=NULL;
    head=scanparenthesis(head);
    printf("%d\n",isavl(head));
}



