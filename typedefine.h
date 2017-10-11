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
    /** �ڵ��ֵ */  
    
    struct mynode*	leftNode;     
	/*��ߵĽڵ㣬�����洢�ڱ������Сһ����ַ�*/  
    struct mynode*	midNode;     
	/*�м�Ľڵ������洢��������һ���ַ�*/ 
    struct mynode*	rightNode;     
	/*�ұߵĽڵ㣬�����洢�ڱ�����д�һ����ַ�*/  
  
    char	c[2];      
    /*���ڵ��ʾ���ַ��������ֽڣ�����װ���ĵķ���*/ 
    
    int num;
    /*���ڵ��Լ�������*/
    
    int isEnd;
    /*��ʾ����ڵ��ǲ�����ֹ�ڵ�*/
    
    struct mynode*	parentNode;
    /*��ʾ����ڵ�ĸ��ڵ�*/
    
    struct mynode*	nextNode;
    /*��ʾ����ڵ��ʧЧ��������һ���ڵ�*/
    
}TSTNode;  

typedef struct offnode{
	long long offset;
	struct offnode *nextnode;
}ONode,*ONP;

typedef struct lnode{
	//����ṹ
	bool flag;
	ONP offset;
	long num;
	char key[wMAX];
	int len;
}LNode,*LNP;

typedef TSTNode* TSTp;

//    ����һ���ڵ�Ľṹ
typedef struct node
{
    TSTp member;            //������
    struct node * pNext;//ָ����
}Node,*pNode;

//    ����һ��ջ�ṹ
typedef struct stack
{
    pNode Top;            //ջ��
    pNode Bottom;        //ջ��
}Stack,* pStack;


//TSTmatch.c
TSTp init(TSTp p);
TSTp add(char* key,TSTp root,int length,int linecount);
pStack Traverse(pStack ps);				//�������һ��ڵ��ջ 
TSTp Match(char* key,TSTp root);		//�ýڵ��Ƿ���root���ӽڵ�ƥ�� 
void  Failure(pStack ps);		//����ʧЧ���� 

//stack.c
void InitStack(pStack );        //    ��ʼ��ջ�ĺ���
bool Push(pStack ,TSTp);            //    ����ѹջ�����ĺ���
void TraverseStack(pStack );    //    ����ջ����
bool Empty(pStack );            //    �ж�ջ�Ƿ�Ϊ�յĺ���
TSTp Pop(pStack );                //    ���г�ջ�����ĺ���
void Clear(pStack );            //    ���ջ�ĺ���
pStack Copy(pStack );		//����ջ����һ���µ�ָ������ 


//treeop.c
void DLR(TSTp root);		//ǰ������� 
void MLR(TSTp root);		//���������





#endif
