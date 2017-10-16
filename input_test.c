#include<stdio.h>

int main()
{
	//测试char[2]转换成short类型 
	FILE *fp=NULL;
	fp=fopen("2.txt","r");
	short i1,i2;
	char c=fgetc(fp);
	i1=(short)c&0x00FF;
	printf("%x\n",i1);
	c=fgetc(fp);
	i2=(short)c;
	printf("%x\n",i2);
	i2=i2<<8;
	printf("%x\n",i2);
	i2=i1|i2;
	printf("%d\n",sizeof(short));
	printf("%x",i2);
}
