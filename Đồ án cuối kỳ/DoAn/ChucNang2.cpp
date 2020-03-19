#include"stdafx.h"
#include"Function2.h"
#include "UI.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#define ListDocGia  "C:\\LibManagement\\readerList.bin"
#define numbersOfReader "C:\\LibManagement\\countReader.bin"

void readerFunctionMenu(int rank, char **currenUser)
{
	DocGia *docgia;
	int n;
	system("cls");

	printf("\n\t\t     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	printf("\n\t\t     º                           QUAN LY DOC GIA                            º");
	printf("\n\t\t     ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹");
	printf("\n\t\t     º                                  ³                                   º");
	printf("\n\t\t     º1. XEM DANH SACH DOC GIA          ³2. THEM DOC GIA                    º");
	printf("\n\t\t     º                                  ³                                   º");
	printf("\n\t\t     º3. CHINH SUA THONG TIN DOC GIA    ³4. TIM KIEM DOC GIA THEO CMND      º");
	printf("\n\t\t     º                                  ³                                   º");
	printf("\n\t\t     º5 .TIM KIEM DOC GIA THEO TEN      ³                                   º");
	printf("\n\t\t     º                                  ³                                   º");
	if (rank != 2)
	{
		printf("\n\t\t     º6. XOA THONG TIN MOT DOC GIA      ³                                   º");
	}
	printf("\n\t\t     º                                  ³                                   º");
	printf("\n\t\t     ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹\n");
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
		inToanBo_DocGia();
		break;
	case 2:
		themDocGia(docgia, n);
		break;
	case 3:
		sua_ThongTin_DocGia();
		break;
	case 4:
		print_DocGia_CMND();
		break;
	case 5:
		print_DocGia_HoTen();
		break;
	case 6:
		if (rank == 2)
		{
			printf("Khon co chuc nang nay! \n");
			break;
		}
		else
		{
			xoaDocGia();
			break;
		}
	default:
		printf("Khong co chuc nang nay! \n");
		break;
	}

	Select:
	printf("\n\t\t NHAN ENTER DE TIEP TUC / NHAN ESC DE QUAY LAI MAN HINH CHINH: ");
	char c = _getch();
	if (c == 13)
	{
		system("cls");
		readerFunctionMenu(rank, currenUser);
	}
	else if (c == 27)
	{
		system("cls");
		menu(rank, currenUser);
		
	}
	else
	{
		goto Select;
	}
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int check_LeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 366;
	else
		return 365;
}
int return_day(int month, int year)
{
	if (month <= 12 && month >= 1)
	{
		switch (month)
		{
		case 4:case 6:case 9: case 11:
			return 30;
			break;
		case 2:
			if (check_LeapYear(year) == 366)
				return 29;
			else
				return 28;
			break;
		default:
			return 31;
			break;
		}
	}
	else
	{
		return 0;
	}
}
bool check_day_month_year(int day, int month, int year)
{
	if (year > 0)
	{
		if (return_day(month, year) != 0)
		{
			if (day > 0)
			{
				if (day <= return_day(month, year))
					return true;
			}

		}
	}
	return false;
}
void countReader(int n)
{
	int tongDocGia = n;
	FILE* f_count = fopen(numbersOfReader, "wb");
	fwrite(&tongDocGia, sizeof(int), 1, f_count);
	fclose(f_count);
}

