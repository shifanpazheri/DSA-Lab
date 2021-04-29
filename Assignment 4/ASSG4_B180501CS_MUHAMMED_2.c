#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node 
{
	int data;
	struct node* left;
	struct node* right;
	char color;
};

struct node* getnode(int key)
{
	//struct node* nullnode;
	//nullnode->data=-999;
        //nullnode->color='B';
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=key;
	return temp;
}

struct node* parent(struct node* head,struct node* z)
{

	struct node* nullnode=getnode(-999);
        nullnode->color='B';
		nullnode->right = head;
		nullnode->left = head;
    if(head == z)
		return nullnode;
	    struct node* y=nullnode;
        struct node* x=head;
        while(x->data!=-999&&x->data!=z->data)//imp
        {
                y=x;
                if(x->data>z->data)
                        x=x->left;
                else x=x->right;
        }
	return y;
}

struct node* leftrotate(struct node* x)
{
	struct node* y=x->right;
	x->right=y->left;
	y->left=x;
	return y;
}

struct node* rightrotate(struct node* x)
{
        struct node* y=x->left;
        x->left=y->right;
        y->right=x;
        return y;
}

struct node* rbinsertfixup(struct node* head,struct node* z)
{
	while(parent(head,z)->color=='R')
	{
		if(parent(head,z)==parent(head,parent(head,z))->left)
		{
			struct node* y=parent(head,parent(head,z))->right;
			if(y->color=='R')
			{
				y->color='B';
				parent(head,z)->color='B';
				parent(head,parent(head,z))->color='R';
				z=parent(head,parent(head,z));
				continue;//imp
			}
			else if(z==parent(head,z)->right)//don't forget "=="
			{
				z=parent(head,z);
				y = parent(head, z);
				y->right =leftrotate(z);
			}
			parent(head,z)->color='B';
			parent(head,parent(head,z))->color='R';
			z=(parent(head,parent(head,z)));//last five line of code is required to avoid lvalve so we must break it
                        y = (parent(head, z));
			if(head==z)
				head=rightrotate(head);
			else
			{      if(y->left==z)
			       	       y->left=rightrotate(z);
			       else
				       y->right=rightrotate(z);
			}
			break;
		}
		else
		{
			struct node* y=parent(head,parent(head,z))->left;
                        if(y->color=='R')
                        {
                                y->color='B';
                                parent(head,z)->color='B';
                                parent(head,parent(head,z))->color='R';
                                z=parent(head,parent(head,z));
                                continue;
                        }
                        else if(z==parent(head,z)->left)//don't forget "=="
                        {
                                z=parent(head,z);
			        y = parent(head, z);
                                y->left =rightrotate(z);
                        }
                        parent(head,z)->color='B';
                        parent(head,parent(head,z))->color='R';		
			z=(parent(head,parent(head,z)));//last five line of code is required to avoid lvalve so we must break it
	                y = (parent(head, z));
			if(head==z)
                                head=leftrotate(head);
                        else
			{
				if(y->right==z)
			                y->right=leftrotate(z);
				else
					y->left=leftrotate(z);
			}
			break;
		}
	}
	head->color='B';
	return head;
}

struct node* insert(struct node* head,struct node* z)
{
	struct node* nullnode=getnode(-999);
	nullnode->color='B';
	struct node* y=nullnode;
	struct node* x=head;
//	printf("%d ",x->data);
  //    printf("%c\n",x->color);
	while(x->data!=-999)//imp
	{
		y=x;
		if(x->data>z->data)
			x=x->left;
		else x=x->right;
	}
	if (y==nullnode)
	{
		head=z;
    //    printf("%d ",head->data);
  //      printf("%c\n",head->color);
	}
	else if(y->data>z->data)
		y->left=z;
	else y->right=z;
	z->left=nullnode;
	z->right=nullnode;
	z->color='R';
	head=rbinsertfixup(head,z);//imp
	return head;//if you get error while inserting second element you forgot this
}

void printparenthesis(struct node* head)
{
	if(head->data==-999)
		return;
	printf("%d %c ",head->data,head->color);
	printf("( ");
	printparenthesis(head->left);
	printf(") ");
        printf("( ");
        printparenthesis(head->right);
        printf(") ");
}

void inorder(struct node* head)
{
	if(head->data==-999)
		return;
	inorder(head->left);
	printf("%d ",head->data);
	printf("%c\n",head->color);
	inorder(head->right);
}

int main()
{
	struct node* nullnode=getnode(-999);
	nullnode->color='B';
	struct node* head=nullnode;//don't forget this bcuz u check this while insert
	char string[20];// make this large or their will be stack smash
	int x;
	for(;;)
        {
		scanf(" %s",string);
		if(!strcmp(string,"insr"))//imp !of strcmp
		{
			scanf("%d",&x);
			struct node* z=getnode(x);
			head=insert(head,z);
			printf("( ");
			printparenthesis(head);
			printf(")\n");
		}
	        if(!strcmp(string,"stop"))
			break;
/*		if(!strcmp(string,"pare"))
		{
			scanf("%d",&x);
			struct node* z=parent(head,getnode(x));
			if(z->data!=-999)
				printf("%d",z->data);
		}
		if(!strcmp(string,"ppp"))
		{
			scanf("%d",&x);
                        struct node* z=parent(head,parent(head,getnode(x)));
                   //     if(z->data!=-999)
                                printf("%d",z->data);
		}*/
	}
}
