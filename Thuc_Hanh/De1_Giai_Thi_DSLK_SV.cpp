#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

//cau 1 khai bao cau truc sinh vien
typedef struct sinhvien{
	char mssv[11];
	char hoten[40];
	float toan,ly,hoa,dtb;
	char xeploai;
}SV;

//cau 2: Ham xep loai cho sinhv vien
char XepLoai(SV a)
{
	if(a.dtb >= 9)
		return 'X';
	if(a.dtb >= 8 && a.dtb < 9)
		return 'G';
	if(a.dtb >= 7 && a.dtb < 8)
		return 'K';
	if(a.dtb >= 4 && a.dtb < 7)
		return 'T';	
	if(a.dtb<4)
		return 'Y';		
}

//cau 3: Nhap 1 sinh vien
void Input1SV(SV &a)
{
	printf("\n\t-Nhap mssv: ");
	fflush(stdin);
	gets(a.mssv);
	printf("\n\t-Nhap ho ten: ");
	gets(a.hoten);
	
	do{
		printf("\n\t-Nhap diem toan: ");
		scanf("%f",&a.toan);
		if(a.toan<0 || a.toan>10)
			printf("\t Nhap sai, Nhap lai.\n");
	}while(a.toan<0 || a.toan>10);
	
	do{
		printf("\n\t-Nhap diem ly: ");
		scanf("%f",&a.ly);
		if(a.ly<0 || a.ly>10)
			printf("\t Nhap sai, Nhap lai.\n");
	}while(a.ly<0 || a.ly>10);
	
	do{
		printf("\n\t-Nhap diem hoa: ");
		scanf("%f",&a.hoa);
		if(a.hoa<0 || a.hoa>10)
			printf("\t Nhap sai, Nhap lai.\n");
	}while(a.hoa<0 || a.hoa>10);
}

//Ham xuat 1 sinh vien
void Output1SV(SV &a)
{
	
	printf("\n\t%s",a.mssv);
	printf("	%s",a.hoten);
	printf("		%.2f",a.toan);
	printf("		%.2f",a.ly);
	printf("		%.2f",a.hoa);
	a.dtb=(a.toan+a.ly+a.hoa)/3;
	printf("		%.2f",a.dtb);
	a.xeploai=XepLoai(a);
	if(a.xeploai=='X')
		printf("	Xuat Sac");
	else if(a.xeploai=='G')
		printf("	Gioi");
	else if(a.xeploai=='K')
		printf("	Kha");
	else if(a.xeploai=='T')
		printf("	Tring Binh");
	else if(a.xeploai=='Y')
		printf("	Yeu");
}

//khai bao kieu du lieu node
typedef struct node{
	SV data;
	struct node* next;
}Node;

//khai bao kieu du lieu list
typedef struct list{
	Node* head;
	Node* tail;
}LIST;

//Ham tao gia tri
void Init(LIST &l)
{
	l.head=l.tail=NULL;
}

//Ham tao node 
Node* GetNode(SV a)
{
	Node* p=new Node;
	if(p==NULL) return NULL;
	p->data=a;
	p->next=NULL;
	return p;
}

//Ham them 1 node vao dau danh sach
void AddHead(LIST &l,Node* p)
{
	if(l.head==NULL)
		l.head=l.tail=p;
	else
	{
		p->next=l.head;
		l.head=p;
	}
}

//Ham them thong tin vao danh sach
void InputDS(LIST &l)
{
	SV a;
	Init(l);
	int b;
	do{
		printf("\n\tThoat nhap ESC, tiep tuc nhap ENTER.");
		b=getch();
		if(b!=27)
			{
				Input1SV(a);
				Node* p=GetNode(a);
				if(p!=NULL)
					AddHead(l,p);
			}
	}while(b!=27);
}

