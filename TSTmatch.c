#include "typedefine.h"

TSTp add(char* key,TSTp root,int length,int linecount)
{
	int charIndex=0;
	TSTp curp=root;
	int isSame=0;
	
	if(key[charIndex+1]=='\0')
	//��ʾ��ֱ�Ӿ��ǿ��ַ��Ľ��������ڵ���Խ���ƥ�� 
		root->isEnd=1; 

	if(curp->midNode!=NULL)
	{
		curp=curp->midNode;
	}
		
	while(1)
	//һֱ����ѭ����ֱ���ؼ��ֶ�����Ϊֹ 
	{
		isSame=0;
		
		if((curp->c[0]==key[charIndex]
		&&curp->c[1]==key[charIndex+1])) 
			isSame=1;
		
		if(curp->c[0]==0&&curp->c[1]==0)
		//�Ը��ڵ�Ҫ�������⴦��һ�� 
		{
			TSTp newp=(TSTp)malloc(sizeof(TSTNode));
			 //û���µĽڵ���ô����һ���µĽڵ㣬�����Ƚ�
			memset(newp,0,sizeof(TSTNode));	
			//��ʼ���µĽڵ�
				
			newp->c[0]=key[charIndex];
			newp->c[1]=key[charIndex+1];
			//�µĽڵ��ֵӦ��ֱ�Ӹ��裬��Ϊ��һ���ǿյģ��൱�ڴ����µ����� 
				
			curp->midNode=newp;
			//�ӽڵ�ָ���µĽڵ� 
				
			curp->midNode->parentNode=curp;
			//�ӽڵ�ĸ��ڵ�ָ�򱾽ڵ� 
	
			curp=curp->midNode; 
			//��һ���ڵ�ָ���ӽڵ� 
			
			continue;
		}
		if(isSame)
		{
			charIndex+=2;
			//ƥ��ɹ���ؼ��ֵ�λ��Ӧ���ƶ���λ 
	 
			if(charIndex==length)
			{
				curp->isEnd=1;
				curp->num=linecount;
				//�ؼ����Ѿ���������Ӧ���������Ա�־�Ѿ����� 
				return root; 
			}
			//����²���ؼ��ֲ����ˣ���ôֱ�ӷ��� 
			
			if(curp->midNode==NULL)
			{
				TSTp newp=(TSTp)malloc(sizeof(TSTNode));
				 //û���µĽڵ���ô����һ���µĽڵ㣬�����Ƚ�
				
				memset(newp,0,sizeof(TSTNode));
				//��ʼ���µĽڵ�
				
				newp->c[0]=key[charIndex];
				newp->c[1]=key[charIndex+1];
				//�µĽڵ��ֵӦ��ֱ�Ӹ��裬��Ϊ��һ���ǿյģ��൱�ڴ����µ����� 
				
				curp->midNode=newp;
				//�ӽڵ�ָ���µĽڵ� 
				
				curp->midNode->parentNode=curp;
				//�ӽڵ�ĸ��ڵ�ָ�򱾽ڵ� 	
			}
			
			//��������ӽڵ㣬Ҳ����midnode���ǿյģ���ô���ǾͲ���Ҫ���д�������������ƥ�� 
		
			curp=curp->midNode; 
			//��һ���ڵ�ָ���ӽڵ� 
		}
		else if(curp->c[0]<key[charIndex]
		||(curp->c[0]==key[charIndex]&&curp->c[1]<key[charIndex+1]))
		//�ж�ֵ�Ĵ�С��С�Ļ���������ƥ�� 
		{
			if(curp->leftNode==NULL)
			{
				TSTp newp=(TSTp)malloc(sizeof(TSTNode));
				 //û���µĽڵ���ô����һ���µĽڵ㣬�����Ƚ�
				
				memset(newp,0,sizeof(TSTNode));
				//��ʼ���µĽڵ�
				
				newp->c[0]=key[charIndex];
				newp->c[1]=key[charIndex+1];
				//�µĽڵ��ֵӦ��ֱ�Ӹ��裬��Ϊ��һ���ǿյģ��൱�ڴ����µ����� 
				
				curp->leftNode=newp;
				//��ڵ�ָ���µĽڵ� 
				
				curp->leftNode->parentNode=curp->parentNode;
				//�ֵܽڵ�ĸ��ڵ�ָ���Լ��ڵ�ĸ��ڵ� 
			}
			
			//���������ڵ�leftnode���ǿյģ���ô���ǾͲ���Ҫ���д������������±Ƚϣ������ܲ���ƥ�� 
			//ע�⣬���ﲻ�öԹؼ��ֵ�ƫ���������޸��� 
			
			curp=curp->leftNode;
			//��һ���ڵ�ָ����ڵ� 
		}
		else 
		//�ж�ֵ�Ĵ�С����Ļ���������ƥ�� 
		{
			if(curp->rightNode==NULL)
			{
				TSTp newp=(TSTp)malloc(sizeof(TSTNode));
				 //û���µĽڵ���ô����һ���µĽڵ㣬�����Ƚ�
				memset(newp,0,sizeof(TSTNode));
				//��ʼ���µĽڵ�
				
				newp->c[0]=key[charIndex];
				newp->c[1]=key[charIndex+1];
				//�µĽڵ��ֵӦ��ֱ�Ӹ��裬��Ϊ��һ���ǿյģ��൱�ڴ����µ����� 
				
				curp->rightNode=newp;
				//�ҽڵ�ָ���µĽڵ�
				
				curp->rightNode->parentNode=curp->parentNode;
				//�ֵܽڵ�ĸ��ڵ�ָ���Լ��ڵ�ĸ��ڵ� 		
			}
			
			//��������ҽڵ�rightnode���ǿյģ���ô���ǾͲ���Ҫ���д������������±Ƚϣ������ܲ���ƥ�� 
			//ע�⣬���ﲻ�öԹؼ��ֵ�ƫ���������޸��� 	
			
			curp=curp->rightNode; 
			//��һ���ڵ�ָ���ҽڵ� 		
		}	
	}	
 } 
 