void themDocGia_first(DocGia*&reader, int &n)
{
	int i = 0;
	int k = 1;
	n = 1;
	reader = (DocGia*)malloc(sizeof(DocGia));
	printf("\t\t\t\t\t\tTHEM MOT DOC GIA MOI VAO THU VIEN\n\n");
	while (k != 0)
	{
		reader = (DocGia*)realloc(reader, sizeof(DocGia)*n);
		printf("\t\t\tDoc gia thu %i:\n", i + 1);
		rewind(stdin);
	nhaplaimadocgia: printf("\t\t\tMoi nhap vao ma doc gia(5 ky tu):");
		gets_s(reader[i].MaDocGia);
		if (Tim_MS_DocGia(reader, n - 1, reader[i].MaDocGia) != -1)
		{
			printf("\t\t\tMa doc gia da co vui long nhap lai!\n");
			goto nhaplaimadocgia;
		}
		printf("\t\t\tHo ten:");
		gets_s(reader[i].HoTen);
		printf("\t\t\tSo CMND:");
		gets_s(reader[i].CMND);
		int c = 1;
		while (c != 0)
		{
			printf("\t\t\tNhap vao ngay thang nam sinh(dd/mm/yyyy):\n");
			{
				printf("\t\t\t\tNgay:");
				scanf_s("%d", &reader[i].daB.ngay);
				printf("\t\t\t\tThang:");
				scanf_s("%d", &reader[i].daB.thang);
				printf("\t\t\t\tNam:");
				scanf_s("%d", &reader[i].daB.nam);
			}
			if (check_day_month_year(reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam) == false)
			{
				printf("\t\t\tNgay thang nam khong ton tai!\nVui long nhap lai!\n\n");
			}
			else
				c = 0;
		}
		rewind(stdin);
		printf("\t\t\tMoi nhap vao gioi tinh(Nam/Nu):");
		gets_s(reader[i].GioiTinh);
		printf("\t\t\tMoi nhap vao Email:");
		gets_s(reader[i].Email);
		printf("\t\t\tMoi nhap vao dia chi:");
		gets_s(reader[i].DiaChi);
		c = 1;
		while (c != 0)
		{
			printf("\t\t\tMoi nhap vao ngay lap the(dd//mm/yyyy):\n");
			{
				printf("\t\t\t\tNgay:");
				scanf_s("%d", &reader[i].ngaylapthe.ngay);
				printf("\t\t\t\tThang:");
				scanf_s("%d", &reader[i].ngaylapthe.thang);
				printf("\t\t\t\tNam:");
				scanf_s("%d", &reader[i].ngaylapthe.nam);
			}
			if (check_day_month_year(reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam) == false)
			{
				printf("\t\t\tNgay thang nam khong ton tai!\nVui long nhap lai!\n\n");
			}
			else
			{
				c = 0;
				if (reader[i].ngaylapthe.thang != 2)
				{
					reader[i].ngayhethan.ngay = reader[i].ngaylapthe.ngay;
					reader[i].ngayhethan.thang = reader[i].ngaylapthe.thang;
					reader[i].ngayhethan.nam = reader[i].ngaylapthe.nam + 2;
				}
				else
				{
					if (return_day(reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam) == 29)
					{
						reader[i].ngayhethan.ngay = 1;
						reader[i].ngayhethan.thang = 3;
						reader[i].ngayhethan.nam = reader[i].ngaylapthe.nam + 2;
					}
				}
			}
		}

	kiemtra: printf("\n\t\t\tNhap tiep doc gia nhan 1, nhap xong nhan 0:");
		scanf_s("%i", &k);
		if (k != 1 && k != 0)
		{
			printf("\t\t\tChi duoc nhap '1' hoac '0', vui long nhap lai!\n");
			goto kiemtra;
		}
		if (k == 1)
		{
			n++;
			i++;
		}
	}
	countReader(n);
	ghiDuLieu(reader, n);
}
//Hàm thêm n độc giả theo yêu cầu của Admin
void themDocGia(DocGia*&reader, int &n)
{
	int tongDocGia = 0;
	FILE* f_count = fopen(numbersOfReader, "rb");
	FILE*f = fopen(ListDocGia, "rb");
	if (f == NULL || f_count == NULL)
	{
		themDocGia_first(reader, n);
		exit('0');
	}
	else
	{
		fread(&tongDocGia, sizeof(int), 1, f_count);
	}
	fclose(f_count);
	n = tongDocGia;
	reader = (DocGia*)malloc(sizeof(DocGia)*n);
	if (f == NULL)
	{
		printf("\t\t\tDa xay ra loi!\n");
		exit('0');
	}
	else
	{
		int i = 0;
		while (i<n)
		{
			fread(&reader[i], sizeof(DocGia), 1, f);
			i++;
		}
	}
	fclose(f);
	printf("\t\t\t\t\t\tTHEM MOT DOC GIA MOI VAO THU VIEN\n\n");
	int k = 1;
	int i = n;
	n++;
	while (k != 0)
	{
		reader = (DocGia*)realloc(reader, sizeof(DocGia)*n);
		printf("\t\t\tDoc gia thu %i:\n", i + 1);
		rewind(stdin);
	nhaplaimadocgia: printf("\t\t\tMoi nhap vao ma doc gia(Toi da 5 ky tu):");
		gets_s(reader[i].MaDocGia);
		if (Tim_MS_DocGia(reader, n - 1, reader[i].MaDocGia) != -1)
		{
			printf("\t\t\tMa doc gia da co vui long nhap lai!\n");
			goto nhaplaimadocgia;
		}
		printf("\t\t\tHo ten:");
		gets_s(reader[i].HoTen);
		printf("\t\t\tSo CMND:");
		gets_s(reader[i].CMND);
		int c = 1;
		while (c != 0)
		{
			printf("\t\t\tNhap vao ngay thang nam sinh(dd/mm/yyyy):\n");
			{
				printf("\t\t\t\tNgay:");
				scanf_s("%d", &reader[i].daB.ngay);
				printf("\t\t\t\tThang:");
				scanf_s("%d", &reader[i].daB.thang);
				printf("\t\t\t\tNam:");
				scanf_s("%d", &reader[i].daB.nam);
			}
			if (check_day_month_year(reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam) == false)
			{
				printf("\t\t\tNgay thang nam khong ton tai!\nVui long nhap lai!\n\n");
			}
			else
				c = 0;
		}
		rewind(stdin);
		printf("\t\t\tMoi nhap vao gioi tinh(Nam/Nu):");
		gets_s(reader[i].GioiTinh);
		printf("\t\t\tMoi nhap vao Email:");
		gets_s(reader[i].Email);
		printf("\t\t\tMoi nhap vao dia chi:");
		gets_s(reader[i].DiaChi);
		c = 1;
		while (c != 0)
		{
			printf("\t\t\tMoi nhap vao ngay lap the(dd/mm/yyyy):\n");
			{
				printf("\t\t\t\tNgay:");
				scanf_s("%d", &reader[i].ngaylapthe.ngay);
				printf("\t\t\t\tThang:");
				scanf_s("%d", &reader[i].ngaylapthe.thang);
				printf("\t\t\t\tNam:");
				scanf_s("%d", &reader[i].ngaylapthe.nam);
			}
			if (check_day_month_year(reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam) == false)
			{
				printf("\t\t\tNgay thang nam khong ton tai!\nVui long nhap lai!\n\n");
			}
			else
			{
				c = 0;
				if (reader[i].ngaylapthe.thang != 2)
				{
					reader[i].ngayhethan.ngay = reader[i].ngaylapthe.ngay;
					reader[i].ngayhethan.thang = reader[i].ngaylapthe.thang;
					reader[i].ngayhethan.nam = reader[i].ngaylapthe.nam + 2;
				}
				else
				{
					if (return_day(reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam) == 29)
					{
						reader[i].ngayhethan.ngay = 1;
						reader[i].ngayhethan.thang = 3;
						reader[i].ngayhethan.nam = reader[i].ngaylapthe.nam + 2;
					}
				}
			}
		}
	kiemtra: printf("\n\t\t\tNhap tiep doc gia nhan 1, nhap xong nhan 0:");
		scanf_s("%i", &k);
		if (k != 1 && k != 0)
		{
			printf("\t\t\tChi duoc nhap '1' hoac '0', vui long nhap lai!\n");
			goto kiemtra;
		}
		if (k == 1)
		{
			n++;
			i++;
		}
	}
	countReader(n);
	ghiDuLieu(reader, n);
}
//Hàm lưu thông tin độc giả vào file
void ghiDuLieu(DocGia*& reader, int n)
{
	FILE* f = fopen(ListDocGia, "wb");
	if (f == NULL)
		printf("\t\t\tDanh sach chua duoc tao!\n");
	else
	{
		int i = 0;
		while (i<n)
		{
			fwrite(&reader[i], sizeof(DocGia), 1, f);
			i++;
		}
	}
	fclose(f);
}
//Hàm lấy dữ liệu độc giả từ FILE
void docDuLieu(DocGia *&reader, int &n)
{
	DocGia g;
	int tongDocGia = 0;
	FILE* f_count = fopen(numbersOfReader, "ab+");
	if (f_count == NULL)
	{
		printf("\t\t\tThu vien khong co doc gia,vui long them doc gia!\n");
		exit(0);
	}
	else
	{
		fread(&tongDocGia, sizeof(int), 1, f_count);
	}
	fclose(f_count);
	n = tongDocGia;
	FILE* f = fopen(ListDocGia, "ab+");
	if (f == NULL)
	{
		printf("\t\t\tDa xay ra loi!\n");
		exit(0);
	}
	else
	{
		reader = (DocGia*)malloc(sizeof(DocGia)*n);
		for (int i = 0; i < n; i++)
		{
			fread(&g, sizeof(DocGia), 1, f);
			reader[i] = g;
		}
	}
	fclose(f);
}
//Hàm xem chi tiết tất cả độc giả có trong Thư Viện
void inToanBo_DocGia()
{
	DocGia *reader;
	int n;
	docDuLieu(reader, n);
	printf("\n\t\t\t\t\t\t\t\tDANH SACH CAC DOC GIA CO TRONG THU VIEN LA");
	printf("\nÉÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍ»");
	printf("\nºMa DG³             Ho Ten           ³    CMND    ³   Dab    ³ SEX ³           Email                   ³            Dia Chi                        ³  Lap the ³  Het han º");
	printf("\nÌÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍ¹");
	for (int i = 0; i < n; i++)
	{
		printf("\nº%-5s", reader[i].MaDocGia);
		printf("³%-30s", reader[i].HoTen);
		printf("³%-12s", reader[i].CMND);
		printf("³%2d/%2d/%4d", reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam);
		printf("³%-5s", reader[i].GioiTinh);
		printf("³%-35s", reader[i].Email);
		printf("³%-43s", reader[i].DiaChi);
		printf("³%2d/%2d/%4d", reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam);
		printf("³%2d/%2d/%4dº", reader[i].ngayhethan.ngay, reader[i].ngayhethan.thang, reader[i].ngayhethan.nam);
	}
	printf("\nÈÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍ¼");
	printf("\n\n");
}
void sua_ThongTin_DocGia()
{
	printf("\n\n");
	printf("\t\t\t\t\t\tSUA THONG TIN DOC GIA \n");
	DocGia *reader;
	int n, vitri;
	docDuLieu(reader, n);
	char check[20];
	rewind(stdin);
	printf("\t\t\tNhap vao ma so doc gia can sua thong tin:");
	gets_s(check);
	vitri = Tim_MS_DocGia(reader, n, check);
	if (vitri == -1)
	{
		printf("\t\t\tKhong tim thay ma so doc gia trong thu vien!\n");
	}
	else
	{

		printf("\t\t\tTIM THAY DOC GIA!\n");
		print_1_DocGia(reader, n, vitri);
		printf("\n");
		int choice;
		printf("\n\t\t\t\t\t1.Sua Ho ten.");
		printf("\n\t\t\t\t\t2.Sua CMND.");
		printf("\n\t\t\t\t\t3.Sua ngay thang nam sinh.");
		printf("\n\t\t\t\t\t4.Sua gioi tinh.");
		printf("\n\t\t\t\t\t5.Sua email.");
		printf("\n\t\t\t\t\t6.Sua dia chi.");
		printf("\n\t\t\t\t\t7.Sua ngay lap the.");
		printf("\n\t\t\tMoi nhap vao thong tin ma ban muon sua:");
		scanf_s("%i", &choice);
		rewind(stdin);
		int k = 1;
		while (k != 0)
		{
			switch (choice)
			{
			case 1:
				printf("\t\t\tHo ten:");
				gets_s(reader[vitri].HoTen);
				k = 0;
				break;
			case 2:
				printf("\t\t\tSo CMND:");
				gets_s(reader[vitri].CMND);
				k = 0;
				break;
			case 3:
				printf("\t\t\tNhap vao ngay thang nam sinh:\n");
				{
					printf("\t\t\t\tNgay:");
					scanf_s("%i", &reader[vitri].daB.ngay);
					printf("\t\t\t\tThang:");
					scanf_s("%i", &reader[vitri].daB.thang);
					printf("\t\t\t\tNam:");
					scanf_s("%i", &reader[vitri].daB.nam);
				}
				k = 0;
				break;
			case 4:
				rewind(stdin);
				printf("\t\t\tMoi nhap vao gioi tinh:");
				gets_s(reader[vitri].GioiTinh);
				k = 0;
				break;
			case 5:
				printf("\t\t\tMoi nhap vao Email:");
				gets_s(reader[vitri].Email);
				break;
			case 6:
				printf("\t\t\tMoi nhap vao dia chi:");
				gets_s(reader[vitri].DiaChi);
				k = 0;
				break;
			case 7:
				printf("\t\t\tMoi nhap vao ngay lap the:\n");
				{
					printf("\t\t\t\tNgay:");
					scanf_s("%i", &reader[vitri].ngaylapthe.ngay);
					printf("\t\t\t\tThang:");
					scanf_s("%i", &reader[vitri].ngaylapthe.thang);
					printf("\t\t\t\tNam:");
					scanf_s("%i", &reader[vitri].ngaylapthe.nam);
				}
				k = 0;
				break;
			default:
				printf("\t\t\tBan da nhap sai!Vui long nhap lai!\n");
				break;
			}
		}
		printf("\n\t\t\tSUA THONG TIN DOC GIA THANH CONG!\n");
		ghiDuLieu(reader, n);
	}
}

