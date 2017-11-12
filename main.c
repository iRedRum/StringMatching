#include "typedefine.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//���ڵ��nextNode��NULL,parentNode��NULL 
//int argc, char *argv[]
int main(int argc, char **argv)
{
	//�ļ������� 
	char *tfilename="string_l.txt";		//ƥ���ı��� 
	char *pfilename="pattern_l.txt";	//ģʽ���ı��� 
	char *wfilename="result.txt";		//����ı��� 
	if(argc == 4)
	{
		tfilename=argv[1];
		pfilename=argv[2];
		wfilename=argv[3];
	}
	 
	TSTp root=(TSTp)malloc(sizeof(TSTNode));//���������ڵ� 
	LNP line=(LNP)malloc(sizeof(LNode)*PLMAX);
	//���������������ṹ��Ŀռ�
	memset(line,0,sizeof(LNode)*PLMAX);
	memset(root,0,sizeof(TSTNode));
	
	//����pattern�ĵ������ַ�����������trie�� 
	FILE *pfp=fopen(pfilename,"r");
	
	if(pfp==NULL)
	{
		printf("error.\n");
		return 0;
	}
	
	char in[wMAX]={'\0'};//��Ҫ���в���Ĺؼ���
	int len=0;	//�ؼ��������Ѵ�������Ŀ
	int linecount=1; //��¼�ؼ������ı��ļ��еĵڼ��� 
	char a='\0';//��ʱ�洢 
	int lentemp;//�����ʱ�򳤶ȵ��ݴ���
	
	a=fgetc(pfp);
	len=0;
	while(a!=EOF)
	{
		if(a==10)
		//���з��ţ���������ַ�
		//Ȼ�������ؼ��ִ��룬�������Ĺ��� 
		{
			in[len]='\0';
			lentemp=line[linecount].len;
			line[linecount].key[lentemp]=0;
			//��Źؼ��ֵĽ�β'\0' 
			line[linecount].flag=true;
			//��ʾ�ýڵ�����˹ؼ��ֵĴ洢 
			add(in,root,len,linecount);
			len=0;//�������³�ʼ��Ϊ0 
			linecount++;//�ؼ��ֵ��������е��� 
			a=fgetc(pfp);//������һ����Ҫ�����жϵ��ַ� 
			continue;
		}
		else if(!(a>>7))
		//������һλ�ǲ���0������ǾͰ���Ӣ�ĵĽ��д��� 
		{
			in[len]=0x00;
			in[len+1]=a;
			lentemp=line[linecount].len++;
			line[linecount].key[lentemp]=a;
		}
		else
		//���ĵĴ���ʽ��һ�δ��������ļ��ڵ��ַ� 
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
	
	//�ı��е����һ���ַ���Ҫ�������⴦�� 
	if(line[linecount].len!=0)
	//����ı����һ���ַ��ǻس����ţ���ô�Ͳ���Ҫ������ӽ������Ų��Ҵ洢�Ĳ����� 
	{
		in[len]='\0';
		lentemp=line[linecount].len;
		line[linecount].key[lentemp]=0;
		line[linecount].flag=true;
		add(in,root,len,linecount); 
	}
	fclose(pfp);

	//Ϊ����trie������ʧЧ������ָ�� 
	pStack ps=(pStack)malloc(sizeof(Stack));
	InitStack(ps);
	//�����ڵ㣬Ҳ���ǵ�0���ѹ��ջ�� 
	Push(ps,root);
	//���������е�һ��Ľڵ� 
	pStack hps=Traverse(ps);

	//�ڽ��õ��������ϴ���ʧЧ���� 
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
	
	//�����ļ��ַ�����ƥ�� 
	FILE *rfp=fopen(tfilename,"r");	//ƥ���ļ�ָ�� 
	FILE *wfp=fopen(wfilename,"w");	//����ļ�ָ�� 
	
	if(rfp==NULL||wfp==NULL)
	{
		printf("error.\n");
		return 0;
	}	
	
	char buffer[BMAX];//�������ı�����ƥ��Ļ����� 
	bool iscontinue=0;	//���������ٽ������2�ֽ������ַ������������������� 
	long long preoffset=0;	//֮ǰ����ȡ�Ļ�������ƫ���� 
	char key[2];//ÿ�δ��ļ���������Ļ�Ӣ���ַ�������2�ֽڴ��� 
	int readi;//�������ж��뻺�����������±�
	int buflen=0;//������¼�Ѿ�ʹ�õĻ�������Ŀ
	TSTp mp=root;//����ƥ��Ľڵ�
	
	while(fgets(buffer,BMAX,rfp)!=NULL)
	{
		readi=0;//û����һ�λ������Ķ��룬��ʼ��һ���±� 
		
		while(buffer[readi]!=0)
		{
			//�ӻ�����������Ҫ����ƥ��ؼ��ֵĶ�ȡ 
			a=buffer[readi];
			if(iscontinue)
			//�ٽ��ʱ�������ַ������⴦�� 
			{
				key[1]=a;
				iscontinue=false;
			}
			else
			{
				if(!(a>>7))
				//Ӣ���ַ������������Ĵ��� 
				{
					key[0]=0x00;
					key[1]=a;
				}
				else
				//�����ַ��Ĵ��� 
				{
					key[0]=a;
					readi++;
					if(buffer[readi]==0)
					//�����ʱ����һ���պ��Ǳ߽��ˣ���Ҫ�������ѭ��
					//������һ��ѭ���Ķ��룬�ٽ���ƴ�� 
					{
						iscontinue=true;
						continue;
					}
					a=buffer[readi];
					key[1]=a;
				}
			}//�ַ���ȡ���� 
			
			readi++; 
			//ָ�򻺳�������һ���ַ� 
			TSTp np=Match(key,mp);
			//���ؼ��ֺ�ƥ��Ľڵ���ӽڵ�ƥ�䣬�Ƿ�����ƥ��Ľڵ�
			//�У����ظ��ӽڵ㣬û�У�����NULL 
			
			while(np==NULL)
			//���ƥ������ƥ�䵽�����Ҳ�Ǹ��ڵ� 
			//����ڵ���ӽڵ�û��ƥ��Ľڵ㣬Ӧ��ȥ������ڵ��ʧЧ�ڵ��� 
			{
				mp=mp->nextNode;
				np=Match(key,mp);
				//�ٽ�����ڵ��ʧЧ�ڵ���ӽڵ����ƥ�俴���Ƿ�ɹ�
			}
			
			if(np!=NULL)
			//�ýڵ���ӽڵ�����ƥ��Ľڵ� 
			{
				if(np->isEnd==1)	
				//�ýڵ�Ϊ�ؼ�����ֹ�ڵ� 
				//����ùؼ��� 
				{ 
					long long int offsettemp=preoffset+readi-line[np->num].len;
					fprintf(wfp,"%s %lld\n",line[np->num].key,offsettemp);
				}
				TSTp ftemp=np;
				while(ftemp->FisEnd)
				//��ʧЧ��������йؼ�����ֹ��� 
				{
					int Fnum=ftemp->Fnum;
					if(Fnum==-1)
					//�ý�����ֹ��㣬������ǰ��ʧЧ�ڵ�����������ֹ��� 
					{
						ftemp=ftemp->nextNode;
						continue;
					}
					//���ʧЧ�ڵ����еĹؼ��� 
					long long int offsettemp=preoffset+readi-line[Fnum].len;
					fprintf(wfp,"%s %lld\n",line[Fnum].key,offsettemp);
					
					ftemp=ftemp->nextNode;//ѭ��
				}
				mp=np;
				//������������һ���ؼ��ֵ�ƥ���� 	
			}
		}
		preoffset=ftell(rfp);
		//�Ѿ�������ļ���С��������������ƫ���� 
	}
	fclose(rfp); 
	fclose(wfp);

	return 0;

}

