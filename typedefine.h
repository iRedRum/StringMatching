#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int bool;
#define false 0
#define true 1

#define PLMAX 1300000
#define wMAX 120
#define BMAX 10000

typedef struct mynode{  
    /** 节点的值 */  
    
    struct mynode*	leftNode;     
	/*左边的节点，用来存储在编码表中小一点的字符*/  
    struct mynode*	midNode;     
	/*中间的节点用来存储检索的下一个字符*/ 
    struct mynode*	rightNode;     
	/*右边的节点，用来存储在编码表中大一点的字符*/  
  
    char	c[2];      
    /*本节点表示的字符，两个字节，用来装中文的符号*/ 
    
    int num;
    /*本节点自己的行数*/
    
    int isEnd;
    /*表示这个节点是不是终止节点*/
    
    struct mynode*	parentNode;
    /*表示这个节点的父节点*/
    
    struct mynode*	nextNode;
    /*表示这个节点的失效函数的下一个节点*/
    
}TSTNode;  

typedef struct offnode{
	long long offset;
	struct offnode *nextnode;
}ONode,*ONP;

typedef struct lnode{
	//输出结构
	bool flag;
	ONP offset;
	long num;
	char key[wMAX];
	int len;
}LNode,*LNP;

typedef TSTNode* TSTp;

//    定义一个节点的结构
typedef struct node
{
    TSTp member;            //数据域
    struct node * pNext;//指针域
}Node,*pNode;

//    定义一个栈结构
typedef struct stack
{
    pNode Top;            //栈顶
    pNode Bottom;        //栈底
}Stack,* pStack;


//TSTmatch.c
TSTp init(TSTp p);
TSTp add(char* key,TSTp root,int length,int linecount);
pStack Traverse(pStack ps);				//构造出下一层节点的栈 
TSTp Match(char* key,TSTp root);		//该节点是否与root的子节点匹配 
void  Failure(pStack ps);		//构造失效函数 

//stack.c
void InitStack(pStack );        //    初始化栈的函数
bool Push(pStack ,TSTp);            //    进行压栈操作的函数
void TraverseStack(pStack );    //    遍历栈函数
bool Empty(pStack );            //    判断栈是否为空的函数
TSTp Pop(pStack );                //    进行出栈操作的函数
void Clear(pStack );            //    清空栈的函数
pStack Copy(pStack );		//复制栈到另一个新的指针里面 


//treeop.c
void DLR(TSTp root);		//前序遍历。 
void MLR(TSTp root);		//中序遍历。





#endif
