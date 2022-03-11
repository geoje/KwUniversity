
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
	printf("               ******** 마당서점 ********\n");
	printf("--------------------------------------------------------\n");
	printf("(설명)     : 도서와 고객 관리 프로그램\n");
	printf("           (1) 도서의 검색 및 관리\n");
	printf("           (2) 고객의 검색과 관리\n");
	printf("           (3) 고객의 도서 판매 관리\n");
	printf("--------------------------------------------------------\n");
	printf("시작하시려면 아무키나 눌러주세요^.^\n");
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
	printf("\t\t\t1.도서관리\n");
	printf("\t\t\t2.고객관리\n");
	printf("\t\t\t3.도서판매관리\n");
	printf("\t\t\t4.종료\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t원하는 번호를 선택하세요:");
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
	default : printf("잘못선택하였습니다!!!\n");
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
	printf("\t\t\t0.모든 고객보기\n");
	printf("\t\t\t1.고객찾기\n");
	printf("\t\t\t2.고객등록하기\n");
	printf("\t\t\t3.고객지우기\n");
	printf("\t\t\t4.고객수정\n");
	printf("\t\t\t5.메인메뉴\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t원하는 번호를 선택하세요:");
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
	default : printf("잘못선택하였습니다!!!\n");
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
	printf("\t\t\t0.모든 도서보기\n");
	printf("\t\t\t1.도서찾기\n");
	printf("\t\t\t2.도서등록하기\n");
	printf("\t\t\t3.도서지우기\n");
	printf("\t\t\t4.도서수정\n");
	printf("\t\t\t5.메인메뉴\n");
	printf("\t\t\t------------------------------------\n");
	printf("\t\t\t원하는 번호를 선택하세요:");
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
	default : printf("잘못선택하였습니다!!!\n");
		book_menu();
	}
}

