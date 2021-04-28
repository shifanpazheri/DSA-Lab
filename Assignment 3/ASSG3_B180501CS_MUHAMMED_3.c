#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	char data[500];
	struct node* next;
};

int ischar(char c)
{
	if((c>=65&&c<=90)||(c>=97&&c<=122))
	{
		return 1;
	}
	else return 0;
}

struct node* getnode(char s[])
{
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	strcpy(temp->data,s);
	temp->next=NULL;
	return temp;
}

struct node* insert(struct node* head,char s[])
{
	struct node*p=head;
	while(p!=NULL)
	{
		if(!strcmp(p->data,s))
		{
			return head;
		}
		p=p->next;
	}
	//printf("%s ",s);
	struct node* temp=getnode(s);
	if(head==NULL)
		head=temp;
	else
	{
		struct node* p =head;
		while(p->next!=NULL)
			p=p->next;
		p->next=temp;
	}
	return head;
}

void print(struct node* head)
{
	if(head==NULL)  printf("NULL");
	else
	{
	struct node*p=head;
	while(p!=NULL)
	{
		printf("%s ",p->data);
		p=p->next;
	}
	}
	printf("\n");
}

int main()
{
        struct node* try=NULL;
	int n;
	scanf("%d",&n);
	struct node* head[n];
	for(int i=0;i<n;i++)
	{
		head[i]=NULL;
	}
	char str[999];
	scanf(" %[^\n]s",str);//space is imp before %
	char temp[500];
//	char free[500];
	int k=0;
	for(int i=0;i<strlen(str);i++)
	{
	//	printf("%s\n",temp);
		if(ischar(str[i]))
		{
		temp[k++]=str[i];	
		}
		else if(str[i]==' '||str[i]=='.')
		{
			temp[k]='\0';
			head[k%n]=insert(head[k%n],temp);
		//	strcpy(temp,"");
	//		printf("string empty=%s\n",temp);
			k=0;
		}
	}
	for(int i=0;i<n;i++)
	        print(head[i]);
}
