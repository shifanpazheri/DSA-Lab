#include<stdio.h>
#include<string.h>

int main()
{
	int t;
	scanf("%d",&t);
	for(int k=0;k<t;k++)
	{
		char pattern[999];
		char string[9999];
		scanf(" %s",pattern);
		scanf(" %s",string);
		int a[26],b[26],count=0;
		for(int i=0;i<26;i++)
			a[i]=0;
		for(int i=0;i<strlen(pattern);i++)
			a[(pattern[i])-97]++;
		for(int p=0;p<strlen(string)-3;p++)
		{
			for(int i=0;i<26;i++)
                                b[i]=0;
			for(int q=p;q<p+strlen(pattern);q++)
			{
                                b[(string[q])-97]++;
			}
			for(int i=0;i<26;i++)
			{
				if(a[i]==b[i])
					count++;
			}
			if(count==26)
			{
				count=0;
				printf("YES\n");
				break;
			}
			else
				count=0;
			if(p==strlen(string)-4)
				 printf("NO\n");
			
		}
	}
}
