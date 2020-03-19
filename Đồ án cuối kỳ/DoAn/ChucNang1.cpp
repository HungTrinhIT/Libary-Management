#include "stdafx.h"
#include "ChucNang1.h"
#include "UI.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <Windows.h>


#define userlist "C:\\LibManagement\\userlist.bin"

void userFunctionMenu(int rank, char **currenUser)
{
	system("cls");

	printf("\n\t\t     ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป");
	printf("\n\t\t     บ                           QUAN LY TAI KHOAN                          บ");
	printf("\n\t\t     ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน");
	printf("\n\t\t     บ                                  ณ                                   บ");
	printf("\n\t\t     บ1 .DANG NHAP                      ณ2. DANG XUAT/THOAT                 บ");
	printf("\n\t\t     บ                                  ณ                                   บ");
	printf("\n\t\t     บ3 .THAY DOI MAT KHAU              ณ4. CAP NHAT THONG TIN CA NHAN      บ");
	printf("\n\t\t     บ                                  ณ                                   บ");
	if (rank == 0)
	{
		printf("\n\t\t     บ5 .TAO NGUOI DUNG                 ณ6. PHAN QUYEN NGUOI DUNG           บ");
		printf("\n\t\t     บ                                  ณ                                   บ");
	}
	printf("\n\t\t     ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n");
	printf("\t\t      0. Quay lai man hinh chinh \n");
	printf("\n\t\t\tNHAP CHUC NANG MUON THUC HIEN: ");

	int ch;
	scanf_s("%i", &ch);
	switch (ch)
	{
	case 0:
		system("cls");
		menu(rank, currenUser);
		break;
	case 1:
		printf("Ban da dang nhap ! \n");
		break;
	case 2:
		currenUser = NULL;
		exit(0);
		break;
	case 3:
		doi_mat_khau(currenUser);
		break;
	case 4:
		cap_nhat_thong_tin(currenUser);
		break;
	case 5:
		if (rank != 0)
		{
			printf("\t\t\tKhong co chuc nang nay !\n");
			break;
		}
		else
		{
			tao_nguoi_dung();
			break;
		}
	case 6:
		if (rank != 0)
		{
			printf("\t\t\tKhong co chuc nang nay !\n");
			break;
		}
		else
		{
			phan_quyen_nguoi_dung();
			break;
		}
	default:
		printf("\t\t\tKhong co chuc nang nay ! \n");
		break;
	}

	Select:
	printf("\n\n\t\t\tNHAN ENTER DE TIEP TUC / NHAN ESC DE QUAY LAI MAN HINH CHINH: ");
	char c = _getch();
	if (c == 13)
	{
		system("cls");
		userFunctionMenu(rank, currenUser);
	}
	if (c == 27)
	{
		system("cls");
		menu(rank, currenUser);
	}
	else
	{
		goto Select;
	}

} 

void create_userfile()		// Khoi tao file nguoi dung khi khoi chay lan dau
{
	char root_username[] = "root_user";
	char root_pass[] = "admin123";
	User root_user;
	FILE *f = fopen(userlist, "rb");
	if (f == NULL)
	{
		_mkdir("C:\\LibManagement");
		f = fopen(userlist, "wb+");
		User root_user;
		strcpy(root_user.Account.username,root_username);
		strcpy(root_user.Account.password, root_pass);
		root_user.rank = 0;
		fwrite(&root_user, sizeof(User), 1, f);
		fclose(f);
	}
	else
	{
		fclose(f);
	}
}

void loadFileUserList(User **user_data, int &n)		// Load du lieu tu file len bo nho trong
{
	FILE *f = fopen(userlist, "rb");
	if (f == NULL)
	{
		printf("Da xay ra loi \n");
		exit(0);
	}
	else
	{
		rewind(f);
		n = 0;
		*user_data = (User*)malloc(sizeof(User));
		do
		{
			fread(*(user_data)+n, sizeof(User), 1, f);
			n++;
			*user_data = (User*)realloc(*user_data, (n + 2) * sizeof(User));
		} while (!feof(f));
	}
	n--;
	fclose(f);
}

