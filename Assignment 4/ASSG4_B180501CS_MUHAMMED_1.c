#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node* left;
	struct node* right;
	char color;
};

struct node * getnode(int key,char c)
{
	struct node * temp=(struct node *)malloc(sizeof(struct node));
	temp->data=key;
	temp->color=c;
	temp->left=NULL;
	temp->right=NULL;
}

/*struct node* parent(struct node* head,struct node* z)
{

        struct node* nullnode=getnode(-999,'B');
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
}*/

struct node * insert(struct node * head)
{
	struct node *nullnode=getnode(-999,'B');
	int x;
	char c;
	scanf(" (");
	if(scanf("%d",&x))
	{
		scanf("%c",&c);//To scan space
		scanf("%c",&c);
		head=getnode(x,c);//don't forget to allocate memory
		head->left=insert(head->left);
		head->right=insert(head->right);
	}
	else
	{
		head=nullnode;
	}
	scanf(" )");
	return head;//imp
}

int max(int a,int b)
{
	if(a>b) return a;
	return b;
}

int blackheight(struct node * head)
{
	if(head->data==-999)
		return 0;//since black height of nullnode is 0
	if(head->color=='B')
	        return 1+max(blackheight(head->left),blackheight(head->right));
	return max(blackheight(head->left),blackheight(head->right));
}

int blacknodecount(struct node* head,struct node* z)
{
	int count=0;
	struct node* nullnode=getnode(-999,'B');
        nullnode->color='B';
        nullnode->right = head;
        nullnode->left = head;
        struct node* y=nullnode;
        struct node* x=head;
        while(x->data!=-999&&x->data!=z->data)//imp
        {
                y=x;
		if(y->color=='B')
			count++;
                if(x->data>z->data)
                        x=x->left;
                else x=x->right;
        }
	if(x->data!=-999&&x->color=='B')
			count++;
	return count;
}

/*int p1(struct node* head)
{
	struct node* nullnode=getnode(-999,'B');
        struct node *current, *pre;

         if (head->data == -999)
              return 0;

         current = head;
         while (current->data != -999) {

        if (current->left->data == -999) {
	//	printf("%d",current->data);
            if(current->color!='B'&&current->color!='R')
                   return 0;
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right->data != -999 && pre->right != current)
                pre = pre->right;
            if (pre->right->data == -999) {
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = nullnode;
	//	printf("%d",current->data);
                if(current->color!='B'&&current->color!='R')
                     return 0;
                current = current->right;
            }
        }
    }
	 return 1;
}

int p4(struct node* head)
{
	struct node* nullnode=getnode(-999,'B');
         struct node *current, *pre;

         if (head->data == -999)
              return 1;

         current = head;
         while (current->data != -999) {

         if (current->left->data == -999) {
		 printf("current->data=%d,current->color=%c",current->data,current->color);
                printf("currentleft->data=%d,currentleft->color=%c",current->left->data,current->left->color);
                printf("currentright->data=%d,currentright->color=%c\n",current->right->data,current->right->color);
                if(current->color=='R'&&(current->left->color=='R'||current->right->color=='R'))
                        return 0;
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right->data != -999 && pre->right != current)
                pre = pre->right;
            if (pre->right->data == -999) {
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = nullnode;
		printf("current->data=%d,current->color=%c",current->data,current->color);
		printf("currentleft->data=%d,currentleft->color=%c",current->left->data,current->left->color);
		printf("currentright->data=%d,currentright->color=%c\n",current->right->data,current->right->color);
                       if(current->color=='R'&&(current->left->color=='R'||current->right->color=='R'))
                             return 0;
                current = current->right; 
            }
        }
    }
        return 1;
}

int p5(struct node* head)
{
         struct node *current, *pre;
	 struct node* nullnode=getnode(-999,'B');
         if (head ->data== -999)
              return 1;

         current = head;
         while (current->data != -999) {

         if (current->left->data == -999) {
		 printf("current->data=%d,current->color=%c",current->data,current->color);
                printf("currentleft->data=%d,currentleft->color=%c",current->left->data,current->left->color);
                printf("currentright->data=%d,currentright->color=%c\n",current->right->data,current->right->color);
                if(current->left->data==-999&&current->right->data==-999&&blacknodecount(head,current)!=blackheight(head))
                        return 0;
            current = current->right;
        }
        else {
            pre = current->left; 
            while (pre->right->data != -999 && pre->right != current) 
                pre = pre->right; 
            if (pre->right->data == -999) { 
                pre->right = current; 
                current = current->left; 
            } 
            else { 
                pre->right = nullnode; 
		printf("current->data=%d,current->color=%c",current->data,current->color);
                printf("currentleft->data=%d,currentleft->color=%c",current->left->data,current->left->color);
                printf("currentright->data=%d,currentright->color=%c\n",current->right->data,current->right->color);
		       if(current->left->data==-999&&current->right->data==-999&&blacknodecount(head,current)!=blackheight(head))
                             return 0;
                current = current->right; 
            } 
        } 
    }
        return 1;
}

int bst(struct node* head)
{
	int k=0;
	int a[9999];
	struct node* nullnode=getnode(-999,'B');
	struct node *current, *pre;

         if (head == NULL)
              return 0;

         current = head;
         while (current->data != -999) {

        if (current->left->data == -999) {
            a[k++]=current->data;
            current = current->right;
        }
        else {
            pre = current->left; 
            while (pre->right->data != -999 && pre->right != current) 
                pre = pre->right; 
            if (pre->right->data == -999) { 
                pre->right = current; 
                current = current->left; 
            } 
            else { 
                pre->right = nullnode; 
                a[k++]=current->data;
                current = current->right; 
            } 
        } 
    }
	for(int i=0;i<k-1;i++)
		if(a[i]>a[i+1])
			return 0;
	return 1;
}*/

