#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* getnode(int value)
{
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=value;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

struct node* preorderrev(struct node* head,int a[],int p,int q)
{
	int i;
	if(p>q) return NULL;
	else
	{
	//	printf("data=%d\n",a[p]);
		head=getnode(a[p]);
		for(i=p;i<=q;i++)
			if(a[p]<a[i])
               			break;
//		printf("a[i]=%d",a[i]);
		head->left=preorderrev(head->left,a,p+1,i-1);//imp
		head->right=preorderrev(head->right,a,i,q);//imp
		return head;
	}
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

void preorder(struct node* head)
{
	if(head==NULL) return;
        printf("%d\n",head->data);
//	if(head->left!=NULL)
        preorder(head->left);
//	if(head->right!=NULL)
        preorder(head->right);
}

int main()
{
    struct node* head=NULL;
    int x,n,i;
    scanf("%d",&n);
    int a[n];
    for(i=0;i<n;i++)
	    scanf("%d",&a[i]);
    head=preorderrev(head,a,0,n-1);
 //   preorder(head);
    printf("( ");
    printparenthesis(head);
    printf(")");
}


