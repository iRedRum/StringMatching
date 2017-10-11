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
	LNP line=(LNP)malloc(sizeof(LNode)*PLMAX);
	//申请用来存放输出结构体的空间 
	int i=0;
	int lentemp;//读入的时候长度的暂存量
	
	for(i=0;i<PLMAX;i++)
	//初始化输出结构体 
	{
		line[i].flag=false;
		line[i].offset=NULL;
		line[i].len=0;
		line[i].num=0;
	}
	
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
			lentemp=line[linecount].len;
			line[linecount].key[lentemp]=0;
			//存放关键字的结尾'\0' 
			line[linecount].flag=true;
			//表示该节点进行了关键字的存储 
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
			lentemp=line[linecount].len++;
			line[linecount].key[lentemp]=a;
		}
		else
		//中文的处理方式，一次传入两个文件内的字符 
		{
			in[len]=a;
			lentemp=line[linecount].len++;
			line[linecount].key[lentemp]=a;
			a=fgetc(fp);
			in[len+1]=a;
			lentemp=line[linecount].len++;
			line[linecount].key[lentemp]=a;
		}
		len+=2;
		a=fgetc(fp);
	}
	
	//文本中的最后一个字符需要进行特殊处理 
	if(line[linecount].len!=0)
	//如果文本最后一个字符是回车符号，那么就不需要进行添加结束符号并且存储的步骤了 
	{
		in[len]='\0';
		lentemp=line[linecount].len;
		line[linecount].key[lentemp]=0;
		line[linecount].flag=true;
		add(in,root,len,linecount); 
	}
	fclose(fp);
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("建树运行时间：%f秒\n",theTimes);
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


	//在建好的三叉树上创建失效函数 
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
	printf("失效运行时间：%f秒\n",theTimes);
	st=et;
	
	
	FILE *rfp=fopen("string.txt","r");
	
	char buffer[BMAX]; 
	bool iscontinue=0;
	long long preoffset=0;
	char key[2];//每次从文件读入的一个字符 
	
	TSTp mp=root;//进行匹配的节点
	
	if(rfp==NULL)
	{
		printf("error.\n");
		return 0;
	}
	
	
	//进行文件字符串的匹配 
	
	int readi;//用来进行读入缓冲区的数组下标
	
	while(fgets(buffer,BMAX,rfp)!=NULL)
	{
		readi=0;//没进行一次缓冲区的读入，初始化一次下标 
		
		while(buffer[readi]!=0)
		{
			
			//从缓冲区进行需要进行匹配关键字的读取 
			
			a=buffer[readi];
			if(iscontinue)
			//临界的时候中文字符的特殊处理 
			{
				key[1]=a;
				iscontinue=false;
			}
			else
			{
				if(a==10)
				//字符是回车进行处理 
				{
					readi++;
					continue;
				}
				if(!(a>>7))
				//英文字符单个进行填充的处理 
				{
					key[0]=0x00;
					key[1]=a;
				}
				else
				//中文字符的处理 
				{
					key[0]=a;
					readi++;
					if(buffer[readi]==0)
					//如果这时候下一个刚好是边界了，需要跳出这个循环
					//进行下一个循环的读入，再进行拼凑 
					{
						iscontinue=true;
						continue;
					}
					a=buffer[readi];
					key[1]=a;
				}
			}
				
			readi++; 
			//指向缓冲区的下一个字符 
			
			
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
					ONP newonp=(ONP)malloc(sizeof(ONode));
					//申请一个新的进行缓冲存储的节点 
					newonp->offset=preoffset+readi;
					//设置新节点中存储的找到字符的偏移量 
					newonp->nextnode=line[mp->num].offset;
					//将输出的结构体头插法到输出链表中 
					line[mp->num].offset=newonp;
					line[mp->num].num++;
					//匹配的次数自增 
				} 
				
				np=Match(key,mp);
				//再将这个节点和失效节点的子节点进行匹配看看是否成功 
				
			} 
			
			if(np!=NULL)
			//该节点的子节点中有匹配的节点 
			{
				if(np->isEnd==1)
				{
					ONP newonp=(ONP)malloc(sizeof(ONode));
					//申请一个新的进行缓冲存储的节点 
					newonp->offset=preoffset+readi;
					//设置新节点中存储的找到字符的偏移量
					newonp->nextnode=line[np->num].offset;
					//将输出的结构体头插法到输出链表中
					line[np->num].offset=newonp;
					line[np->num].num++;
					//匹配的次数自增 
					//匹配的节点是关键字的结束的节点，输出相应数据到result里面 
				} 
				
				mp=np;
				//接下来进行下一个关键字的匹配了 	
			}
		}
		
		preoffset=ftell(rfp);
		//已经读入的文件大小，用来计算后面的偏移量 
		
	}
	
	fclose(rfp); 
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("查找运行时间：%f秒\n",theTimes);
	st=et;
	
	
	FILE *wfp=fopen("wtest.txt","w");
	for(i=1;i<PLMAX;i++)
	{
		if(!line[i].flag)
		//该节点是否有存放关键字 
		//这里担心关键字的文档存在断层，我们使用了continue 
			continue;
		fprintf(wfp,"%s %lld ",line[i].key,line[i].num);
		//输出关键字和出现的次数 
		ONP onptemp;
		for(onptemp=line[i].offset;onptemp!=NULL;onptemp=onptemp->nextnode)
		{
			fprintf(wfp,"%lld ",onptemp->offset);
			//循环输出出现在文件中的偏移量 
		}
		fprintf(wfp,"\n");
	}
	
	fclose(wfp);
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("输出运行时间：%f秒\n",theTimes);
	st=et;
	return 0;

}
