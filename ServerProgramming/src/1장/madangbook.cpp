
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h> 
#include "madangbook.h"
#include <CType.h>

void intro()
{
	/* clrscr(); */ int ch;
	system("cls");
	printf("\n--------------------------------------------------------\n");
	printf("               ******** ���缭�� ********\n");
	printf("--------------------------------------------------------\n");
	printf("(����)     : ������ �� ���� ���α׷�\n");
	printf("           (1) ������ �˻� �� ����\n");
	printf("           (2) ���� �˻��� ����\n");
	printf("           (3) ���� ���� �Ǹ� ����\n");
	printf("--------------------------------------------------------\n");
	printf("�����Ͻ÷��� �ƹ�Ű�� �����ּ���^.^\n");
	printf("--------------------------------------------------------\n");
	ch=_getch();
}


void main_menu()
{
	/* clrscr();  */
	system("cls");
	fflush(stdin);
	printf("\n\n\n\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t1.��������\n");
	printf("\t\t\t2.������\n");
	printf("\t\t\t3.�����ǸŰ���\n");
	printf("\t\t\t4.����\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t���ϴ� ��ȣ�� �����ϼ���:");
	scanf("%d",&num);
	switch(num)
	{
	case 1 : book_menu();
		break;
	case 2 : client_menu();
		break;
	case 3 : give_take();
		break;
	case 4 : exit(1);
		break;
	default : printf("�߸������Ͽ����ϴ�!!!\n");
		main_menu();
	}
}

void client_menu()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("\n\n\n\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t0.��� ������\n");
	printf("\t\t\t1.��ã��\n");
	printf("\t\t\t2.������ϱ�\n");
	printf("\t\t\t3.�������\n");
	printf("\t\t\t4.������\n");
	printf("\t\t\t5.���θ޴�\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t���ϴ� ��ȣ�� �����ϼ���:");
	scanf("%d",&num);
	switch(num)
	{
	case 0 : c_searchall();
		break;
	case 1 : c_search();
		break;
	case 2 : c_insert();
		break;
	case 3 : c_delete();
		break;
	case 4 : c_update();
		break;
	case 5 : main_menu();
		break;
	default : printf("�߸������Ͽ����ϴ�!!!\n");
		book_menu();
	}
}

void book_menu()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("\n\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t0.��� ��������\n");
	printf("\t\t\t1.����ã��\n");
	printf("\t\t\t2.��������ϱ�\n");
	printf("\t\t\t3.���������\n");
	printf("\t\t\t4.��������\n");
	printf("\t\t\t5.���θ޴�\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t���ϴ� ��ȣ�� �����ϼ���:");
	scanf("%d",&num);
	switch(num)
	{
	case 0 : searchall();
		break;
	case 1 : search();
		break;
	case 2 : insert();
		break;
	case 3 : b_delete();
		break;
	case 4 : update();
		break;
	case 5 : main_menu();
		break;
	default : printf("�߸������Ͽ����ϴ�!!!\n");
		book_menu();
	}
}

void give_take()
{
	int j;
	/* clrscr(); */
	system("cls");
	
	fflush(stdin); // 09/05: ���ۺ���.
	printf("����ȣ�� �Է��ϼ��� : ");
	gets(tmp_number);
	j = is_client(tmp_number);
	if(j == 0)
	{
		printf("\nȸ���� �ƴմϴ�...Ȯ���� �ٽ� �õ����ּ���");
		getchar();
		return;
	}
	if(j == 1)
	{
		
		fp = fopen("./madangclient.dat","rb+");
		cp = (Client *)calloc(1,sizeof(Client));
	
		while(fread(cp,sizeof(Client),1,fp) != 0)
		{
			
			i = ftell(fp);
			if(strcmp(cp->number,tmp_number) == 0)
			{
				if(cp->empty == 0)
					break;
				printf("ã�ҽ��ϴ�!\n");
				printf("���̸� : %s\n",cp->name);
				printf("����ȣ : %s\n",cp->number);
				printf("���ּ� : %s\n",cp->address);
				printf("�ǸŸ�� : %s\n",cp->list);
				getchar();
				printf("����� �Է��ϼ��� :");
				gets(cp->list);
				fclose(fp);
				fp = fopen("./madang.dat","rb+");
				fseek(fp,i - sizeof(Client),SEEK_SET);
				fwrite(cp,sizeof(Client),1,fp);
				fclose(fp);
				return;
			}
		}
		fclose(fp);
		printf("ã�����Ͽ����ϴ�\n");
		getchar();
	}
	
}

