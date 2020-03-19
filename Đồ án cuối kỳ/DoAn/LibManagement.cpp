// DoAn.cpp : Library Management Program
// author: Duy_Pham and Minh_Hung
// MSSV: 1712018 && 1712049

#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include<Windows.h>
#include "ChucNang1.h"
#include "Function2.h"
#include "Function3.h"
#include "ChucNang4,5.h"
#include "ChucNang6.h"
#include "UI.h"

#define userlist "C:\\LibManagement\\userlist.bin" 
#define root_user "root_user"
#define root_pass "admin123"



char *currenUser=NULL;
int rank;

char *tchar_to_string(_TCHAR *widechar)
{
	int size = 0;
	while ((char)widechar[size] != '/0')
	{
		size++;
	}
	size++;
	char *charpointer = new char[size];
	wcstombs(charpointer, widechar, size);
	return charpointer;
} 

void chep_thong_tin(char name[], char pass[], _TCHAR *argv[])
{
	int i = 0;
	while (argv[1][i] != '\0')
	{
		name[i] = argv[1][i];
		i++;
	}
	name[i] = '\0';
	i = 0;
	while (argv[2][i] != '\0')
	{
		pass[i] = argv[2][i];
		i++;
	}
	pass[i] = '\0';
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f;
	int ch;
	char username[50];
	char pass[50];
	chep_thong_tin(username, pass, argv);
	if ((f = fopen(userlist, "rb")) == NULL)
	{
		if (strcmp(username, root_user) == 0 && strcmp(pass, root_pass) == 0)
		{
			create_userfile();
			printf("DANG NHAP THANH CONG ! \n");
			currenUser = username;
			rank = 0;
		}
		else
		{
			printf("SAI THONG TIN TAI KHOAN \n");
		}
	}
	else
	{
		User check_user;
		f = fopen(userlist, "rb");
		while (!feof(f))
		{
			fread(&check_user, sizeof(User), 1, f);
			if (strcmp(username, check_user.Account.username) == 0 && strcmp(pass, check_user.Account.password) == 0)
			{
				printf("DANG NHAP THANH CONG ! \n");
				rank = check_user.rank;
				currenUser = check_user.Account.username;
				break;
			}
		}
	}
	if (currenUser != NULL)
	{
		loading();
		system("cls");
		menu(rank, &currenUser);
	}
	else
	{
		printf("Sai thong tin dang nhap \n");
	}
}
 












