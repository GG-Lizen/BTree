#include"BTree.h"

void addBT(BTree &p) {
	int in;
	result r;
	printf("\n");
	printf("\n");
	printf("                               ************************\n");
	printf("                               *         ���         *\n");
	printf("                               ************************\n");
	printf("                               ************************\n");
	printf("\n");
	printf("\n");
		printf("�����룺");
		scanf(" %d", &in);
		getchar();
		SearchBTree(p, in, r);
		if (r.tag == 0)
			InsertBTree(p, in, r.pt, r.i);


}
void deleteBT(BTree& p) {
	int in;
	result r;
	printf("\n");
	printf("\n");
	printf("                               ************************\n");
	printf("                               *         ɾ��         *\n");
	printf("                               ************************\n");
	printf("                               ************************\n");
	printf("\n");
	printf("\n");
	printf("�����룺");
	scanf(" %d", &in);
	getchar();
	SearchBTree(p, in, r);
	DeleteBTree(r.pt, r.i);

}
void Show(BTree p) {
	if (p->keynum == 0) {
		printf("B��Ϊ��\n");
		return;
	}
	printf("B���ṹ����\n");
	if (p == NULL || p->keynum == 0) return;
	printBTree(p, 1);
}

int main() {
	int in;
	BTree p;
	initialBTree(p);
	result r;
	while (true)
	{
		printf("\n");
		printf("\n");
		printf("                               ***************************\n");
		printf("                               *                         *\n");
		printf("                               *         1�����         *\n");
		printf("                               *                         *\n");
		printf("                               *         2��ɾ��         *\n");
		printf("                               *                         *\n");
		printf("                               *         3���鿴         *\n");
		printf("                               *                         *\n");
		printf("                               ***************************\n");
		printf("                               ***************************\n");
		printf("\n");
		printf("\n");
		printf("������>>");
		scanf(" %d", &in);
		getchar();
		switch (in)
		{
		case 1:addBT(p); break;
		case 2:deleteBT(p); break;
		case 3:Show(p); break;
		default:
			break;
		}
	}


}