#include "typedefine.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//���ڵ��nextNode��NULL,parentNode��NULL 
//int argc, char *argv[]
int main()
{
	//����pattern�ĵ������ַ�����������trie�� 
	clock_t st=clock();//����ʼ��ʱ�� 
	clock_t et=0;//���������ʱ�� 
	double theTimes=0;//ʹ��ʱ�� 
	TSTp root=(TSTp)malloc(sizeof(TSTNode));//��Ҫ���в���ĸ��ڵ� 
	char a='\0';//��ʱ�洢 
	char in[wMAX]={'\0'};//��Ҫ���в���Ĺؼ���
	int len=0;	//�ؼ��������Ѵ�������Ŀ
	int linecount=1; //��¼�ؼ������ı��ļ��еĵڼ��� 
	FILE *fp=NULL;	//�ļ�ָ�� 

	
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
		//���з��ţ���������ַ�
		//Ȼ�������ؼ��ִ��룬�������Ĺ��� 
		{
			in[len]='\0';
			add(in,root,len,linecount);
			len=0;//�������³�ʼ��Ϊ0 
			linecount++;//�ؼ��ֵ��������е��� 
			a=fgetc(fp);//������һ����Ҫ�����жϵ��ַ� 
			continue;
		}
		else if(!(a>>7))
		//������һλ�ǲ���0������ǾͰ���Ӣ�ĵĽ��д��� 
		{
			in[len]=0x00;
			in[len+1]=a;
		}
		else
		//���ĵĴ���ʽ��һ�δ��������ļ��ڵ��ַ� 
		{
			in[len]=a;
			a=fgetc(fp);
			in[len+1]=a;
		}
		len+=2;
		a=fgetc(fp);
	}
	
	//�ı��е����һ���ַ���Ҫ�������⴦�� 
	in[len]='\0';
	
	add(in,root,len,linecount); 
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("����ʱ�䣺%f��\n",theTimes);
	st=et;
	
	//DLR(root);
	//MLR(root);

	
	
	//Ϊ����trie������ʧЧ������ָ�� 
	pStack ps=(pStack)malloc(sizeof(Stack));
	InitStack(ps);
	//�����ڵ㣬Ҳ���ǵ�0���ѹ��ջ�� 
	Push(ps,root);
	//���������е�һ��Ľڵ� 
	pStack hps=Traverse(ps);

	//printf("%d",max);
    //unsigned long line[2000000];
    long long * line=(long long *)malloc(sizeof(long long)*PLMAX); 
    
    int i=0;
    for(i=0;i<PLMAX;i++)
    	line[i]=-1;
	
	
	
	while(!Empty(hps))
	{
		//�����������ĸ߲�Ľڵ㱣����ײ�ڵ��ջ�������һ�εı��� 
		pStack lps=Copy(hps);
		
		//ʧЧ�����Ĵ��� 
		Failure(hps);
		
		//TraverseStack(lps);
		
		//���������е���һ��Ľڵ� 
		hps=Traverse(lps);
		
	}
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("����ʱ�䣺%f��\n",theTimes);
	st=et;
	
	
	FILE *rfp=fopen("string.txt","r");
	
	char key[2];//ÿ�δ��ļ������һ���ַ� 
	
	TSTp mp=root;//����ƥ��Ľڵ�
	
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
		//���ؼ��ֺ�ƥ��Ľڵ���ӽڵ�ƥ�䣬�Ƿ�����ƥ��Ľڵ�
		//�У����ظ��ӽڵ㣬û�У�����NULL 
		
		while(np==NULL)
		//���ƥ������ƥ�䵽�����Ҳ�Ǹ��ڵ� 
		//����ڵ���ӽڵ�û��ƥ��Ľڵ㣬Ӧ��ȥ������ڵ��ʧЧ�ڵ��� 
		{
		
			mp=mp->nextNode;
			//��������ڵ��ʧЧ�ڵ��ƥ�� 
		
			if(mp->isEnd==1)
			//�ж�mp�Ƿ���һ���ؼ��ֵĽ����ڵ� 
			{
				if(line[mp->num]==-1) 
					line[mp->num]=ftell(rfp);
				//���������result�ļ���
				
			} 
			
			np=Match(key,mp);
			//�ٽ�����ڵ��ʧЧ�ڵ���ӽڵ����ƥ�俴���Ƿ�ɹ� 
			
		} 
		
		if(np!=NULL)
		//�ýڵ���ӽڵ�����ƥ��Ľڵ� 
		{
			if(np->isEnd==1)
			{
				if(line[np->num]==-1)
					line[np->num]=ftell(rfp);
				//printf("%ld",ftell(rfp));
				//ƥ��Ľڵ��ǹؼ��ֵĽ����Ľڵ㣬�����Ӧ���ݵ�result���� 
			} 
			
			mp=np;
			//������������һ���ؼ��ֵ�ƥ���� 	
		}
		
		a=fgetc(rfp);
		
	}
	fclose(rfp);
	
	et=clock();
	theTimes=(double)((et-st)/CLOCKS_PER_SEC);
	printf("����ʱ�䣺%f��\n",theTimes);
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
	printf("����ʱ�䣺%f��\n",theTimes);
	st=et;
	
	return 0;

}