void nhap_pass(char password[])		// Ham giau ki tu khi nhap pass
{
	char ch;
	int pos = 0;
	while (true)
	{
		ch = _getch();
		if (ch == 13)		// ch == ENTER
		{
			break;
		}
		if (ch == 8)			// ch==BACKSPACE
		{
			printf("\b \b");
			password[--pos] = '\0';
		}
		else
		{
			printf("*");
			password[pos++] = ch;
			password[pos] = '\0';
		}
		if (pos <= 0)
			pos = 0;
	}
}
void tao_nguoi_dung()
{
	printf("\n \n");
	printf("\t\t\t\t\t\tDANG KI TAI KHOAN \n\n");
	printf("\n");
	FILE *f;
	User new_user;
	User check_user;
	bool isExisted;		// Kiem tra ten dang nhap da ton tai
	char new_username[50];
	f = fopen(userlist, "ab+");
	do
	{
		isExisted = false;
		printf("\t\t\tNhap ten dang nhap: ");
		rewind(stdin);
		gets_s(new_username);
		while (!feof(f))
		{
			fread(&check_user, sizeof(User), 1, f);
			if (strcmp(check_user.Account.username,new_username)==0)
			{
				isExisted = true;
			}
		}
		if (isExisted == true)
		{
			printf("\t\t\tTEN DANG NHAP DA TON TAI ! \n");
		}
	} while (isExisted == true);
	strcpy(new_user.Account.username, new_username);
	printf("\t\t\tNhap mat khau: ");
	nhap_pass(new_user.Account.password);
	printf("\n\t\t\tDIEN THONG TIN CA NHAN: \n");
	
	printf("\t\t\tHo va ten: ");
	rewind(stdin);
	gets_s(new_user.Information.hoten);
	
	do
	{
		printf("\t\t\tNgay thang nam sinh (dd/mm/yyyy):  ");
		rewind(stdin);
		gets_s(new_user.Information.DoB);
		if (strlen(new_user.Information.DoB) != 10)
			printf("\t\t\tXin nhap dung dinh dang ! \n");
	} while (strlen(new_user.Information.DoB) != 10);
	
	printf("\t\t\tNhap so CMND: ");
	rewind(stdin);
	gets_s(new_user.Information.CMND);
	
	printf("\t\t\tDia chi: ");
	rewind(stdin);
	gets_s(new_user.Information.diachi);
	
	do
	{
		printf("\t\t\tNhap gioi tinh (Nhap 1 neu la nam / Nhap 0 neu la nu): ");
		scanf_s("%i", &new_user.Information.gioitinh);
		if (new_user.Information.gioitinh != 1 && new_user.Information.gioitinh != 0)
			printf("\t\t\tNhap sai \n");
	} while (new_user.Information.gioitinh != 1 && new_user.Information.gioitinh != 0);
	
	new_user.status = 1;
	
	do
	{
		printf("\t\t\tNhap loai nguoi dung (Nhap 1 neu la quan ly / Nhap 2 neu la chuyen vien): ");
		scanf_s("%i", &new_user.rank);
		if (new_user.rank != 1 && new_user.rank != 2)
			printf("\t\t\tNhap sai \n");
	} while (new_user.rank != 1 && new_user.rank != 2);
	
	fseek(f, 0, SEEK_END);
	fwrite(&new_user, sizeof(User), 1, f);
	
	printf("\t\t\tDANG KI THANH CONG ! \n");
	fclose(f);
}

int dang_nhap( int &rank, char *&currenUser)
{
	printf("\n \n");
	printf("\t\t\t\t\t\tDANG NHAP \n");
	printf("\n");
	FILE *f;
	User user;
	char username[50];
	char password[50];
	printf("\t\t\tNhap ten dang nhap: ");
	rewind(stdin);
	gets_s(username);
	printf("\t\t\tNhap mat khau: ");
	rewind(stdin);
	nhap_pass(password);
	f = fopen(userlist, "rb");
	if (f != NULL)
	{
		while (!feof(f))
		{
			fread(&user, sizeof(User), 1, f);
			if (strcmp(username, user.Account.username) == 0 && strcmp(password, user.Account.password) == 0)
			{
				rank = user.rank;
				printf("\n\t\t\tDANG NHAP THANH CONG ! \n");
				currenUser = user.Account.username;
				return 1;
			}
		}
		printf("\n\t\t\tMAT KHAU HOAC TEN DANG NHAP KHONG CHINH XAC ! \n");
		currenUser = NULL;
		return 0;
	}
	else  // Loi mo file
	{
		printf("\n\t\t\tLOI XAC THUC TU HE THONG. THU LAI SAU ! \n");
		currenUser = NULL;
		return 0;
	}
	fclose(f);
}

