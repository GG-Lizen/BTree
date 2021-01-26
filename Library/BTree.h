#pragma once
#include"Base.h"
#define m 5 //B树阶为3
typedef struct BTNode{
	int keynum;//结点当前的关键字个数
	KeyType key[m + 1];//关键字数组,key[0]未用
	struct BTNode* parent;//双亲结点指针
	struct BTNode* ptr[m+1]; // 孩子结点指针数组
	Record* recptr[m + 1]; // 记录指针向量, 0号单元未用
}BTNode,*BTree;//B树的结点及指针类型
typedef struct {
	BTree pt;//指向找到的结点
	int i;//1≤i≤m,在结点中的关键字位序
	int tag;//1:查找成功,0:查找失败
}result;//B树的查找结果类型

Status initialBTree(BTree& p);
void SearchBTree(BTree t,int k,result &r);//查找
void InsertBTree(BTree&t,int k,BTree q,int i);//插入
void DeleteBTree(BTree& p, int i);//删除
void printBTree(BTree p, int i);//打印凹入表