int is_client(char tmp_number[5] )
{
	/* clrscr(); */
	
	///system("cls");
	fflush(stdin);
	fp = fopen("./madangclient.dat","r");
	cp=(Client *)calloc(1,sizeof(Client));
	//	cp = 
	//	printf("%s",cp->name);
	while(fread(cp,sizeof(Client),1,fp) != -1)
	{
		if(strcmp(cp->number,tmp_number) == 0)
		{
			if(cp->empty == 0)
				break;
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

void c_insert()
{
	cp = (Client *)calloc(1,sizeof(Client));
	cp1 = (Client *)calloc(1,sizeof(Client));
	/* clrscr(); */
	//	system("cls");
	fflush(stdin);
	
	printf("���̸� :");
	gets(cp->name);
	printf("\n����ȣ :");
	gets(cp->number);
	printf("\n�ּ� :");
	gets(cp->address);
	cp->empty = 1;
	fp = fopen("./madangclient.dat","ab+");
	//	getchar();
	rewind(fp);// 0905: ������ ���� ó�� �κ����� ������ġ�� �ű��.

	while(fread(cp1,sizeof(Client),1,fp) != 0){
	
		i = ftell(fp);  //0905: ������ ȭ�� ������( �б�/���� �۾��� ��ġ�μ� ȭ���� ���ۺκп��� ������ offset ����Ʈ �� )�� ��ȯ�մϴ�.
		
		if( cp1->empty == 0)
		{
		
			fclose(fp);
			 fp = fopen("./madang.dat","rb+");   //Open a binary file for read/write
			fseek(fp,i-sizeof(Client),SEEK_SET);
			fwrite(cp,sizeof(Client),1,fp);
			 fclose(fp);
			return;
		}
	}
		fclose(fp);
		fp = fopen("./madangclient.dat","ab+");  //Open a binary file for read/write
	fwrite(cp,sizeof(Client),1,fp);
	fclose(fp);
}

void insert()
{
	bp = (Book *)calloc(1,sizeof(Book));
	bp1 = (Book *)calloc(1,sizeof(Book));
	/* clrscr(); */
	// system("cls");
	fflush(stdin);
	printf("\n ������ȣ : ");
	gets(bp->b_number);
	printf("   ����   : ");
	gets(bp->b_name);
	printf("  ���ǻ�  : ");
	gets(bp->publisher);
	printf("   ����   : ");
	gets(bp->price);
	bp->b_empty = 1;
	
	
	fp = fopen("madangbook.dat","a");
	rewind(fp);  
	while(fread(bp1,sizeof(Book),1,fp) != 0)
	   {
		i = ftell(fp);
		if( bp1->b_empty == 0)
	       {
			fclose(fp);
			fp = fopen("madangbook.dat","rb+");
			fseek(fp,i-sizeof(Book),SEEK_SET);
			fwrite(bp,sizeof(Book),1,fp);
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	fp = fopen("madangbook.dat","ab+");
	fwrite(bp,sizeof(Book),1,fp);
	fclose(fp);
}

void c_searchall() /* Uchang */
{
		/* clrscr(); */
	system("cls");
	fflush(stdin);
	fp = fopen("./madangclient.dat","rb");
	cp=(Client *)calloc(1,sizeof(Client));

	while(fread(cp,sizeof(Client),1,fp) != 0){
				printf("���̸� : %s\n",cp->name);
				printf("����ȣ : %s\n",cp->number);
				printf("���ּ� : %s\n",cp->address);
				printf("--------------------------\n");
			}
	getchar();
}
void c_search()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("����ȣ�� �Է��ϼ���:");
	gets(tmp_number);
	fp = fopen("./madangclient.dat","rb");
	cp=(Client *)calloc(1,sizeof(Client));
	

	if(strcmp(tmp_number,"")==0){
		while(fread(cp,sizeof(Client),1,fp) != 0){
			if(cp->empty !=0){
				printf("���̸� : %s\n",cp->name);
				printf("����ȣ : %s\n",cp->number);
				printf("���ּ� : %s\n",cp->address);
				printf("--------------------------\n");
			}
	
		}
		
		
	}else{
		while(fread(cp,sizeof(Client),1,fp) != 0)
		{
			if(strcmp(cp->number,tmp_number) == 0)
			{
				if(cp->empty == 0)
					break;
				printf("ã�ҽ��ϴ�!\n");
				printf("���̸� : %s\n",cp->name);
				printf("����ȣ : %s\n",cp->number);
				printf("���ּ� : %s\n",cp->address);
				fclose(fp);
				getchar();
				return;
			}
			
		}
		fclose(fp);
		printf("ã�� ���Ͽ����ϴ�!!\n");
		getchar();
	}
	getchar();
}		

void searchall() /* uchang */
{
		/* clrscr();  */
	//system("clear");
	//system("cls");
	fflush(stdin);
	fp = fopen("madangbook.dat","rb");
	bp=(Book *)calloc(1,sizeof(Book));
	printf("\n\n");
	printf("-------------------------------------------------------------\n");
	printf("                           ������� \n");
	printf("-------------------------------------------------------------\n");
	printf("������ȣ :        ����        :        ���ǻ�      :  ���� \n");
	printf("-------------------------------------------------------------\n");
	while(fread(bp,sizeof(Book),1,fp) != 0){
			if(bp->b_empty!=0){
				printf("%9s:",bp->b_number);
				printf("%20s:",bp->b_name);
				printf("%20s:",bp->publisher);
				printf(" %5s\n",bp->price);
		}
	}
	printf("-------------------------------------------------------------\n");
	getchar();
}

void search()
{
	/* clrscr();  */
	//system("clear");
	system("cls");
	fflush(stdin);
	printf("������ȣ�� �Է��ϼ���:");
	gets(tmp_number);
	fp = fopen("madangbook.dat","rb");
	bp=(Book *)calloc(1,sizeof(Book));

	if(strcmp(tmp_number,"")==0){
		while(fread(bp,sizeof(Book),1,fp) != 0){
			if(bp->b_empty!=0){
				printf("������ȣ : %s\n",bp->b_number);
				printf("����     : %s\n",bp->b_name);
				printf("���ǻ�   : %s\n",bp->publisher);
				printf("����     : %s\n",bp->price);
				printf("--------------------------\n");
			}
			
		}
		
		
	}else{
		while(fread(bp,sizeof(Book),1,fp) != -1)
		{
			if(strcmp(bp->b_number,tmp_number) == 0)
			{
				if(bp->b_empty == 0)
					break;
				printf("ã�ҽ��ϴ�!\n");
				printf("������ȣ : %s\n",bp->b_number);
				printf("����     : %s\n",bp->b_name);
				printf("���ǻ�   : %s\n",bp->publisher);
				printf("����     : %s\n",bp->price);
				printf("--------------------------\n");
				fclose(fp);
				getchar();
				return;
			}
			
			
		}
		fclose(fp);
		printf("ã�� ���Ͽ����ϴ�!!\n");
		getchar();
	}
	getchar();
}


void c_delete()
{
	char yes_no;
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("����ȣ�� �Է��ϼ��� :");
	gets(tmp_number);
	fp = fopen("./madangclient.dat","rb+");
	cp=(Client *)calloc(1,sizeof(Client));
	while(fread(cp,sizeof(Client),1,fp) != 0)
	{
		i = ftell(fp);
		if(strcmp(cp->number,tmp_number) == 0)
		{
			if(cp->empty == 0)
				break;
			printf("ã�ҽ��ϴ�!\n");
			printf("���̸� : %s\n",cp->name);
			printf("����ȣ : %s\n",cp->number);
			printf("���ּ� : %s\n",cp->address);
			getchar();
			fclose(fp);
			printf("�����ϰڽ��ϱ�?(y/n)");
			scanf("%c",&yes_no);
			if(yes_no == 'y')
			{
				fp = fopen("./madang.dat","rb+");
				fseek(fp,i - sizeof(Client),SEEK_SET);
				cp->empty = 0;
				fwrite(cp,sizeof(Client),1,fp);
				fclose(fp);
			}
			return;
		}
	}
	fclose(fp);
	printf("ã�����Ͽ����ϴ�");
	getchar();
}

void b_delete()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("������ȣ�� �Է��ϼ��� :");
	gets(tmp_number);
	fp = fopen("madangbook.dat","rb+");
	bp=(Book *)calloc(1,sizeof(Book));
	while(fread(bp,sizeof(Book),1,fp) != 0)
	{
		i = ftell(fp);
		if(strcmp(bp->b_number,tmp_number) == 0)
		{
			if(bp->b_empty == 0)
				break;
			printf("ã�ҽ��ϴ�!\n");
			printf("�������� : %s\n",bp->b_name);
			printf("������ȣ : %s\n",bp->b_number);
			printf("�������ǻ� : %s\n",bp->publisher);
			printf("�������� : %s\n",bp->price);
			getchar();
			fclose(fp);
			printf("�����ϰڽ��ϱ�?(y/n)");
			scanf("%c",&yes_no);
			if(yes_no == 'y')
			{
				fp = fopen("madangbook.dat","rb+");
				fseek(fp,i - sizeof(Book),SEEK_SET);
				bp->b_empty = 0;
				fwrite(bp,sizeof(Book),1,fp);
				fclose(fp);
			}
			return;
		}
	}
	fclose(fp);
	printf("ã�����Ͽ����ϴ�");
	getchar();
}
void c_update()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("����ȣ�� �Է��ϼ��� :");
	gets(tmp_number);
	fp = fopen("./madangclient.dat","rb+");
	cp = (Client *)calloc(1,sizeof(Client));
	while(fread(cp,sizeof(Client),1,fp) != -1)
	{
		i = ftell(fp);
		if(strcmp(cp->number,tmp_number) == 0)
		{
			if(cp->empty == 0)
				break;
			printf("ã�ҽ��ϴ�!\n");
			printf("���̸� : %s\n",cp->name);
			printf("����ȣ : %s\n",cp->number);
			printf("���ּ� : %s\n",cp->address);
			getchar();
			printf("���ο� ���̸��� �Է��ϼ��� :");
			gets(cp->name);
			printf("\n���ο� ����ȣ�� �Է��ϼ��� :");
			gets(cp->number);
			printf("\n���ο� ���ּҸ� �Է��ϼ��� :");
			gets(cp->address);
			fclose(fp);
			fp = fopen("./madangclient.dat","rb+");
			fseek(fp,i - sizeof(Client),SEEK_SET);
			fwrite(cp,sizeof(Client),1,fp);
			fclose(fp);
			getchar();
			return;
		}
	}
	fclose(fp);
	printf("ã�����Ͽ����ϴ�\n");
	getchar();
}

void update()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("������ȣ�� �Է��ϼ��� :");
	gets(tmp_number);
	fp = fopen("madangbook.dat","rb+");
	bp = (Book *)calloc(1,sizeof(Book));
	while(fread(bp,sizeof(Book),1,fp) != -1)
	{
		i = ftell(fp);
		if(strcmp(bp->b_number,tmp_number) == 0)
		{
			if(bp->b_empty == 0)
				break;
			printf("ã�ҽ��ϴ�!\n");
				printf("������ȣ : %s\n",bp->b_number);
				printf("����     : %s\n",bp->b_name);
				printf("���ǻ�   : %s\n",bp->publisher);
				printf("����     : %s\n",bp->price);
				printf("--------------------------\n");
			getchar();
			printf("\n���ο� ������ȣ�� �Է��ϼ��� :");
			gets(bp->b_number);
			printf("���ο� ���������� �Է��ϼ��� :");
			gets(bp->b_name);
			printf("\n���ο� �������ǻ縦 �Է��ϼ��� :");
			gets(bp->publisher);
			printf("\n���ο� ���������� �Է��ϼ��� :");
			gets(bp->price);
			fclose(fp);
			fp = fopen("madangbook.dat","rb+");
			fseek(fp,i - sizeof(Book),SEEK_SET);
			fwrite(bp,sizeof(Book),1,fp);
			fclose(fp);
			getchar();
			return;
		}
	}
	fclose(fp);
	printf("ã�����Ͽ����ϴ�\n");
	getchar();
}


main()
{
	intro();
	
	while(1)
	{
		
	       main_menu();
	}
}
