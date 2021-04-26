#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
        int data;
        struct node * left;
        struct node * right;
    //    struct node * p;
};

struct node * getnode(int x)
{
        struct node * temp=(struct node *)malloc(sizeof(struct node));
        temp->data=x;
        temp->left=NULL;
        temp->right=NULL;
      //  temp->p=NULL;
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
           //   temp->p=y;
              if(y->data>=k) y->left=temp;
              else y->right=temp;
        }
        return head;
}

void printparenthesis(struct node* head)
{
    if(head==NULL) return;
    printf("%d ",head->data);
   // if(head->left==NULL&&head->right==NULL) return;
    printf("( ");
    printparenthesis(head->left);
    printf(") ");
    printf("( ");
    printparenthesis(head->right);
    printf(") ");
}
void inorder(struct node *head)
{
        if(head==NULL) return;
        inorder(head->left);
        printf("%d ",head->data);
        inorder(head->right);
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
                if(!strcmp(s,"prep"))
                {
			printf("( ");
                        printparenthesis(head);
			printf(")");
                }
		if(!strcmp(s,"inor"))
		{
			inorder(head);
		}
	}

}