void give_take()
{
	int j;
	/* clrscr(); */
	system("cls");
	
	fflush(stdin); // 09/05: 버퍼비우기.
	printf("고객번호를 입력하세요 : ");
	gets(tmp_number);
	j = is_client(tmp_number);
	if(j == 0)
	{
		printf("\n회원이 아닙니다...확인후 다시 시도해주세요");
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
				printf("찾았습니다!\n");
				printf("고객이름 : %s\n",cp->name);
				printf("고객번호 : %s\n",cp->number);
				printf("고객주소 : %s\n",cp->address);
				printf("판매목록 : %s\n",cp->list);
				getchar();
				printf("목록을 입력하세요 :");
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
		printf("찾지못하였습니다\n");
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
	
	printf("고객이름 :");
	gets(cp->name);
	printf("\n고객번호 :");
	gets(cp->number);
	printf("\n주소 :");
	gets(cp->address);
	cp->empty = 1;
	fp = fopen("./madangclient.dat","ab+");
	//	getchar();
	rewind(fp);// 0905: 파일의 가장 처음 부분으로 시작위치를 옮기기.

	while(fread(cp1,sizeof(Client),1,fp) != 0){
	
		i = ftell(fp);  //0905: 현재의 화일 포인터( 읽기/쓰기 작업의 위치로서 화일의 시작부분에서 부터의 offset 바이트 수 )를 반환합니다.
		
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
	printf("\n 도서번호 : ");
	gets(bp->b_number);
	printf("   제목   : ");
	gets(bp->b_name);
	printf("  출판사  : ");
	gets(bp->publisher);
	printf("   가격   : ");
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
				printf("고객이름 : %s\n",cp->name);
				printf("고객번호 : %s\n",cp->number);
				printf("고객주소 : %s\n",cp->address);
				printf("--------------------------\n");
			}
	getchar();
}
void c_search()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("고객번호를 입력하세요:");
	gets(tmp_number);
	fp = fopen("./madangclient.dat","rb");
	cp=(Client *)calloc(1,sizeof(Client));
	

	if(strcmp(tmp_number,"")==0){
		while(fread(cp,sizeof(Client),1,fp) != 0){
			if(cp->empty !=0){
				printf("고객이름 : %s\n",cp->name);
				printf("고객번호 : %s\n",cp->number);
				printf("고객주소 : %s\n",cp->address);
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
				printf("찾았습니다!\n");
				printf("고객이름 : %s\n",cp->name);
				printf("고객번호 : %s\n",cp->number);
				printf("고객주소 : %s\n",cp->address);
				fclose(fp);
				getchar();
				return;
			}
			
		}
		fclose(fp);
		printf("찾지 못하였습니다!!\n");
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
	printf("                           도서목록 \n");
	printf("-------------------------------------------------------------\n");
	printf("도서번호 :        제목        :        출판사      :  가격 \n");
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
	printf("도서번호를 입력하세요:");
	gets(tmp_number);
	fp = fopen("madangbook.dat","rb");
	bp=(Book *)calloc(1,sizeof(Book));

	if(strcmp(tmp_number,"")==0){
		while(fread(bp,sizeof(Book),1,fp) != 0){
			if(bp->b_empty!=0){
				printf("도서번호 : %s\n",bp->b_number);
				printf("제목     : %s\n",bp->b_name);
				printf("출판사   : %s\n",bp->publisher);
				printf("가격     : %s\n",bp->price);
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
				printf("찾았습니다!\n");
				printf("도서번호 : %s\n",bp->b_number);
				printf("제목     : %s\n",bp->b_name);
				printf("출판사   : %s\n",bp->publisher);
				printf("가격     : %s\n",bp->price);
				printf("--------------------------\n");
				fclose(fp);
				getchar();
				return;
			}
			
			
		}
		fclose(fp);
		printf("찾지 못하였습니다!!\n");
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
	printf("고객번호를 입력하세요 :");
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
			printf("찾았습니다!\n");
			printf("고객이름 : %s\n",cp->name);
			printf("고객번호 : %s\n",cp->number);
			printf("고객주소 : %s\n",cp->address);
			getchar();
			fclose(fp);
			printf("삭제하겠습니까?(y/n)");
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
	printf("찾지못하였습니다");
	getchar();
}

void b_delete()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("도서번호를 입력하세요 :");
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
			printf("찾았습니다!\n");
			printf("도서제목 : %s\n",bp->b_name);
			printf("도서번호 : %s\n",bp->b_number);
			printf("도서출판사 : %s\n",bp->publisher);
			printf("도서가격 : %s\n",bp->price);
			getchar();
			fclose(fp);
			printf("삭제하겠습니까?(y/n)");
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
	printf("찾지못하였습니다");
	getchar();
}
void c_update()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("고객번호를 입력하세요 :");
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
			printf("찾았습니다!\n");
			printf("고객이름 : %s\n",cp->name);
			printf("고객번호 : %s\n",cp->number);
			printf("고객주소 : %s\n",cp->address);
			getchar();
			printf("새로운 고객이름을 입력하세요 :");
			gets(cp->name);
			printf("\n새로운 고객번호를 입력하세요 :");
			gets(cp->number);
			printf("\n새로운 고객주소를 입력하세요 :");
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
	printf("찾지못하였습니다\n");
	getchar();
}

void update()
{
	/* clrscr(); */
	system("cls");
	fflush(stdin);
	printf("도서번호를 입력하세요 :");
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
			printf("찾았습니다!\n");
				printf("도서번호 : %s\n",bp->b_number);
				printf("제목     : %s\n",bp->b_name);
				printf("출판사   : %s\n",bp->publisher);
				printf("가격     : %s\n",bp->price);
				printf("--------------------------\n");
			getchar();
			printf("\n새로운 도서번호를 입력하세요 :");
			gets(bp->b_number);
			printf("새로운 도서제목을 입력하세요 :");
			gets(bp->b_name);
			printf("\n새로운 도서출판사를 입력하세요 :");
			gets(bp->publisher);
			printf("\n새로운 도서가격을 입력하세요 :");
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
	printf("찾지못하였습니다\n");
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