void doi_mat_khau(char **currenUser)
{
	printf("\n \n");
	printf("\t\t\t\t\t\tDOI MAT KHAU \n\n");
	printf("\n");
	char newpass[50];
	char oldpass[50];
	FILE *f;
	User *user_data;
	int n;
	
	f = fopen(userlist, "rb");
	loadFileUserList(&user_data, n);	// Load du lieu tu file vao bo nho trong
	for (int i = 0; i < n; i++)
	{
		if (strcmp(*currenUser,(user_data+i)->Account.username)==0)
		{
			printf("\t\t\tVi ly do bao mat moi ban nhap mat khau cu: ");
			nhap_pass(oldpass);
			if (strcmp(oldpass, (user_data + i)->Account.password)==0)
			{
				printf("\n\t\t\tNhap mat khau moi: ");
				nhap_pass(newpass);
				strcpy((user_data + i)->Account.password, newpass);
				
				fclose(f);

				f = fopen(userlist, "wb");
				fwrite(user_data, sizeof(User), n, f);
				printf("\n\t\t\tCap nhat mat khau thanh cong ! \n");
				fclose(f);
				
				break;
			}
			else
			{
				printf("\n\t\t\tMat khau khong dung ! \n");
				break;
			}
		}
	}
}


void cap_nhat_thong_tin(char **currenUser)
{
	printf("\n \n");
	printf("\t\t\t\t\t\tCAP NHAT THONG TIN \n\n");
	printf("\n");
	char ch[50];
	int n;
	User *user_data;
	FILE *f;
	f = fopen(userlist, "rb");
	loadFileUserList(&user_data, n);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(*currenUser, (user_data + i)->Account.username) == 0)
		{
			printf("\t\t\tNhap ho va ten: ");
			rewind(stdin);
			gets_s(ch);
			strcpy((user_data + i)->Information.hoten, ch);

			printf("\t\t\tNhap so CMND: ");
			rewind(stdin);
			gets_s(ch);
			strcpy((user_data + i)->Information.CMND, ch);

			printf("\t\t\tNhap ngay thang nam sinh (dd/mm/yyyy): ");
			rewind(stdin);
			gets_s(ch);
			strcpy((user_data + i)->Information.DoB, ch);

			printf("\t\t\tNhap dia chi: ");
			rewind(stdin);
			gets_s(ch);
			strcpy((user_data + i)->Information.diachi, ch);

			printf("\t\t\tNhap gioi tinh (Nhap 1 neu la nam / 0 neu la nu): ");
			rewind(stdin);
			gets_s(ch);
			(user_data + i)->Information.gioitinh = atoi(ch);

			break;
		}
	}
	fclose(f);

	f = fopen(userlist, "wb");
	fwrite(user_data, sizeof(User), n, f);
	fclose(f);

	printf("\t\t\tCap nhat thong tin thanh cong ! \n");

}

void phan_quyen_nguoi_dung()
{
	printf("\n \n");
	printf("\t\t\t\t\t\tPHAN QUYEN NGUOI DUNG \n\n");
	printf("\n");
	FILE *f;
	User *user;
	int n;
	char username[50];
	loadFileUserList(&user, n);
	printf("\n\t\t\tDanh sach nguoi dung: \n");
	for (int i = 0; i < n; i++)
	{
		if ((user + i)->rank ==1 || (user+i)->rank==2)
		{
			printf("%i. %s",i, (user + i)->Account.username);
			printf(": ");
			if ((user + i)->rank == 1)
				printf("\t\t\tQuan ly thu vien \n");
			if ((user + i)->rank == 2)
				printf("\t\t\tChuyen vien \n");
		}
	}
	printf("\n");
	printf("\t\t\tNhap ten nguoi dung muon phan quyen lai: ");
	rewind(stdin);
	gets_s(username);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(username, (user + i)->Account.username) == 0)
		{
			if ((user + i)->rank == 1)
			{
				printf("\t\t\tNguoi dung %s co quyen QUAN LY THU VIEN \n", (user + i)->Account.username);	
				printf("\t\t\tNhan y de doi / n de huy: ");
				char ch;
				scanf_s("%c", &ch);
				if (ch == 'y')
				{
					(user + i)->rank = 2;
					printf("\t\t\tDa doi quyen nguoi dung ! \n");
				}
				else
				{
					printf("\t\t\tQuyen nguoi dung khong thay doi ! \n");
				}
			}
			if ((user + i)->rank == 2)
			{
				printf("\t\t\tNguoi dung %s co quyen CHUYEN VIEN \n", (user + i)->Account.username);
				printf("\t\t\tNhan y de doi / n de huy: ");
				char ch;
				scanf_s("%c", &ch);
				if (ch == 'y')
				{
					(user + i)->rank = 1;
					printf("\t\t\tDa doi quyen nguoi dung ! \n");
				}
				else
				{
					printf("\t\t\tQuyen nguoi dung khong thay doi ! \n");
				}
			}
		}
	}
}