pStack Traverse(pStack ps)
//�������һ��ڵ��ջ 
{
	pStack new_ps=(pStack)malloc(sizeof(Stack));
	//����һ���µ�ջ��ָ�룬�����洢��Ҫ���ص��µ�һ������нڵ�
	
	pStack t_ps=(pStack)malloc(sizeof(Stack)); 
	//����һ���µ�ջ���������� 
	
	InitStack(new_ps);
	InitStack(t_ps);
	//��ʼ������ջ 
	
	while(!Empty(ps))
	//���������е�һ��Ľڵ����һ��Ľڵ� 
	{
		TSTp p=NULL;
		
		p=Pop(ps);
		//����һ��Ľڵ��ջ�ﵯ����һ��Ľڵ㣬��������һ��Ľڵ� 

		if(p->midNode!=NULL)
		{
			Push(t_ps,p->midNode);
		}
		while(!Empty(t_ps))
		//������ѹ�������ڵ��������һ��Ľڵ� 
		{
			p=Pop(t_ps);
			//ֻ����������ջ�Ľڵ� 
			
			Push(new_ps,p);

			if(p->leftNode!=NULL)
			{
				Push(t_ps,p->leftNode);
			}
			//��������Ľڵ����ڵ㲻�ǿյĻ���Ҫѹ��ջ�� 
			
			if(p->rightNode!=NULL)
			{
				Push(t_ps,p->rightNode);
			}
			//��������Ľڵ���ҽڵ㲻�ǿյĻ���Ҫѹ��ջ�� 	
		}
	 } 
	 return new_ps;
	 //��ֻ����һ��ڵ��ջ��ָ�뷵�� 
}
 
TSTp Match(char* key,TSTp root)
//�ýڵ��Ƿ���root���ӽڵ�ƥ�� 
{
	if(key==NULL)
		return NULL;
		
	TSTp curp=root->midNode;
	
	while(1)
	{
		if(curp==NULL&&root->nextNode==NULL)
		//����Ǹ��ڵ�ƥ�䣬��ô����ڵ��ʧЧ�ڵ�ָ��ľ��Ǹ��ڵ� 
			return root;
		else if(curp==NULL)
			return NULL;
		
		if(curp->c[0]==key[0]
		&&curp->c[1]==key[1])
			return 	curp;
		else if(curp->c[0]<key[0]
		||(curp->c[0]==key[0]&&curp->c[1]<key[1]))
			curp=curp->leftNode;
		else
			curp=curp->rightNode;
	}
 } 


void  Failure(pStack ps)
//����ʧЧ���� 
{
	TSTp p=NULL;
	
	while(!Empty(ps))
	{
		p=Pop(ps);
		//���ε�������Ĳ�Ľڵ�
		
		int isMatch=0;
		//�Ƿ��Ѿ�ƥ�䵽����Ӧ��ʧЧת���ڵ� 
			
		if(p->parentNode->nextNode==NULL)
		//��������Ϊ1�Ľڵ㣬��ô��ʧЧ�ڵ���Ǹ��ڵ� 
			p->nextNode=p->parentNode;
		else
		{	
			TSTp curp=p->parentNode->nextNode;
			//��Ҫ����ƥ��ʧЧ�ڵ�Ľڵ�
				 
			while(!isMatch)
			{
					
				TSTp mp=Match(p->c,curp);
				if(mp!=NULL)
				{
					p->nextNode=mp;
					if(mp->isEnd==1)	//��ʧЧ�ڵ�Ϊ��ֹ��� 
					{
						p->FisEnd=1;
						p->Fnum=mp->num;
					}
					else if(mp->FisEnd==1)	//��ʧЧ�ڵ��ǰ��ʧЧ�ڵ���������ֹ��� 
					{
						p->FisEnd=1;
						p->Fnum=-1; 
					}
					isMatch=1;
				}
				else
				{
					curp=curp->nextNode;
					//�������ƥ������ڵ��ʧЧ�ڵ���ӽڵ�	
				}
			}
		}
	}
}
