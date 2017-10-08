#include "typedefine.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//根节点的nextNode是NULL,parentNode是NULL 
//int argc, char *argv[]
int main()
{
	//读入pattern文档进行字符串构建三叉trie树 
	clock_t st=clock();//程序开始的时间 
	clock_t et=0;//程序结束的时间 
	double theTimes=0;//使用时间 
	TSTp root=(TSTp)malloc(sizeof(TSTNode));//需要进行插入的根节点 
	char a='\0';//临时存储 
	char in[wMAX]={'\0'};//需要进行插入的关键字
	int len=0;	//关键字数组已存入字数目
	int linecount=1; //记录关键字在文本文件中的第几行 
	FILE *fp=NULL;	//文件指针 

	
	fp=fopen("pattern.txt","r");
	init(root);
	if(fp==NULL)
	{
		printf("error.\n");
		return 0;
	}
	a=fgetc(fp);
	len=0;
	while(a!=EOF)
	{
		if(a==10)
		//换行符号，插入结束字符
		//然后把这个关键字传入，进行树的构建 
		{
			in[len]='\0';
			add(in,root,len,linecount);
			len=0;//长度重新初始化为0 
			linecount++;//关键字的行数进行递增 
			a=fgetc(fp);//读入下一个需要进行判断的字符 
			continue;
		}
		else if(!(a>>7))
		//看看第一位是不是0，如果是就按照英文的进行处理 
		{
			in[len]=0x00;
			in[len+1]=a;
		}
		else
		//中文的处理方式，一次传入两个文件内的字符 
		{
			in[len]=a;
			a=fgetc(fp);
			in[len+1]=a;
		}
		len+=2;
		a=fgetc(fp);
	}
	
	//文本中的最后一个字符需要进行特殊处理 
	in[len]='\0';
	
	add(in,root,len,linecount); 
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("运行时间：%f秒\n",theTimes);
	st=et;
	
	//DLR(root);
	//MLR(root);

	
	
	//为三叉trie树创建失效函数的指针 
	pStack ps=(pStack)malloc(sizeof(Stack));
	InitStack(ps);
	//将根节点，也就是第0层的压入栈里 
	Push(ps,root);
	//遍历出所有第一层的节点 
	pStack hps=Traverse(ps);

	//printf("%d",max);
    //unsigned long line[2000000];
    long long * line=(long long *)malloc(sizeof(long long)*PLMAX); 
    
    int i=0;
    for(i=0;i<PLMAX;i++)
    	line[i]=-1;
	
	
	
	while(!Empty(hps))
	{
		//将遍历出来的高层的节点保存进底层节点的栈里，进行下一次的遍历 
		pStack lps=Copy(hps);
		
		//失效函数的创建 
		Failure(hps);
		
		//TraverseStack(lps);
		
		//遍历出所有的下一层的节点 
		hps=Traverse(lps);
		
	}
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("运行时间：%f秒\n",theTimes);
	st=et;
	
	
	FILE *rfp=fopen("string.txt","r");
	
	char key[2];//每次从文件读入的一个字符 
	
	TSTp mp=root;//进行匹配的节点
	
	if(rfp==NULL)
	{
		printf("error.\n");
		return 0;
	}
	a=fgetc(rfp);
	while(a!=EOF)
	{
		if(a==10)
		{
			a=fgetc(rfp);
		}
		if(!(a>>7))
		{
			key[0]=0x00;
			key[1]=a;
		}
		else
		{
			key[0]=a;
			a=fgetc(rfp);
			key[1]=a;
		}
		
		TSTp np=Match(key,mp);
		//将关键字和匹配的节点的子节点匹配，是否有相匹配的节点
		//有，返回该子节点，没有，返回NULL 
		
		while(np==NULL)
		//这个匹配总能匹配到，最次也是根节点 
		//这个节点的子节点没有匹配的节点，应该去看这个节点的失效节点了 
		{
		
			mp=mp->nextNode;
			//进行这个节点的失效节点的匹配 
		
			if(mp->isEnd==1)
			//判断mp是否是一个关键字的结束节点 
			{
				if(line[mp->num]==-1) 
					line[mp->num]=ftell(rfp);
				//进行输出到result文件上
				
			} 
			
			np=Match(key,mp);
			//再将这个节点和失效节点的子节点进行匹配看看是否成功 
			
		} 
		
		if(np!=NULL)
		//该节点的子节点中有匹配的节点 
		{
			if(np->isEnd==1)
			{
				if(line[np->num]==-1)
					line[np->num]=ftell(rfp);
				//printf("%ld",ftell(rfp));
				//匹配的节点是关键字的结束的节点，输出相应数据到result里面 
			} 
			
			mp=np;
			//接下来进行下一个关键字的匹配了 	
		}
		
		a=fgetc(rfp);
		
	}
	fclose(rfp);
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("运行时间：%f秒\n",theTimes);
	st=et;
	
	
	FILE *wfp=fopen("wtest.txt","w");
	fseek(fp,0,SEEK_SET);
	char akey[wMAX];
	long midnum=0; 
	for(i=1;i<PLMAX;i++)
	{
		fgets(akey,wMAX,fp);
		akey[ftell(fp)-midnum-2]='\0';
		midnum=ftell(fp);
		fprintf(wfp,"%s\t%10ld\n",akey,line[i]);
	}
	fclose(wfp);
	fclose(fp);
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("运行时间：%f秒\n",theTimes);
	st=et;
	
	return 0;

}
