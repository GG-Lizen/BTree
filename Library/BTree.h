#pragma once
#include"Base.h"
#define m 5 //B����Ϊ3
typedef struct BTNode{
	int keynum;//��㵱ǰ�Ĺؼ��ָ���
	KeyType key[m + 1];//�ؼ�������,key[0]δ��
	struct BTNode* parent;//˫�׽��ָ��
	struct BTNode* ptr[m+1]; // ���ӽ��ָ������
	Record* recptr[m + 1]; // ��¼ָ������, 0�ŵ�Ԫδ��
}BTNode,*BTree;//B���Ľ�㼰ָ������
typedef struct {
	BTree pt;//ָ���ҵ��Ľ��
	int i;//1��i��m,�ڽ���еĹؼ���λ��
	int tag;//1:���ҳɹ�,0:����ʧ��
}result;//B���Ĳ��ҽ������

Status initialBTree(BTree& p);
void SearchBTree(BTree t,int k,result &r);//����
void InsertBTree(BTree&t,int k,BTree q,int i);//����
void DeleteBTree(BTree& p, int i);//ɾ��
void printBTree(BTree p, int i);//��ӡ�����