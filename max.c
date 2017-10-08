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
		//换行符号，插入结束字符
		//然后把这个关键字传入，进行树的构建 
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
		//看看第一位是不是0，如果是就按照英文的进行处理 
		{
		
		}
		else
		//中文的处理方式，一次传入两个文件内的字符 
		{
			a=fgetc(fp);
		}
		//printf("%x,%x\n",(unsigned char)in[len],(unsigned char)in[len+1]);
		count++;
		a=fgetc(fp);
	}
	printf("%d %d",max,maxline);
	
 } 
