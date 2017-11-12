#include "typedefine.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//根节点的nextNode是NULL,parentNode是NULL 
//int argc, char *argv[]
int main(int argc, char **argv)
{
	//文件名变量 
	char *tfilename="string_l.txt";		//匹配文本名 
	char *pfilename="pattern_l.txt";	//模式串文本名 
	char *wfilename="result.txt";		//输出文本名 
	if(argc == 4)
	{
		tfilename=argv[1];
		pfilename=argv[2];
		wfilename=argv[3];
	}
	 
	TSTp root=(TSTp)malloc(sizeof(TSTNode));//三叉树根节点 
	LNP line=(LNP)malloc(sizeof(LNode)*PLMAX);
	//申请用来存放输出结构体的空间
	memset(line,0,sizeof(LNode)*PLMAX);
	memset(root,0,sizeof(TSTNode));
	
	//读入pattern文档进行字符串构建三叉trie树 
	FILE *pfp=fopen(pfilename,"r");
	
	if(pfp==NULL)
	{
		printf("error.\n");
		return 0;
	}
	
	char in[wMAX]={'\0'};//需要进行插入的关键字
	int len=0;	//关键字数组已存入字数目
	int linecount=1; //记录关键字在文本文件中的第几行 
	char a='\0';//临时存储 
	int lentemp;//读入的时候长度的暂存量
	
	a=fgetc(pfp);
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
			a=fgetc(pfp);//读入下一个需要进行判断的字符 
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
			a=fgetc(pfp);
			in[len+1]=a;
			lentemp=line[linecount].len++;
			line[linecount].key[lentemp]=a;
		}
		len+=2;
		a=fgetc(pfp);
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
	fclose(pfp);

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
	
	//进行文件字符串的匹配 
	FILE *rfp=fopen(tfilename,"r");	//匹配文件指针 
	FILE *wfp=fopen(wfilename,"w");	//输出文件指针 
	
	if(rfp==NULL||wfp==NULL)
	{
		printf("error.\n");
		return 0;
	}	
	
	char buffer[BMAX];//用来做文本读入匹配的缓冲区 
	bool iscontinue=0;	//处理缓冲区临界情况（2字节中文字符被分在两个缓冲区） 
	long long preoffset=0;	//之前所读取的缓冲区总偏移量 
	char key[2];//每次从文件读入的中文或英文字符（都按2字节处理） 
	int readi;//用来进行读入缓冲区的数组下标
	int buflen=0;//用来记录已经使用的缓冲区数目
	TSTp mp=root;//进行匹配的节点
	
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
			}//字符读取结束 
			
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
				np=Match(key,mp);
				//再将这个节点和失效节点的子节点进行匹配看看是否成功
			}
			
			if(np!=NULL)
			//该节点的子节点中有匹配的节点 
			{
				if(np->isEnd==1)	
				//该节点为关键字终止节点 
				//输出该关键字 
				{ 
					long long int offsettemp=preoffset+readi-line[np->num].len;
					fprintf(wfp,"%s %lld\n",line[np->num].key,offsettemp);
				}
				TSTp ftemp=np;
				while(ftemp->FisEnd)
				//其失效结点链中有关键字终止结点 
				{
					int Fnum=ftemp->Fnum;
					if(Fnum==-1)
					//该结点非终止结点，但是其前置失效节点链中仍有终止结点 
					{
						ftemp=ftemp->nextNode;
						continue;
					}
					//输出失效节点链中的关键字 
					long long int offsettemp=preoffset+readi-line[Fnum].len;
					fprintf(wfp,"%s %lld\n",line[Fnum].key,offsettemp);
					
					ftemp=ftemp->nextNode;//循环
				}
				mp=np;
				//接下来进行下一个关键字的匹配了 	
			}
		}
		preoffset=ftell(rfp);
		//已经读入的文件大小，用来计算后面的偏移量 
	}
	fclose(rfp); 
	fclose(wfp);

	return 0;

}

