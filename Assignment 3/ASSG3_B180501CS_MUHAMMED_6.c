#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
    int height;
    int count;
};

struct node* getnode(int value)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=value;
    temp->right=NULL;
    temp->left=NULL;
    temp->height=0;
    temp->count=1;
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
    if(head->data==temp->data)
    {
        head->count++;
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

void inorder(struct node* head)
{
    if(head==NULL)
    return;
    inorder(head->left);
    for(int i=0;i<head->count;i++)
        printf("%d ",head->data);
    inorder(head->right);
}

int main()
{
    struct node* head=NULL;
    int n,x;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&x);
        head=insert(head,getnode(x));
    }
    inorder(head);
}




