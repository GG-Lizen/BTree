#pragma once
#include"BTree.h"

//初始化
Status initialBTree(BTree& p) {
	p = (BTree)malloc(sizeof(BTNode));
	p->keynum = 0;
	p->parent = NULL;
	for (int i = 0; i <= m; i++)
		p->ptr[i] = NULL;
	return OK;
}

//ens

//查找
int Search(BTree p, int k) {
	int i = 1;
	while (i<=p->keynum&&k>p->key[i])
	{
		i++;
	}
	return i;
}
void SearchBTree(BTree t, int k, result& r) {
	// 在n阶B树t上奋抄兰键字k.用r返回(pt, i, tag)
	// 若查找成功标记上aa = 1指针pt所指结点中第i个关键字等于k
	// 否则tag = 0.若要插入羊键字为k的记录.应位于pt结点中第i - 1个和第主个关键字之间
	int i = 0,found = 0;
	BTree p = t, q = NULL;//初始,p指向根结点;p将用于指向待查结点,g指向其双亲
	while (p!= NULL && 0 == found) {
		i = Search(p, k);//在p->key[1 ..p->keynum]中查找p->key[i-1]k<=p->key[i]
		if(i<=p->keynum && p->key[i] ==k) found = 1;//找到待查关键字
		else { q = p; p = p->ptr[i - 1]; }
	}
	if (1 == found) {//查找成功,返回k的位置p及i
		r.pt = p; r.i = i; r.tag = 1;
	}else {//查找不成功,返回k的插入位置q及i
		r.pt = q; r.i = i; r.tag = 0;
	}
}
//查找end

//插入
void split(BTree& q, int s, BTree& ap) {
	// 将q结点分裂成两个结点, 前一半保留在原结点, 后一半移人ap所指新结点
	int i, j, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));//生成新结点
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1, j = 1; i <= n; i++, j++) { // 后一半移人ap结点
		ap->key[j] = q->key[i];
		ap->ptr[j] = q->ptr[i];
	}
	ap->keynum = n - s;
	ap->parent = q->parent;
	for (i = 0; i <= n - s; i++)// 修改新结点的子结点的 parent域
		if (ap->ptr[i] != NULL) ap->ptr[i]->parent = ap;
	q->keynum = s - 1; // q结点的前一半保留，修改keynum
}
void newRoot(BTree& t, BTree p, int x, BTree ap) {// 生成新的根结点
	t = (BTNode*)malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap; t->key[1] = x; 
	if (p != NULL) p->parent = t;
	if (ap != NULL)ap->parent = t;
	t->parent = NULL; // 新根的双亲是空指针
}
void Insert(BTree& q, int i, int x, BTree ap) {
	// 关键字x和新结点指针ap 分别插人到q->key[i]和 q->ptr[i]
	int j, n = q->keynum;
	for (j = n; j >= i; j--) {
		q->key[j + 1] = q->key[j]; 
		q->ptr[j + 1] = q->ptr[j];
	}
	q->key[i] = x; q->ptr[i] = ap;
	if (ap!= NULL) ap->parent = q;
	q->keynum++;
}
void InsertBTree(BTree& t, int k, BTree q, int i) {
	// 在B树t中q结点的key[i - 1]和key[i]之间插人关键字k
	// 若插入后结点关键字个数等于B树的阶, 则沿双亲指针链进行结点分裂, 使t仍是m阶B树
	int x, s, finished = 0, needNewRoot = 0;
	BTree ap;
	if (NULL == q) newRoot(t,NULL,k,NULL);//生成新的根结点
	else {
		x = k; ap = NULL;
		while (0 == needNewRoot && 0 == finished) {
			Insert(q, i, x, ap);//x和ap分别插人到q->key[ i]和q->ptr[i]
			if(q->keynum <m) finished=1;//插入完成
			else {//分裂q结点
				s = (m + 1)/ 2; split(q, s, ap); x = q->key[s]; 
				if (q->parent != NULL) {
					q = q->parent; i = Search(q, x);//在双亲结点中查找×的插人位置
				}
				else needNewRoot = 1;
			}
		}//while
		if (1== needNewRoot) // t是空树或者根结点已分裂为q和ap结点
		newRoot(t, q,x, ap);//生成含信息(a,x,ap)的新的根结点t
	}
}
//插入end


