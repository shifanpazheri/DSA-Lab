#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* left;
    struct node* right;
    int sum;
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
	  if(c[i]=='-')
	  {
		  len--;
		  continue;
	  }
 //       printf("len=%d\n",len);
   //     printf("c[i]=%d\n",c[i]-'0');
          no=no+pow(10,len)*(c[i]-'0');
     //   printf("no=%d\n",no);
        len--;
    }
    if(c[f]=='-') no*=-1;
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
    temp->sum=-999;
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

struct node* update_tree(struct node* head)
{
	if(head->right!=NULL&&head->left!=NULL) 
	{
		head->right=update_tree(head->right);
		head->left=update_tree(head->left);
		head->sum=head->data+(head->left)->sum+(head->right)->sum;
	}
	else if(head->right!=NULL)
	{
		head->right=update_tree(head->right);
                head->sum=head->data+(head->right)->sum;
	}
	else if(head->left!=NULL)
	{
                head->left=update_tree(head->left);
                head->sum=head->data+(head->left)->sum;
	}
	else
		head->sum=head->data;
	return head;
}

void printparenthesis(struct node* head)
{
    if(head==NULL) return;
    printf("%d ",head->sum);
   // if(head->left==NULL&&head->right==NULL) return;
    printf("( ");
    printparenthesis(head->left);
    printf(") ");
    printf("( ");
    printparenthesis(head->right);
    printf(") ");
}

void preOrder(struct node* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

int main()
{
    char str[10000];
    scanf("%[^\n]s",str);
    struct node* head=NULL;
    head=treeFromString(str,2 , strlen(str) - 3);//index is very important
  //  preOrder(head);
    head=update_tree(head);
    printf("( ");
    printparenthesis(head);
    printf(")");
  //  printf("%d",value("589654",3,2));
}


