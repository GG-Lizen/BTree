#include"BTree.h"

void addBT(BTree &p) {
	int in;
	result r;
	printf("\n");
	printf("\n");
	printf("                               ************************\n");
	printf("                               *         添加         *\n");
	printf("                               ************************\n");
	printf("                               ************************\n");
	printf("\n");
	printf("\n");
		printf("请输入：");
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
	printf("                               *         删除         *\n");
	printf("                               ************************\n");
	printf("                               ************************\n");
	printf("\n");
	printf("\n");
	printf("请输入：");
	scanf(" %d", &in);
	getchar();
	SearchBTree(p, in, r);
	DeleteBTree(r.pt, r.i);

}
void Show(BTree p) {
	if (p->keynum == 0) {
		printf("B树为空\n");
		return;
	}
	printf("B树结构如下\n");
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
		printf("                               *         1、添加         *\n");
		printf("                               *                         *\n");
		printf("                               *         2、删除         *\n");
		printf("                               *                         *\n");
		printf("                               *         3、查看         *\n");
		printf("                               *                         *\n");
		printf("                               ***************************\n");
		printf("                               ***************************\n");
		printf("\n");
		printf("\n");
		printf("请输入>>");
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