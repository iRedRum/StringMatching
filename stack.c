#include "typedefine.h"

//    ����ջ�ĳ�ʼ���ĺ���
void InitStack(pStack ps)
{
    ps->Top = (pNode)malloc(sizeof(Node));        //    �����ڴ�ռ��ջ��
    if (NULL == ps->Top)
    {
        printf("��̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    else
    {
        ps->Bottom = ps->Top;	               //    ʹջ��Ҳָ��ջ���ռ�
        ps->Top->pNext = NULL;                    //    ջ��ָ����ΪNULL��
    }
    return ;
}

//    ���н�ջ�����ĺ���
bool Push(pStack ps,TSTp data)
{
    pNode pNew = (pNode)malloc(sizeof(Node));    //    ����һ���½ڵ㣬�������ڴ�ռ�
    if (NULL == pNew)
    {
        return false;
    }
    pNew->member = data;                        //    ��Ҫ��ջ�����ݸ����½ڵ��member��Ա
    pNew->pNext = ps->Top;                        //    ʹ�½ڵ��ָ��ָ��ջ��
    ps->Top = pNew;                                //    ���½ڵ���Ϊ��ջ��

    return true;
}

//    ����ջ�ĺ���
void TraverseStack(pStack ps)
{
    pNode pNew = ps->Top;
    while(pNew!= ps->Bottom)                //    ֻҪջ��������ջ�ף�ѭ��
    {
        printf("��ǰ��%c%c,ʧЧ��%c%c\n",pNew->member->c[0],pNew->member->c[1],pNew->member->nextNode->c[0],pNew->member->nextNode->c[1]);            //    ��ӡջ���ĳ�Աmember
        pNew = pNew->pNext;                //    ջ��ָ�������ƶ�һ��
    }
    return ;
}

//����ջ 
pStack Copy(pStack ps)
{
	pStack pss=(pStack)malloc(sizeof(Stack));
    pNode pNew = ps->Top;
    InitStack(pss);
    while(pNew!= ps->Bottom)                //    ֻҪջ��������ջ�ף�ѭ��
    {
        Push(pss,pNew->member);          //    ��ӡջ���ĳ�Աmember
        pNew = pNew->pNext;                //    ջ��ָ�������ƶ�һ��
    }
    return pss;
}

//    �ж�ջ�Ƿ�Ϊ��
bool Empty(pStack ps)
{
    if(ps->Top == ps->Bottom)    //    ջ������ջ�ף�������ջ��û����ô
    {
        return true;
    }
    else
    {
        return false;
    }
}

//    ���г�ջ��������
TSTp Pop(pStack ps)
{
    pNode pSwap = NULL;            
    TSTp return_val=NULL;
    if (Empty(ps))                //�ж�ջ�Ƿ�Ϊ�գ�Ϊ�վͲ��ܽ��г�ջ����
    {
        exit(-1);
    }
    else
    {
        return_val = ps->Top->member;    //    ��ջ���ĳ�Աmember��ֵ����return_val��Ϊ��������ֵ
        pSwap = ps->Top;                //    ʹpSwapָ��ջ��
        ps->Top = ps->Top->pNext;        //    ʹջ��ָ��ջ����һ���ڵ�
        free(pSwap);                    //    �ͷ���ǰ��ջ���ռ�
        return return_val;
    }
}

//    ���ջ�ĺ���
void Clear(pStack ps)
{
    pNode pNew = NULL;
    
    while (ps->Top != ps->Bottom)        //    ջ����ջ�ײ��ȣ�ѭ��
    {
        pNew = ps->Top;                    //    ʹһ���½ڵ��ջ��ָ��ͬһ�ռ�
        ps->Top = ps->Top->pNext;        //    ʹջ��ָ��ջ������һ���ڵ�
        free(pNew);                        //    �ͷŵ���ǰ��ջ���ռ�
    }
    return ;
}

