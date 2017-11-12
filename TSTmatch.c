#include "typedefine.h"

TSTp add(char* key,TSTp root,int length,int linecount)
{
	int charIndex=0;
	TSTp curp=root;
	int isSame=0;
	
	if(key[charIndex+1]=='\0')
	//表示有直接就是空字符的进来，根节点可以进行匹配 
		root->isEnd=1; 

	if(curp->midNode!=NULL)
	{
		curp=curp->midNode;
	}
		
	while(1)
	//一直进行循环，直到关键字都查完为止 
	{
		isSame=0;
		
		if((curp->c[0]==key[charIndex]
		&&curp->c[1]==key[charIndex+1])) 
			isSame=1;
		
		if(curp->c[0]==0&&curp->c[1]==0)
		//对根节点要进行特殊处理一次 
		{
			TSTp newp=(TSTp)malloc(sizeof(TSTNode));
			 //没有新的节点那么申请一个新的节点，继续比较
			memset(newp,0,sizeof(TSTNode));	
			//初始化新的节点
				
			newp->c[0]=key[charIndex];
			newp->c[1]=key[charIndex+1];
			//新的节点的值应该直接赋予，因为下一个是空的，相当于创建新的子树 
				
			curp->midNode=newp;
			//子节点指向新的节点 
				
			curp->midNode->parentNode=curp;
			//子节点的父节点指向本节点 
	
			curp=curp->midNode; 
			//下一个节点指向子节点 
			
			continue;
		}
		if(isSame)
		{
			charIndex+=2;
			//匹配成功后关键字的位移应该移动两位 
	 
			if(charIndex==length)
			{
				curp->isEnd=1;
				curp->num=linecount;
				//关键字已经生成了相应的树，所以标志已经结束 
				return root; 
			}
			//如果新插入关键字查完了，那么直接返回 
			
			if(curp->midNode==NULL)
			{
				TSTp newp=(TSTp)malloc(sizeof(TSTNode));
				 //没有新的节点那么申请一个新的节点，继续比较
				
				memset(newp,0,sizeof(TSTNode));
				//初始化新的节点
				
				newp->c[0]=key[charIndex];
				newp->c[1]=key[charIndex+1];
				//新的节点的值应该直接赋予，因为下一个是空的，相当于创建新的子树 
				
				curp->midNode=newp;
				//子节点指向新的节点 
				
				curp->midNode->parentNode=curp;
				//子节点的父节点指向本节点 	
			}
			
			//如果他的子节点，也就是midnode不是空的，那么我们就不需要进行创建，继续往下匹配 
		
			curp=curp->midNode; 
			//下一个节点指向子节点 
		}
		else if(curp->c[0]<key[charIndex]
		||(curp->c[0]==key[charIndex]&&curp->c[1]<key[charIndex+1]))
		//判断值的大小，小的话往左子树匹配 
		{
			if(curp->leftNode==NULL)
			{
				TSTp newp=(TSTp)malloc(sizeof(TSTNode));
				 //没有新的节点那么申请一个新的节点，继续比较
				
				memset(newp,0,sizeof(TSTNode));
				//初始化新的节点
				
				newp->c[0]=key[charIndex];
				newp->c[1]=key[charIndex+1];
				//新的节点的值应该直接赋予，因为下一个是空的，相当于创建新的子树 
				
				curp->leftNode=newp;
				//左节点指向新的节点 
				
				curp->leftNode->parentNode=curp->parentNode;
				//兄弟节点的父节点指向自己节点的父节点 
			}
			
			//如果他的左节点leftnode不是空的，那么我们就不需要进行创建，继续往下比较，看看能不能匹配 
			//注意，这里不用对关键字的偏移量进行修改了 
			
			curp=curp->leftNode;
			//下一个节点指向左节点 
		}
		else 
		//判断值的大小，大的话往右子树匹配 
		{
			if(curp->rightNode==NULL)
			{
				TSTp newp=(TSTp)malloc(sizeof(TSTNode));
				 //没有新的节点那么申请一个新的节点，继续比较
				memset(newp,0,sizeof(TSTNode));
				//初始化新的节点
				
				newp->c[0]=key[charIndex];
				newp->c[1]=key[charIndex+1];
				//新的节点的值应该直接赋予，因为下一个是空的，相当于创建新的子树 
				
				curp->rightNode=newp;
				//右节点指向新的节点
				
				curp->rightNode->parentNode=curp->parentNode;
				//兄弟节点的父节点指向自己节点的父节点 		
			}
			
			//如果他的右节点rightnode不是空的，那么我们就不需要进行创建，继续往下比较，看看能不能匹配 
			//注意，这里不用对关键字的偏移量进行修改了 	
			
			curp=curp->rightNode; 
			//下一个节点指向右节点 		
		}	
	}	
 } 
 