/*void inordernonrec(struct node* head)
{
	struct node* nullnode=getnode(-999,'B');
	struct node *current, *pre; 
  
         if (head->data == -999) 
              return; 
  
         current = head; 
         while (current->data != -999) { 
  
        if (current->left->data == -999) { 
            printf("%d %c\n", current->data,current->color); 
            current = current->right; 
        } 
        else { 
            pre = current->left; 
            while (pre->right->data != -999 && pre->right != current) 
                pre = pre->right; 
            if (pre->right->data == -999) { 
                pre->right = current; 
                current = current->left; 
            } 
            else { 
                pre->right = nullnode;// don't forget to make this nullnode 
                printf("%d %c\n", current->data,current->color); 
                current = current->right; 
            } 
        } 
    } 
}*/

int bstarray(struct node* head,int a[])
{
	if(head->data==-999)
		return 55;
	static int k=0;
	int l=bstarray(head->left,a);
	a[k++]=head->data;
	int m=bstarray(head->right,a);
	return k;
}

int bst(struct node* head)
{
	int a[999];
	int k=bstarray(head,a);
	for(int i=0;i<k-1;i++)
	{
	  //   printf("%d\n",a[i]);
	     if(a[i]>a[i+1])
	     {
	//	     printf("break if violation");
		     return 0;
	     }
	}
	return 1;
}

void p1(struct node* root,struct node * head,int * v1)
{
        if(head->data==-999)//change this to see variation of nullnode
                return;
        p1(root,head->left,v1);
  //      printf("head=%c head->left=%c head->right=%c\n",head->color,head->left->color,head->right->color);
        if(head->color!='R'&&head->color!='B')
                *v1=0;
        p1(root,head->right,v1);
}


void p4(struct node* root,struct node * head,int * v4)
{
        if(head->data==-999)//change this to see variation of nullnode
                return;
        p4(root,head->left,v4);
       // printf("head=%c head->left=%c head->right=%c\n",head->color,head->left->color,head->right->color);
        if(head->color=='R'&&(head->left->color=='R'||head->right->color=='R'))
                *v4=0;
        p4(root,head->right,v4);
}

void p5(struct node* root,struct node * head,int * v5)
{
        if(head->data==-999)//change this to see variation of nullnode
                return;
        p5(root,head->left,v5);
      //  printf("head->left=%d head->right=%d blacknodecount=%d blackheightofroot=%d\n",head->left->data,head->right->data,blacknodecount(root,head),blackheight(root));
        if(head->left->data==-999&&head->right->data==-999&&blacknodecount(root,head)!=blackheight(root))
		*v5=0;
        p5(root,head->right,v5);
}


void inorder(struct node* root,struct node * head)
{
	if(head->data==-999)//change this to see variation of nullnode
		return;
	inorder(root,head->left);
        printf("%d ",head->data);
	printf("%c\n",head->color);
	printf("black node count of is %d\n",blacknodecount(root,head));
	inorder(root,head->right);
}

int main()
{
	struct node *head=NULL;
	struct node *nullnode=getnode(-999,'B');
	head=insert(head);
//	inorder(head,head);
//	inordernonrec(head);
        int v5=1,v4=1,v1=1;
	p1(head,head,&v1);
	p4(head,head,&v4);
	p5(head,head,&v5);
	if(v1&&v4&&v5&&head->color=='B'&&bst(head))
	{
		printf("1");
	}
	else 
		printf("0");
}
