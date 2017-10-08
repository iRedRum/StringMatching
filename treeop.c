#include "typedefine.h"

void DLR(TSTp root)
{
	char a[2];
	if(root==NULL)
	{
		return;
	}
	a[0]=root->c[0];
	a[1]=root->c[1];
	if(root->parentNode!=NULL)
	{
		printf("�ַ���%c%c�����룺%x,%x\n",a[0],a[1],(unsigned char)a[0],(unsigned char)a[1]);
		printf("���ף�%c%c\n",root->parentNode->c[0],root->parentNode->c[1]);
	}
	DLR(root->leftNode);
	DLR(root->midNode);
	DLR(root->rightNode);
}

void MLR(TSTp root)
{
	char a[2];
	if(root==NULL)
	{
		return 0;
	}
	MLR(root->leftNode);
	a[0]=root->c[0];
	a[1]=root->c[1];
	if(a[0]>>7)
	{
		printf("�ַ���%c%c�����룺%x,%x\n",a[0],a[1],(unsigned char)a[0],(unsigned char)a[1]);
		//printf("���룺%x,%x\n",(unsigned char)a[0],(unsigned char)a[1]);
	}
	else
	{
		printf("�ַ���%c�����룺%x,%x\n",a[1],(unsigned char)a[0],(unsigned char)a[1]);
		//printf("���룺%x,%x\n",(unsigned char)a[0],(unsigned char)a[1]);
	}
	MLR(root->midNode);
	MLR(root->rightNode);
} 