//Hàm tìm một độc giả theo Mã độc giả
int Tim_MS_DocGia(DocGia *reader, int n, char c[20])
{
	int i = 0;
	while (i<n && strcmp(reader[i].MaDocGia, c) != 0)
	{
		i++;
	}
	if (i >= n)
		return -1;//Tìm không thấy mã độc giả đó trong thư viện
	else
		return i;//Tìm thấy và trả về vị trí vừa tìm được
}
//Hàm tìm độc giả theo số CMND
int Tim_CMND_DocGia(DocGia *reader, int n, char check[20])
{
	int i = 0;
	while ((i < n) && (strcmp(reader[i].CMND, check) != 0))
	{
		i++;
	}
	if (i >= n)
		return -1;//Tìm không thấy CMND đó trong thư viện
	else
		return i;//Tìm thấy và trả về vị trí vừa tìm được
}
//Hàm tìm thông tin độc giả theo họ tên
int Tim_HoTen_DocGia(DocGia *reader, int n, char check[50])
{
	int i = 0;
	while ((i < n) && (strcmp(_strupr(reader[i].HoTen), _strupr(check)) != 0))
		i++;
	if (i >= n)
		return -1;
	else
		return i;
}
//Hàm in thông tin 1 độc giả tại vị trí: vitri
void print_1_DocGia(DocGia *reader, int n, int vitri)
{
	printf("\n\t\t\t\t\t\t\t\tDANH SACH CAC DOC GIA CO TRONG THU VIEN LA");
	printf("\nÉÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍ»");
	printf("\nºMa DG³             Ho Ten              ³    CMND    ³   Dab    ³ SEX ³           Email                   ³            Dia Chi                     ³  Lap the ³  Het han º");
	printf("\nÌÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍ¹");
	{
		printf("\nº%-5s", reader[vitri].MaDocGia);
		printf("³%-33s", reader[vitri].HoTen);
		printf("³%-12s", reader[vitri].CMND);
		printf("³%2d/%2d/%4d", reader[vitri].daB.ngay, reader[vitri].daB.thang, reader[vitri].daB.nam);
		printf("³%-5s", reader[vitri].GioiTinh);
		printf("³%-35s", reader[vitri].Email);
		printf("³%-40s", reader[vitri].DiaChi);
		printf("³%2d/%2d/%4d", reader[vitri].ngaylapthe.ngay, reader[vitri].ngaylapthe.thang, reader[vitri].ngaylapthe.nam);
		printf("³%2d/%2d/%4dº", reader[vitri].ngayhethan.ngay, reader[vitri].ngayhethan.thang, reader[vitri].ngayhethan.nam);
	}
	printf("\nÈÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	printf("\n");
}
//In độc giả tìm thấy theo HoTen
void print_DocGia_HoTen()
{
	DocGia*reader;
	int n;
	docDuLieu(reader, n);
	char check[50];
	rewind(stdin);
	printf("\t\t\tNhap vao ten doc gia ma ban muon tim:");
	gets_s(check);
	int vitri;
	vitri = Tim_HoTen_DocGia(reader, n, check);
	if (vitri == -1)
		printf("\t\t\tKhong tim thay doc gia nay trong thu vien!\n");
	else
	{
		printf("\n\t\t\tTIM THAY DOC GIA!\n");
		print_1_DocGia(reader, n, vitri);
	}
}
//In độc giả theo số CMND
void print_DocGia_CMND()
{
	DocGia* reader;
	int n;
	docDuLieu(reader, n);
	char check[20];
	rewind(stdin);
	printf("\t\t\tNhap vao so CMND ma ban muon tim:");
	gets_s(check);
	int vitri;
	vitri = Tim_CMND_DocGia(reader, n, check);
	if (vitri == -1)
		printf("\t\t\tKhong tim thay doc gia nay trong thu vien!\n");
	else
	{
		printf("Tim thay doc gia!\nThong tin doc gia do la:\n");
		print_1_DocGia(reader, n, vitri);
	}
}
//Hàm xóa thông tin một độc giả
void xoaDocGia()
{
	DocGia* reader;
	int n;
	docDuLieu(reader, n);
	char ms[20];
	int vitri;
	printf("\n\t\t\t\t\t\tXOA THONG TIN DOC GIA\n");
	rewind(stdin);
	printf("\t\t\tNhap vao ma so cua doc gia:");
	gets_s(ms);
	vitri = Tim_MS_DocGia(reader, n, ms);
	if (vitri == -1)
		printf("\t\t\tKhong co vi tri nay trong danh sach!\n");
	else
	{
		printf("\t\t\tTim thay doc gia trong thu vien!\nThong tin doc gia ma ban muon xoa la:\n");
		print_1_DocGia(reader, n, vitri);
		printf("\t\t\tBan co chac muon xoa doc gia nay khong( Chac:1 , khong:0): ");
		if (getchar() == '1')
		{
			{
				for (int i = vitri; i < n - 1; i++)
				{
					reader[i] = reader[i + 1];
				}
				n--;
			}
			printf("\t\t\tXoa thanh cong!\n");
			reader = (DocGia*)realloc(reader, sizeof(DocGia)*n);
			countReader(n);
			ghiDuLieu(reader, n);
		}
		else
		{
			printf("\t\t\tBan da khong xoa doc gia nao!\n");
		}
	}
}

bool check_Reader(char *maDocGia)
{
	FILE *f = fopen(ListDocGia, "rb");
	DocGia reader;
	while (!feof(f))
	{
		fread(&reader, sizeof(DocGia), 1, f);
		if (strcmp(reader.MaDocGia, maDocGia) == 0)
		{
			return true;
		}
	}
	return false;
}

void tenDocGiaTheoMaDG(char *maDocGia, char ten[])
{
	DocGia docgia;
	FILE *f = fopen(ListDocGia, "rb");
	while (!feof(f))
	{
		fread(&docgia, sizeof(DocGia), 1, f);
		if (strcmp(docgia.MaDocGia, maDocGia) == 0)
		{
			strcpy(ten, docgia.HoTen);
			break;
		}
	}
}