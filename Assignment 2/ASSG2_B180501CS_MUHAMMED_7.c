#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct stack
{
    int top;
    int data[100];
    int capacity;
};

void push(struct stack *s,int x)
{
    (s->top)++;
    if(s->top>=s->capacity)
    {
        (s->top)--;
        printf("OVERFLOW\n");
    }
    else
    s->data[s->top]=x;
}

int isempty(struct stack s)
{
    if(s.top==-1)
    return 1;
    return 0;
}

int top(struct stack s)
{
    if(isempty(s))
        return -999;
    else
        return s.data[s.top];
}

void pop(struct stack*s)
{
    if(isempty(*s))
        printf("EMPTY\n");
    else
    {
        s->top--;
    }
}

int value(char *c,int f,int l)
{
    if(f>l) return -999;
    int len=l-f;
    int no=0;
//    if(strlen(c)==0) return -999;
    for(int i=f;i<=l;i+=1)
    {
 //       printf("len=%d\n",len);
   //     printf("c[i]=%d\n",c[i]-'0');
        no=no+pow(10,len)*(c[i]-'0');
     //   printf("no=%d\n",no);
        len--;
    }
    return no;
}

int findIndex(char c[],int f,int l)
{
    if(f>l) return -1;
    struct stack s;
    s.top=-1;
    s.capacity=99999;
    for(int i=f;i<=l;i++)
    {
        if(c[i]=='(')
        {
            push(&s,c[i]);
        }
        if(c[i]==')')
        {
            if(top(s)=='(')
               pop(&s);
        }
        if(isempty(s)) return i;
    }
    return -1;
}

struct node* getnode(int data)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return (temp);
}

struct node* treeFromString(char str[], int si, int ei)//spaces also considered
{
    // Base case
    if (si > ei)
        return NULL;
    int val;
    int i=si;
    while(str[i]!='(')
    {
        i++;
    }
 //   printf("%c\n",str[i]);
    val=value(str,si,i-2);
    // new root
//    printf("%d\n",val);
    struct node* head = getnode(val);
    int index = -1;
   // printf("str[i]=%c\n",str[i]);
    //printf("i=%d,ei=%d\n",i,ei);
    if (i <= ei && str[i] == '(')
        {
            //printf("check");
            index = findIndex(str, i , ei);// if next char is '(' find the index of its complement ')'
        }
    //printf("index=%d\n",index);
    // if index found
    if (index != -1) {
        head->left = treeFromString(str, i + 2, index - 2);// recursive call for left subtree->it exclude start and end parenthesis
        head->right = treeFromString(str, index + 4, ei-2);// recursive call for right subtree->it exclude start and end parenthesis
    }
    return head;
}

/*int max3(int a,int b,int c)
{
        if(a>b&&a>c) return a;
        else if (b>c) return b;
        else return c;
}*/

int inordertravel(struct node* head,int a[])
{
	static int i=0;
	if(head==NULL) return ;
	inordertravel(head->left,a);
	a[i]=head->data;
//	printf("head=%d\n",head->data);
//	printf("a[i]=%d\n",a[i]);
	i++;
	inordertravel(head->right,a);
	return i;
}

int maxsubtree(struct node* head,int a[],int n)
{
	int count=1;
	int max=1;
	if(n==0) return 0;
	for(int i=0;i<n-1;i++)
	{       if(a[i]<=a[i+1])
			count++;
	        if(max<count)
			max=count;
		if(a[i]>a[i+1])
			count=1;
        }
	return max;
}

void preOrder(struct node* head)
{
    if (head == NULL)
        return;
    printf("%d ", head->data);
    preOrder(head->left);
    preOrder(head->right);
}

int main()
{
    char str[999];
    scanf("%[^\n]s",str);
    struct node* head=NULL;
    head=treeFromString(str,2 , strlen(str) - 3);//index is very important
    int a[strlen(str)+10];
    int n=inordertravel(head,a);
  //  for(int i=0;i<n;i++)
//	    printf("%d\n",a[i]);
//    preOrder(head);
   printf("%d",maxsubtree(head,a,n));
  //  printf("%d",value("589654",3,2));
}


