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
		printf("×Ö·û£º%c%c£¬±àÂë£º%x,%x\n",a[0],a[1],(unsigned char)a[0],(unsigned char)a[1]);
		printf("¸¸Ç×£º%c%c\n",root->parentNode->c[0],root->parentNode->c[1]);
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
		printf("×Ö·û£º%c%c£¬±àÂë£º%x,%x\n",a[0],a[1],(unsigned char)a[0],(unsigned char)a[1]);
		//printf("±àÂë£º%x,%x\n",(unsigned char)a[0],(unsigned char)a[1]);
	}
	else
	{
		printf("×Ö·û£º%c£¬±àÂë£º%x,%x\n",a[1],(unsigned char)a[0],(unsigned char)a[1]);
		//printf("±àÂë£º%x,%x\n",(unsigned char)a[0],(unsigned char)a[1]);
	}
	MLR(root->midNode);
	MLR(root->rightNode);
} 
