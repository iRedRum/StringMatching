#include <stdio.h>

int main()
{
	FILE * fp=NULL;
	char a='\0';
	int max=0;
	int count=0;
	int line=0;
	int maxline=0;
	fp=fopen("pattern.txt","r");
	if(fp==NULL)
	{
		printf("error.\n");
		return 0;
	}
	a=fgetc(fp);
	while(a!=EOF)
	{
		if(a==10)
		//���з��ţ���������ַ�
		//Ȼ�������ؼ��ִ��룬�������Ĺ��� 
		{
			if(count>max)
			{
				max=count;
				maxline=line;
			}
			count=0;
			line++;
		}
		else if(!(a>>7))
		//������һλ�ǲ���0������ǾͰ���Ӣ�ĵĽ��д��� 
		{
		
		}
		else
		//���ĵĴ���ʽ��һ�δ��������ļ��ڵ��ַ� 
		{
			a=fgetc(fp);
		}
		//printf("%x,%x\n",(unsigned char)in[len],(unsigned char)in[len+1]);
		count++;
		a=fgetc(fp);
	}
	printf("%d %d",max,maxline);
	
 } 