//Ham xuat thong tin sv co trong danh sach
void OutputDS(LIST l)
{
	printf("\n\tMSSV	HoTen		Toan		Ly		Hoa		DTB	XepLoai\n");
	for(Node* p=l.head; p!=NULL; p=p->next)
	{
		Output1SV(p->data);
		printf("\n");
	}
}

//Ham xoa 1 node bat ky co trong danh sach
void Delete(LIST &l,Node* p)
{
	if(l.head==NULL)
		return;
	if(p!=NULL)
	{
		if(p==l.head)
		{
			l.head=l.head->next;
			p->next=NULL;
		}
		else if(p==l.tail)
		{
			Node*q=l.head,*e;
			while(q->next!=NULL)
			{
				e=q;
				q=q->next;
			}
			l.tail=e;
			l.tail->next=NULL;
		}
		else
		{
			Node* q=l.head,*e;
			while(q->next!=p->next)
			{
				e=q;
				q=q->next;
			}
			e->next=p->next;
			p->next=NULL;
		}
		delete(p);
	}
}

//cau 4 xoa sinh vien loai yeu
void DeleteSinhVienYeu(LIST &l)
{
	Node*p=l.head,*q;
	 while(p!=NULL)
	 {
	 	q=p;
	 	if(p->data.xeploai=='Y')
	 	{
	 		p=p->next;
	 		Delete(l,q);
		}
		else
			p=p->next;
	 }
}

//cau 5 liet ke sinh vien co diem trung binh >=9
void LietKe(LIST l)
{
	int flag=0;
	for(Node* p=l.head; p!=NULL; p=p->next)
	{
		if(p->data.xeploai=='X')
		{
			Output1SV(p->data);
			printf("\n");
			flag=1;
		}
	}
	if(flag==0)
		printf("\t-Khong co.");
}

//Ham menu
void Menu()
{
	printf("\t--------CAC CHUC NANG CUA CHUONG TRINH---------\n\n");
	printf("\tChuc nang 1: Nhap thong tin sinh vien vao danh sach.\n\n");
	printf("\tChuc nang 2: Xuat thong tin sinh vien co trong danh sach.\n\n");
	printf("\tChuc nang 3: Xoa tat ca sinh vien co hanh kiem YEU.\n\n");
	printf("\tChuc nang 4: Nhung sinh vien co diem trung binh >= 9.\n\n");
	printf("\t-----------------Nhan ESC de thoat-------------\n\n");
}

//cau 6 ham chinh
int main()
{
	LIST l;
	int chucnang;
	do{
		Menu();
		printf("\tChon 1 trong cac chuc nang tren: ");
		chucnang=getche();
		printf("\n");
		switch(chucnang)
		{
			case '1':
			{
				InputDS(l);
				system("cls");
				break;
			}
			case '2':
			{
				OutputDS(l);
				printf("\n\t(NHAN PHIM BAT KY DE QUAY VE MENU CHUC NANG)");
				getch();
				system("cls");
				break;	
			}	
			case '3':
			{
				DeleteSinhVienYeu(l);
				printf("\n\t-Danh sach sau khi xoa sinh vien YEU la:\n");
				OutputDS(l);
				printf("\n\t(NHAN PHIM BAT KY DE QUAY VE MENU CHUC NANG)");
				getch();
				system("cls");
				break;
			}
			case '4':
			{
				printf("\n\t-Danh sach sinh vien co dtb >=9\n");
				printf("\n\tMSSV	HoTen		Toan		Ly		Hoa		DTB	XepLoai\n");
				LietKe(l);
				printf("\n\t(NHAN PHIM BAT KY DE QUAY VE MENU CHUC NANG)");
				getch();
				system("cls");
				break;
			}
			default:
				if(chucnang!=27)
				{
					printf("\tKhong co chuc nang nay.");
					printf("\n\t(NHAN PHIM BAT KY DE QUAY VE MENU CHUC NANG)");
					getch();
					system("cls");
				}	
		}
	}while(chucnang!=27);
	return 0;
}
