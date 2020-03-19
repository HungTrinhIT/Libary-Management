#include "stdafx.h"
#include "ChucNang4,5.h"
#include "Function3.h"
#include "Function2.h"
#include "UI.h"
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define borrowlist "C:\\LibManagement\\borrowlist.txt"
#define returnlist "C:\\LibManagement\\returnlist.text"
#define tmpborrowlist "C:\\LibManagement\\tmpborrowlist.txt"
#define listBook "C:\\LibManagement\\bookList.bin"
#define numbersOfBook "C:\\LibManagement\\countbook.bin"
#define ListDocGia  "C:\\LibManagement\\readerList.bin"
#define numbersOfReader "C:\\LibManagement\\countReader.bin"

void recountNumberOfBook(char *ISBN, int key )	// 0: tru so luong sach / 1: cong so luong sach
{
	Book *book;
	int n;
	docDuLieu(book, n);
	for (int i = 0; i < n; i++)
	{
		if (strcmp((book + i)->ISBN, ISBN) == 0)
		{
			if (key == 0)
			{
				(book + i)->soLuong = (book + i)->soLuong - 1;
			}
			else if (key == 1)
			{
				(book + i)->soLuong = (book + i)->soLuong + 1;
			}
			break;
		}
	}
	FILE *f = fopen(listBook, "wb+");
	fwrite(book, sizeof(Book), n, f);
	fclose(f);
}


void lapPhieuMuonSach(int rank, char **currenUser)
{
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t\tLAP PHIEU MUON SACH \n");
	printf("\n");

	int soLuongSach;
	PhieuMuonSach muonSach;
	FILE *f = fopen(borrowlist, "a+");
	if (f == NULL)
	{
		printf("Loi mo file \n");
	}
	else
	{
		fprintf(f, "\n");
		printf("\t\t\tNhap ma doc gia: ");
		rewind(stdin);
		gets_s(muonSach.maDocGia);
		if (!check_Reader(muonSach.maDocGia))
		{
			printf("\t\t\tDoc gia chua ton tai. Xin them phieu doc gia! \n");
			fclose(f);
			goto Select;
		}

		fprintf(f, muonSach.maDocGia);
		fprintf(f, " ");

		printf("\t\t\tNhap ngay muon (dd/mm/yyyy): ");
		rewind(stdin);
		gets_s(muonSach.ngayMuon);
		fprintf(f, muonSach.ngayMuon);
		fprintf(f, " ");

		printf("\t\t\tNhap ngay tra du kien (dd/mm/yyyy): ");
		rewind(stdin);
		gets_s(muonSach.ngayTraDuKien);
		fprintf(f, muonSach.ngayTraDuKien);
		fprintf(f, " ");

		printf("\t\t\tNhap so luong sach muon: ");
		scanf_s("%i", &soLuongSach);
		char n[3];
		sprintf(n, "%i", soLuongSach);	// Chuyen tu int sang char	va luu vao bien n
		fprintf(f, n);		//Ghi so luong sach muon vao file
		fprintf(f, " ");

		for (int i = 0; i < soLuongSach; i++)
		{
			printf("\t\t\t   -Nhap ma ISBN sach thu %i: ", i + 1);
			rewind(stdin);
			gets_s(muonSach.ISBN);
			recountNumberOfBook(muonSach.ISBN, 0);
			fprintf(f, muonSach.ISBN);
			if (i < soLuongSach - 1)
			{
				fprintf(f, " ");
			}
		}
		fclose(f);
	}

Select:
	printf("\n\n\t\t\tNHAN ENTER DE TIEP TUC / NHAN ESC DE QUAY LAI MAN HINH CHINH: ");
	char c = _getch();
	if (c == 13)
	{
		system("cls");
		lapPhieuMuonSach(rank, currenUser);
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


void lapPhieuTraSach(int rank, char **currenUser)
{
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t\tLAP PHIEU TRA SACH \n");
	printf("\n");
	int check;
	int pos_begin, pos_end;
	FILE *bf = fopen(borrowlist, "r");
	PhieuTraSach trasach;
	PhieuMuonSach muonsach;
	char buffer[15];
	printf("\t\t\tNhap ma doc gia: ");
	rewind(stdin);
	gets_s(trasach.maDocGia);

	while (!feof(bf))
	{
		check = 0;
		fscanf(bf, "%s", buffer);
		if (strcmp(buffer, trasach.maDocGia) == 0)
		{
			pos_begin = ftell(bf)-5;	//Lay vi tri bat dau
			
			check = 1;
			FILE *rf =fopen(returnlist, "a+");
			fprintf(rf, "\n");
			int n;
			// Doc thong tin tu file borrowlist va ghi vao file returnlist
			printf("\n\t\t\tTHONG TIN MUON SACH: \n");
			printf("\t\t\tMa doc gia: %s \n", trasach.maDocGia);
			fprintf(rf, trasach.maDocGia);
			fprintf(rf, " ");
			
			fscanf(bf, "%s", trasach.ngayMuon);
			printf("\t\t\tNgay muon sach: %s \n", trasach.ngayMuon);
			fprintf(rf, trasach.ngayMuon);
			fprintf(rf, " ");

			fscanf(bf, "%s", trasach.ngayTraDuKien);
			printf("\t\t\tNgay tra du kien: %s \n",trasach.ngayTraDuKien);
			fprintf(rf, trasach.ngayTraDuKien);
			fprintf(rf, " ");

			fscanf(bf, "%i", &n);
			char buf[3];
			_itoa(n, buf, 10);
			fprintf(rf, buf);
			fprintf(rf, " ");

			printf("\t\t\tDanh sach ma ISBN sach da muon: \n");
			for (int i = 0; i < n; i++)
			{
				fscanf(bf, "%s", trasach.ISBN);
				recountNumberOfBook(trasach.ISBN,1);
				printf("\t\t\t  %i) %s \n",i+1,trasach.ISBN);
				fprintf(rf, trasach.ISBN);
				fprintf(rf, " ");
			}
			pos_end = ftell(bf);	//Lay vi tri ket thuc

			printf("\t\t\tNhap ngay tra thuc te (dd/mm/yyyy): ");
			rewind(stdin);
			gets_s(trasach.ngayTraThucTe);
			fprintf(rf, trasach.ngayTraThucTe);
			
			
			break;
			fclose(rf);
			printf("\n\n\t\t\t\t\t\tTRA SACH THANH CONG \n");
		}
	}
	// Cap nhat lai file muon sach
	if (check == 1)
	{
		rewind(bf);
		FILE *f = fopen(tmpborrowlist, "w+");
		char ch = fgetc(bf);
		while (ch != EOF)
		{
			if (ftell(bf) < pos_begin || ftell(bf) > pos_end)
			{
				fputc(ch, f);
			}
			ch = getc(bf);
		}
		fclose(f);
		fclose(bf);
		
		remove(borrowlist);
		rename(tmpborrowlist, borrowlist);

	}

	// Khong tim thay ma doc gia trong file
	if (check == 0)
		printf("\t\t\tDoc gia nay chua muon sach ! \n");

Select:
	printf("\n\n\t\t\tNHAN ENTER DE TIEP TUC / NHAN ESC DE QUAY LAI MAN HINH CHINH: ");
	char c = _getch();
	if (c == 13)
	{
		system("cls");
		lapPhieuTraSach(rank, currenUser);
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


