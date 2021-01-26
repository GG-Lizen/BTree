#pragma once
#include"BTree.h"

//��ʼ��
Status initialBTree(BTree& p) {
	p = (BTree)malloc(sizeof(BTNode));
	p->keynum = 0;
	p->parent = NULL;
	for (int i = 0; i <= m; i++)
		p->ptr[i] = NULL;
	return OK;
}

//ens

//����
int Search(BTree p, int k) {
	int i = 1;
	while (i<=p->keynum&&k>p->key[i])
	{
		i++;
	}
	return i;
}
void SearchBTree(BTree t, int k, result& r) {
	// ��n��B��t�Ϸܳ�������k.��r����(pt, i, tag)
	// �����ҳɹ������aa = 1ָ��pt��ָ����е�i���ؼ��ֵ���k
	// ����tag = 0.��Ҫ���������Ϊk�ļ�¼.Ӧλ��pt����е�i - 1���͵������ؼ���֮��
	int i = 0,found = 0;
	BTree p = t, q = NULL;//��ʼ,pָ������;p������ָ�������,gָ����˫��
	while (p!= NULL && 0 == found) {
		i = Search(p, k);//��p->key[1 ..p->keynum]�в���p->key[i-1]k<=p->key[i]
		if(i<=p->keynum && p->key[i] ==k) found = 1;//�ҵ�����ؼ���
		else { q = p; p = p->ptr[i - 1]; }
	}
	if (1 == found) {//���ҳɹ�,����k��λ��p��i
		r.pt = p; r.i = i; r.tag = 1;
	}else {//���Ҳ��ɹ�,����k�Ĳ���λ��q��i
		r.pt = q; r.i = i; r.tag = 0;
	}
}
//����end

//����
void split(BTree& q, int s, BTree& ap) {
	// ��q�����ѳ��������, ǰһ�뱣����ԭ���, ��һ������ap��ָ�½��
	int i, j, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));//�����½��
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1, j = 1; i <= n; i++, j++) { // ��һ������ap���
		ap->key[j] = q->key[i];
		ap->ptr[j] = q->ptr[i];
	}
	ap->keynum = n - s;
	ap->parent = q->parent;
	for (i = 0; i <= n - s; i++)// �޸��½����ӽ��� parent��
		if (ap->ptr[i] != NULL) ap->ptr[i]->parent = ap;
	q->keynum = s - 1; // q����ǰһ�뱣�����޸�keynum
}
void newRoot(BTree& t, BTree p, int x, BTree ap) {// �����µĸ����
	t = (BTNode*)malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap; t->key[1] = x; 
	if (p != NULL) p->parent = t;
	if (ap != NULL)ap->parent = t;
	t->parent = NULL; // �¸���˫���ǿ�ָ��
}
void Insert(BTree& q, int i, int x, BTree ap) {
	// �ؼ���x���½��ָ��ap �ֱ���˵�q->key[i]�� q->ptr[i]
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
	// ��B��t��q����key[i - 1]��key[i]֮����˹ؼ���k
	// ���������ؼ��ָ�������B���Ľ�, ����˫��ָ�������н�����, ʹt����m��B��
	int x, s, finished = 0, needNewRoot = 0;
	BTree ap;
	if (NULL == q) newRoot(t,NULL,k,NULL);//�����µĸ����
	else {
		x = k; ap = NULL;
		while (0 == needNewRoot && 0 == finished) {
			Insert(q, i, x, ap);//x��ap�ֱ���˵�q->key[ i]��q->ptr[i]
			if(q->keynum <m) finished=1;//�������
			else {//����q���
				s = (m + 1)/ 2; split(q, s, ap); x = q->key[s]; 
				if (q->parent != NULL) {
					q = q->parent; i = Search(q, x);//��˫�׽���в��ҡ��Ĳ���λ��
				}
				else needNewRoot = 1;
			}
		}//while
		if (1== needNewRoot) // t�ǿ������߸�����ѷ���Ϊq��ap���
		newRoot(t, q,x, ap);//���ɺ���Ϣ(a,x,ap)���µĸ����t
	}
}
//����end


//ɾ��
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
	BTree q;//ָ��p�����
	q = p->parent;
	if (q == NULL) {
		if (p->keynum == 0) {//�����任
			q = p->ptr[0];//ָ���¸����
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
	else p_M = p->key[p->keynum];//ָ��p_M���Ԫ��

	j = 1;
	while (q->key[j] <=p_M&&j<=q->keynum) {//Ѱ���ڸ��ڵ���ָ��λ��
		j++;
	}//j-1Ϊp����λ��
	
	if (j > q->keynum) {//���Ҳ�
		j--;
		InsertBTree(p, q->key[j],p, Search(p, q->key[j]));
		//�ֵܿɽ�
		if (q->ptr[j-1]->keynum > (m - 1) / 2) {
			q->key[j] = q->ptr[j-1]->key[q->keynum];
			Remove(q->ptr[j-1], q->keynum);
		}
		//�ֵܲ��ɽ�
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
		//�ֵܿɽ�
		if (q->ptr[j]->keynum > (m - 1) / 2) {
			q->key[j] = q->ptr[j]->key[1];
			Remove(q->ptr[j], 1);
		}
		//�ֵܲ��ɽ�
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
//ɾ��end

//��ӡ�����
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

//��ӡ�����end