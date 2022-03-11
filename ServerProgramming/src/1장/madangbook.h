#ifndef _u_book_h
#define _u_book_h

typedef struct
{
	char b_number[5];
	char b_name[20];
	char publisher[20];
	char price[5];
	int b_empty;
} Book;

typedef struct
{
	char name[20];  //�̸�
	char number[5];  //����ȣ
	char address[20]; //�ּ�
	char list[30];  //����å ����Ʈ.
	int empty;    // ȸ������ ����.1= ����� 0= ������.
} Client;



FILE *fp;
Book *bp,*bp1;
Client *cp,*cp1;
int i,num;
char yes_no;
char tmp_number[5];

void intro();
void main_menu();
void client_menu();
void book_menu();
void give_take();
int is_client(char number[5]);
void c_insert();
void insert();
void c_search();
void c_searchall();
void search();
void searchall();
void c_delete();
void b_delete();
void c_update();
void update();

#endif