pStack Traverse(pStack ps)
//构造出下一层节点的栈 
{
	pStack new_ps=(pStack)malloc(sizeof(Stack));
	//定义一个新的栈的指针，用来存储将要返回的新的一层的所有节点
	
	pStack t_ps=(pStack)malloc(sizeof(Stack)); 
	//定义一个新的栈，用来遍历 
	
	InitStack(new_ps);
	InitStack(t_ps);
	//初始化两个栈 
	
	while(!Empty(ps))
	//遍历出所有低一层的节点的下一层的节点 
	{
		TSTp p=NULL;
		
		p=Pop(ps);
		//从上一层的节点的栈里弹出低一层的节点，来计算下一层的节点 

		if(p->midNode!=NULL)
		{
			Push(t_ps,p->midNode);
		}
		while(!Empty(t_ps))
		//遍历出压入的这个节点的所有下一层的节点 
		{
			p=Pop(t_ps);
			//只弹出遍历的栈的节点 
			
			Push(new_ps,p);

			if(p->leftNode!=NULL)
			{
				Push(t_ps,p->leftNode);
			}
			//如果弹出的节点的左节点不是空的话，要压入栈里 
			
			if(p->rightNode!=NULL)
			{
				Push(t_ps,p->rightNode);
			}
			//如果弹出的节点的右节点不是空的话，要压入栈里 	
		}
	 } 
	 return new_ps;
	 //将只含下一层节点的栈的指针返回 
}
 
TSTp Match(char* key,TSTp root)
//该节点是否与root的子节点匹配 
{
	if(key==NULL)
		return NULL;
		
	TSTp curp=root->midNode;
	
	while(1)
	{
		if(curp==NULL&&root->nextNode==NULL)
		//如果是根节点匹配，那么这个节点的失效节点指向的就是根节点 
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
//构造失效函数 
{
	TSTp p=NULL;
	
	while(!Empty(ps))
	{
		p=Pop(ps);
		//依次弹出所求的层的节点
		
		int isMatch=0;
		//是否已经匹配到了相应的失效转换节点 
			
		if(p->parentNode->nextNode==NULL)
		//如果是深度为1的节点，那么其失效节点就是根节点 
			p->nextNode=p->parentNode;
		else
		{	
			TSTp curp=p->parentNode->nextNode;
			//需要进行匹配失效节点的节点
				 
			while(!isMatch)
			{
					
				TSTp mp=Match(p->c,curp);
				if(mp!=NULL)
				{
					p->nextNode=mp;
					if(mp->isEnd==1)	//该失效节点为终止结点 
					{
						p->FisEnd=1;
						p->Fnum=mp->num;
					}
					else if(mp->FisEnd==1)	//该失效节点的前置失效节点链中有终止结点 
					{
						p->FisEnd=1;
						p->Fnum=-1; 
					}
					isMatch=1;
				}
				else
				{
					curp=curp->nextNode;
					//否则继续匹配这个节点的失效节点的子节点	
				}
			}
		}
	}
}