//删除
void Merge(BTree&p1,BTree&p2) {
	if (p1->keynum > (m - 1) / 2 || p2->keynum>(m - 1) / 2) return;
	int i,j;
	j = p1->keynum;
	p1->ptr[j] = p2->ptr[0];
	
	for (i = 1; i <= p2->keynum; i++)
	{
		p1->key[j + i] = p2->key[i];
		p1->ptr[j + i] = p2->ptr[i];
	//	p1->ptr[j + i]->parent = p1;
	}
	if(p1->ptr[j] !=NULL)
		for (i = 0; i <= p2->keynum; i++)
		{
			p1->ptr[j + i]->parent = p1;
		}
	p1->keynum += j;
	free(p2);

}
void Remove(BTree& p, int i) {
	if (i <= 0 || i > p->keynum) return;
	int j, n = p->keynum;
	for (j = i; j < n; j++) {
		p->key[j] = p->key[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
		p->keynum--;
}
void Successor(BTree& p, int i) {
	if (i <= 0 || i > p->keynum) return;
	BTree q = p->ptr[i];
	if (q == NULL)return;
	while (q->ptr[0] != NULL) {
		q = q->ptr[0];
	}
	p->key[i] = q->key[1];
	p = q;
}
void Restore(BTree& p,int i) {
	int j,p_M,n=p->keynum;
	BTree q;//指向p父结点
	q = p->parent;
	if (q == NULL) {
		if (p->keynum == 0) {//根结点变换
			q = p->ptr[0];//指向新根结点
			if (q == NULL)return;
			p->keynum = q->keynum ;
			p->ptr[0] = q->ptr[0];
			for (j = 1; j <= q->keynum; j++) {
				p->key[j] = q->key[j];
				p->ptr[j] = q->ptr[j];
			}
			for (j = 0; j <= p->keynum; j++)
			{
				if (p->ptr[j] != NULL)p->ptr[j]->parent = p;
			}
			free(q);
	}
		return;
	}
	if (n == 0) p_M = p->key[1];
	else p_M = p->key[p->keynum];//指向p_M最大元素

	j = 1;
	while (q->key[j] <=p_M&&j<=q->keynum) {//寻找在父节点中指针位序
		j++;
	}//j-1为p所在位序
	
	if (j > q->keynum) {//最右侧
		j--;
		InsertBTree(p, q->key[j],p, Search(p, q->key[j]));
		//兄弟可借
		if (q->ptr[j-1]->keynum > (m - 1) / 2) {
			q->key[j] = q->ptr[j-1]->key[q->keynum];
			Remove(q->ptr[j-1], q->keynum);
		}
		//兄弟不可借
		else {
			Merge( q->ptr[j-1],p);
			//DeleteBTree(q, j-1);
			Remove(q, j);
			if (q->keynum < (m - 1) / 2)
				Restore(q, j);
		}
	}
	else {
		InsertBTree(p, q->key[j], p, Search(p, q->key[j]));
		//兄弟可借
		if (q->ptr[j]->keynum > (m - 1) / 2) {
			q->key[j] = q->ptr[j]->key[1];
			Remove(q->ptr[j], 1);
		}
		//兄弟不可借
		else {
			Merge(p,q->ptr[j]);
			//DeleteBTree(q, j);
			Remove(q, j);
			if(q->keynum < (m - 1) / 2)
				Restore(q, j);
		
		}
	}
}
void DeleteBTree(BTree& p, int i) {
	if (p->ptr[i] != NULL) {
		Successor(p, i);
		DeleteBTree(p, 1);
	}
	else {
		Remove(p, i);
		if (p->keynum < (m - 1) / 2)
			Restore(p, i);
	}
}
//删除end

//打印凹入表
void printBTree(BTree p, int i) {
	if (p == NULL) return;
	int j ,n;
	for (n = 0; n < i; n++) {
		printf("\t");
	}
	printf("---\n");
	for (j= p->keynum; j>= 1; j--) {
		for (n = 0; n < i; n++) {
			printf("\t");
		}
		printf("%d\n", p->key[j]);
		if (p->ptr[j] != NULL)
			printBTree(p->ptr[j], i + 1);
	}
	if (p->ptr[0] != NULL)
		printBTree(p->ptr[0], i + 1);
	for (n = 0; n < i; n++) {
		printf("\t");
	}
	printf("---\n");
}

//打印凹入表end