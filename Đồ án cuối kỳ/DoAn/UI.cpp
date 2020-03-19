#include "stdafx.h"
#include "UI.h"
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "ChucNang1.h"
#include "ChucNang6.h"
#include "ChucNang4,5.h"
#include "Function2.h"
#include "Function3.h"


void info(int rank, char **currenUser)
{
	system("cls");
	printf("	\n			  ************** DO AN NHAP KY THUAT LAP TRINH ***************  \n");
	printf("				         CHUONG TRINH QUAN LY THU VIEN  \n\n");
	printf("	\t\t\tSINH VIEN 1:\n");
	printf("	\t\t\t\t*Sinh Vien  : Pham Hoang Phuoc Duy  \n");
	printf("	\t\t\t\t*Lop        : 17CTT1 \n");
	printf("	\t\t\t\t*MSSV       : 1712018\n");
	printf("	\t\t\t\t*Dien Thoai : 0949063841\n");
	printf("	\t\t\t\t*Email      : phuocduypham2502@gmail.com\n");
	printf("\n\n");
	printf("	\t\t\tSINH VIEN 2:\n");
	printf("	\t\t\t\t*Sinh Vien  : Trinh Vu Minh Hung  \n");
	printf("	\t\t\t\t*Lop        : 17CTT1 \n");
	printf("	\t\t\t\t*MSSV       : 1712049\n");
	printf("	\t\t\t\t*Dien Thoai : 012925112976\n");
	printf("	\t\t\t\t*Email      : minhhung.it99@gmail.com\n");

	printf("\n\t\t\tNHAN PHIM BAT KI DE QUAY LAI! ");
	char ch = _getch();
	system("cls");
	menu(rank, currenUser);
}

void menu(int rank, char **currenUser)
{

	// Chinh kich thuoc man hinh cmd
	HANDLE wHnd;
	HANDLE rHnd;

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SMALL_RECT windowSize = { 0, 0, 99, 44 };
	COORD bufferSize = { 100, 45 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);


	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 3);	// gray blue
	printf("\t\t\t\t+=======================================+    Tai khoan: %s \n", *currenUser);
	SetConsoleTextAttribute(hOut, 11);	// light blue
	printf("\t\t\t\t| +-----------------------------------+ | \n");
	printf("\t\t\t\t| |         Library Management        | | \n");
	SetConsoleTextAttribute(hOut, 14);	//yellow
	printf("\t\t\t\t| |            Version 1.0            | | \n");
	SetConsoleTextAttribute(hOut, 10);	// green
	printf("\t\t\t\t| |    Author: Duy_Pham && Minh Hung  | | \n");
	SetConsoleTextAttribute(hOut, 11);
	printf("\t\t\t\t| |        All rights reserved        | | \n");
	printf("\t\t\t\t| +-----------------------------------+ | \n");
	SetConsoleTextAttribute(hOut, 3);
	printf("\t\t\t\t+=======================================+ \n");
	SetConsoleTextAttribute(hOut, 14);	//yellow
	printf("\t\t\t========================================================\n");
	SetConsoleTextAttribute(hOut, 12);
	printf("\t\t\t\t               ____                           \n");
	printf("\t\t\t\t  |\\    /|    |____    |\\  |    |    |              \n");
	printf("\t\t\t\t  | \\  / |    |____    | \\ |    |    |           \n");
	printf("\t\t\t\t  |  \\/  |    |____    |  \\|    |____|                 \n");
	SetConsoleTextAttribute(hOut, 14);	//yellow
	printf("\n");
	printf("\t\t\t========================================================\n");
	SetConsoleTextAttribute(hOut, 3);	// gray blue
	printf("\t\t\t\t0 : About us ");
	printf("\t\t\t 7: Exit ");

	SetConsoleTextAttribute(hOut, 15);	// white
	printf("\n\t\t      ษออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออป");
	printf("\n\t\t      บ                            ณ                             บ");
	printf("\n\t\t      บ    1. QUAN LY TAI KHOAN    ณ     2. QUAN LY DOC GIA      บ");
	printf("\n\t\t      บ                            ณ                             บ");
	printf("\n\t\t      บ    3. QUAN LY SACH         ณ     4. LAP PHIEU MUON SACH  บ");
	printf("\n\t\t      บ                            ณ                             บ");
	printf("\n\t\t      บ    5. LAP PHIEU TRA SACH   ณ     6. THONG KE             บ");
	printf("\n\t\t      บ                            ณ                             บ");
	printf("\n\t\t      ศออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออผ\n");
	printf("\n");
	
	SetConsoleTextAttribute(hOut, 14);
	printf("\t\t\tNHAP MUC MUON THUC HIEN: ");
	SetConsoleTextAttribute(hOut, 15);	// white
	int ch;
	scanf_s("%i", &ch);
	switch (ch)
	{
	case 0:
		info(rank, currenUser);
		break;
	case 1:
		userFunctionMenu(rank,currenUser);
		break;
	case 2: 
		readerFunctionMenu(rank,currenUser);
		break;
	case 3:
		bookFunctionMenu(rank, currenUser);
		break;
	case 4:
		lapPhieuMuonSach(rank,currenUser);
		break;
	case 5:
		lapPhieuTraSach(rank,currenUser);
		break;
	case 6: 
		statisticMenu(rank,currenUser);
		break;
	case 7:
		currenUser = NULL;
		exit(0);
	default:
		printf("\t\t\tKHONG CO MUC NAY! \n");
	}
}


void loading()
{
	printf("Khoi tao chuong trinh: ");
	for (int i = 0; i <= 100; i++)
	{
		printf("%i", i);
		Sleep(50);
		if (i <= 9)
		{
			printf("\b");
		}
		else if (i<=100)
		{
			printf("\b");
			printf("\b");
		}
	}
	printf("Done ! \n");
}



