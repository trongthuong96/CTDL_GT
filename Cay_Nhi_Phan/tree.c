/*	Nguoi Lap Trinh : Do Trong Thuong
	Ngay Chinh Sua  : 20/08/2020
	Thoi Gian		: 17h00*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct node Node;
void Init(Node *&tree);
Node *GetNode(int x);
void Insert(Node *&tree, Node *p);
void Input(Node *&tree);
void Output(Node *tree);
long tinhtong(Node *tree);
int DemNode(Node *tree);
Node *Search(Node *&tree, int x);
void Delete(Node *&tree, int x);
int CapCay(Node *tree);
void Menu();

//Ham chinh
int main()
{
	Node *tree;
	int chon,c;
	do{
		Menu();
		printf(" - Chon 1 trong cac chuc nang tren: ");
		c=0;
		while((chon=getche()) != 13)
		{
			if( chon == 27) break;
			if(chon>47 && chon<58)
				c=c*10+(chon-48);
		}
		system("cls");
		printf("\n");
		switch(c)
		{
			case 1:
				Input(tree);
				system("cls");
				break;
			case 2:
				if(tree==NULL)
					printf(" - Danh sach trong.");
				else
				{
					printf(" - Du lieu trong danh sach la:\n");
					Output(tree);
				}
				getch();
				system("cls");
				break;
			case 3:
				int e;
				printf("\n - Nhap gia tri can xoa: ");
				scanf("%d",&e);
				Delete(tree,e);
				system("cls");
				break;
			case 4:
				int them;
				Node *q;
				printf("Nhap gia tri cho node can them: ");
				scanf("%d",&them);
				q=GetNode(them);
				if(q==NULL)
					printf("\nKhong them dc.");
				else
					Insert(tree,q);
				system("cls");
				break;
				
			case 5:
			{	int tim;
				printf("\n - Nhap gia tri can tim: ");
				scanf("%d",&tim);
				Node *p=Search(tree,tim);
				if(p!=NULL)
					printf("- Gia tri can tim o dia chi: %d",p);
				else
					printf("- Khong co gia tri can tim");
				getch();
				system("cls");
				break;
			}
			case 6:
			{
				printf("\n - Tong gia tri cua cay la: %d",tinhtong(tree));
				getch();
				system("cls");
				break;
			}
			case 7:
				printf("\n - Do dai cua cay la: %d",CapCay(tree));
				getch();
				system("cls");
				break;
			case 8:
				printf("\n - So node trong cay la: %d",DemNode(tree));
				getch();
				system("cls");
				break;
		default:
				if(chon!=27)
				{
					printf("Khong co chuc nang nay.");
					getch();
					system("cls");
				}
		}
	}while(chon!=27);
		
	return 0;
}

typedef struct node{
	int info;
	struct node *left;
	struct node *right;
}Node;

//Khoi tao goc
void Init(Node *&tree)
{
	tree=NULL;
}

//Tao node
Node *GetNode(int x)
{
	Node *p= new Node;
	if(p==NULL) return NULL;
	p->info=x;
	p->left=p->right=NULL;
	return p;
}

//Chen node cho cay
void Insert(Node *&tree, Node *p)
{
	if(tree==NULL)
		tree=p;
	else{
		if(p->info < tree->info)
			Insert(tree->left,p);
		if(p->info > tree->info)
			Insert(tree->right,p);
		return;
	}
}

//Nhap gia tri cho cay
void Input(Node *&tree)
{
	int x,c;
	if(tree==NULL)
		Init(tree);
	printf("\nNhap ESC de thoat INPUT.\n");
	do{
		c=0;
		printf(" - Nhap x: ");
		while((x=getche()) != 13)
		{
			if( x == 27) break;
			if(x>47 && x<58)
				c=c*10+(x-48);
			else
			{
				printf("\n\tBan nhap sai. Hay nhap so nguyen.\n - Nhap x: ");
			}
		}
		printf("\n");
		if(x!=27){
			Node *p= GetNode(c);
			if(p!=NULL)
				Insert(tree,p);
		}
	}while(x!=27);
}

//In ra gia tri cua cay theo thu tu tang dan
void Output(Node *tree)
{
	if(tree==NULL) return;
	Output(tree->left);
	printf("%4d",tree->info);
	Output(tree->right);
}

//Ham tinh tong gia tri trong tree
long tinhtong(Node *tree)
{
	long s=0;
	if(tree==NULL) return 0;
	s=tinhtong(tree->left)+tinhtong(tree->right)+tree->info;
	return s;
}

//Ham dem so node trong tree
int DemNode(Node *tree)
{
	if(tree==NULL) return 0;
	int a=DemNode(tree->left);
	int b=DemNode(tree->right);
	return a+b+1;
}

//Tim 1 node khi biet gia tri
Node *Search(Node *&tree, int x)
{
	if(tree==NULL) return NULL;
	if(tree->info < x)
		return Search(tree->right,x);
	if(tree->info > x)
		return Search(tree->left,x);
	return tree;
}

//Xoa 1 node trong cay
void Delete(Node *&tree, int x)
{
	if(tree==NULL) return;
	if(tree->info < x)
		return Delete(tree->right,x);
	if(tree->info > x)
		return Delete(tree->left,x);
	Node *p=tree;
	if(tree->left == NULL)
		tree = tree->right;
	else if(tree->right == NULL)
		tree = tree->left;
	else
	{
		Node *q, *l;
		q=p;
		l=p->left;
		while(l->right != NULL)
		{
			q=l;
			l=l->right;
		}
		tree->info = l->info;
		if(q==p)
			q->left=l->left;
		else
			q->right=l->left;
		p=l;
	}
	delete(p);
}

void DeleteAll(Node *&tree)
{
	
}

// Do dai cua cay
int CapCay(Node *tree)
{
	if(tree==NULL) return 0;
	int left=CapCay(tree->left);
	int right=CapCay(tree->right);
	if(left < right)
		return right+1;
	return left+1;
}

//Menu chuc nang
void Menu()
{
	printf("\n\n");
	printf("-------CHUC NANG-------");
	printf("\n");
	printf("\n 1. Nhap du lieu cho cay.");
	printf("\n 2. Xuat du lieu trong cay.");
	printf("\n 3. Xoa node trong cay.");
	printf("\n 4. Them 1 node vao cay.");
	printf("\n 5. Tim dia chi node trong cay khi biet gia tri.");
	printf("\n 6. Tong gia tri trong cay.");
	printf("\n 7. Do dai cua cay.");
	printf("\n 8. Tong so node co trong cay");
	printf("\n");
	printf("\n----NHAN ESC DE THOAT----");
	printf("\n");
	printf("\n=================================\n");
	printf("\n");
}
