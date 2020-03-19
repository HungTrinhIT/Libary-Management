#include"stdafx.h"
#include"Function2.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define ListDocGia  "D:\\DoAn\\readerList.bin"
#define numbersOfReader "D:\\DoAn\\countReader.bin"
bool day_month_year_reader(int day, int  month, int year)
{
	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		{
			if (day < 1 || day >31)
			{
				printf("ngay khong ton tai\n");
				return false;
			}
		}
		case 2:
		{
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				if (day < 1 || day>29)
				{
					printf("ngay khong ton tai\n");
					return false;
				}
			}
			else
			{
				if (day < 1 || day >28)
				{
					printf("ngay khong ton tai\n");
					return false;
				}
			}
		}
		case 4: case 6: case 9: case 11:
		{
			if (day < 1 || day>30)
			{
				printf("ngay ko ton tai\n");
				return false;
			}
		}
	}
	return true;
}
void countReader(int n)
{
	int tongDocGia = n;
	FILE* f_count = fopen(numbersOfReader, "wb");
	fwrite(&tongDocGia, sizeof(int), 1, f_count);
	fclose(f_count);
}
//int check_NamNhuan(int nam)
//{
//	if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0))
//		return 366;
//	else
//		return 365;
//}
//int check_Thang(int thang,int nam)
//{
//	switch (thang)
//	{
//	case 4:case 6:case 9: case 11:
//		return 30;
//	case 2:
//		if (check_NamNhuan(nam) == 366)
//			return 29;
//		else
//			return 28;
//	default:
//		return 31;
//	}
//}
void themDocGia_first(DocGia*&reader, int &n)
{
	int i = 0;
	int k = 1;
	n = 1;
	reader = (DocGia*)malloc(sizeof(DocGia));
	printf("                    THEM MOT DOC GIA MOI VAO THU VIEN      \n\n");
	while (k != 0)
	{
		reader = (DocGia*)realloc(reader, sizeof(DocGia)*n);
		printf("Doc gia thu %i:\n", i + 1);
		rewind(stdin);
	nhaplaimadocgia: printf("Moi nhap vao ma doc gia:");
		gets_s(reader[i].MaDocGia);
		if (Tim_MS_DocGia(reader, n - 1, reader[i].MaDocGia) != -1)
		{
			printf("Ma doc gia da co vui long nhap lai!\n");
			goto nhaplaimadocgia;
		}
		printf("Ho ten:");
		gets_s(reader[i].HoTen);
		printf("So CMND:");
		gets_s(reader[i].CMND);
	dab:	printf("Nhap vao ngay thang nam sinh:\n");
		{
			printf("\tNgay:");
			scanf_s("%i", &reader[i].daB.ngay);
			printf("\tThang:");
			scanf_s("%i", &reader[i].daB.thang);
			printf("\tNam:");
			scanf_s("%i", &reader[i].daB.nam);
		}
		if (day_month_year_reader(reader[i].daB.ngay,reader[i].daB.thang,reader[i].daB.nam==false))
		{
			printf("Ngay thang nam cua ban khong hop le vui long nhap lai!\n");				goto dab;
		}
		rewind(stdin);
		printf("Moi nhap vao gioi tinh:");
		gets_s(reader[i].GioiTinh);
		printf("Moi nhap vao Email:");
		gets_s(reader[i].Email);
		printf("Moi nhap vao dia chi:");
		gets_s(reader[i].DiaChi);
	lapthe:	printf("Moi nhap vao ngay lap the:\n");
		{
			printf("\tNgay:");
			scanf_s("%i", &reader[i].ngaylapthe.ngay);
			printf("\tThang:");
			scanf_s("%i", &reader[i].ngaylapthe.thang);
			printf("\tNam:");
			scanf_s("%i", &reader[i].ngaylapthe.nam);
		}
		if (day_month_year_reader(reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam == false))
		{
			printf("Ngay thang nam cua ban khong hop le vui long nhap lai!\n");
			goto lapthe;
		}
	kiemtra: printf("\nNhap tiep doc gia nhan 1, nhap xong nhan 0:");
		scanf_s("%i", &k);
		if (k != 1 && k != 0)
		{
			printf("Chi duoc nhap '1' hoac '0', vui long nhap lai!\n");
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
void themDocGia(DocGia*&reader , int &n)
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
		printf("Da xay ra loi!\n");
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
	printf("                    THEM MOT DOC GIA MOI VAO THU VIEN      \n\n");
	int k = 1;
	int i = n;
	n++;
	while (k!=0)
	{
		reader = (DocGia*)realloc(reader, sizeof(DocGia)*n);
		printf("Doc gia thu %i:\n", i + 1);
		rewind(stdin);
	nhaplaimadocgia: printf("Moi nhap vao ma doc gia:");
		gets_s(reader[i].MaDocGia);
		if (Tim_MS_DocGia(reader, n - 1, reader[i].MaDocGia) != -1)
		{
			printf("Ma doc gia da co vui long nhap lai!\n");
			goto nhaplaimadocgia;
		}
		printf("Ho ten:");
		gets_s(reader[i].HoTen);
		printf("So CMND:");
		gets_s(reader[i].CMND);
	dab:	printf("Nhap vao ngay thang nam sinh:\n");
		{
			printf("\tNgay:");
			scanf_s("%i", &reader[i].daB.ngay);
			printf("\tThang:");
			scanf_s("%i", &reader[i].daB.thang);
			printf("\tNam:");
			scanf_s("%i", &reader[i].daB.nam);
		}
		if (day_month_year_reader(reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam == false))
		{
			printf("Ngay thang nam cua ban khong hop le vui long nhap lai!\n");				
			goto dab;
		}
		rewind(stdin);
		printf("Moi nhap vao gioi tinh:");
		gets_s(reader[i].GioiTinh);
		printf("Moi nhap vao Email:");
		gets_s(reader[i].Email);
		printf("Moi nhap vao dia chi:");
		gets_s(reader[i].DiaChi);
	lapthe:	printf("Moi nhap vao ngay lap the:\n");
		{
			printf("\tNgay:");
			scanf_s("%i", &reader[i].ngaylapthe.ngay);
			printf("\tThang:");
			scanf_s("%i", &reader[i].ngaylapthe.thang);
			printf("\tNam:");
			scanf_s("%i", &reader[i].ngaylapthe.nam);
		}
		if (day_month_year_reader(reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam == false))
		{
			printf("Ngay thang nam cua ban khong hop le vui long nhap lai!\n");
			goto lapthe;
		}
	kiemtra: printf("\nNhap tiep doc gia nhan 1, nhap xong nhan 0:");
		scanf_s("%i", &k);
		if (k != 1 && k != 0)
		{
			printf("Chi duoc nhap '1' hoac '0', vui long nhap lai!\n");
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
		printf("Danh sach chua duoc tao!\n");
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
	FILE* f_count = fopen(numbersOfReader, "rb");
	if (f_count == NULL)
	{
		printf("Thu vien khong co doc gia,vui long them doc gia!\n");
		exit('0');
	}
	else
	{
		fread(&tongDocGia, sizeof(int), 1, f_count);
	}
	fclose(f_count);
	n = tongDocGia;
	FILE* f = fopen(ListDocGia, "rb");
	if (f == NULL)
	{
		printf("Da xay ra loi!\n");
		exit('0');
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
	printf("\n\n\t DANH SACH DOC GIA CO TRONG THU VIEN \n");
	for (int i = 0; i < n; i++)
	{
		printf("Thong tin doc gia thu %i:\n", i + 1);
		printf("\tMa doc gia:");
		puts(reader[i].MaDocGia);
		printf("\n\tHo va ten doc gia:");
		puts(reader[i].HoTen);
		printf("\n\tSo CMND:");
		puts(reader[i].CMND);
		printf("\n\tNgay thang nam sinh:%i/%i/%i", reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam);
		printf("\n\tGioi tinh:");
		puts(reader[i].GioiTinh);
		printf("\n\tDia chi Email:");
		puts(reader[i].Email);
		printf("\n\tDia nha nha :");
		puts(reader[i].DiaChi);
		printf("\n\tNgay lap the:%i/%i/%i", reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam);
		printf("\n\n");
	}
}
void sua_ThongTin_DocGia()
{
	DocGia *reader;
	int n, vitri;
	docDuLieu(reader, n);
	char check[20];
	rewind(stdin);
	printf("Nhap vao ma so doc gia can sua thong tin:");
	gets_s(check);
	vitri = Tim_MS_DocGia(reader, n, check);
	if (vitri == -1)
	{
		printf("Khong tim thay ma so doc gia trong thu vien!\n");
	}
	else
	{
		printf("TIM THAY DOC GIA!\n");
		print_1_DocGia(reader,n,vitri);
		printf("\n");
		printf("Ho ten:");
		gets_s(reader[vitri].HoTen);
		printf("So CMND:");
		gets_s(reader[vitri].CMND);
		printf("Nhap vao ngay thang nam sinh:\n");
		{
			printf("\tNgay:");
			scanf_s("%i", &reader[vitri].daB.ngay);
			printf("\tThang:");
			scanf_s("%i", &reader[vitri].daB.thang);
			printf("\tNam:");
			scanf_s("%i", &reader[vitri].daB.nam);
		}
		rewind(stdin);
		printf("Moi nhap vao gioi tinh:");
		gets_s(reader[vitri].GioiTinh);
		printf("Moi nhap vao Email:");
		gets_s(reader[vitri].Email);
		printf("Moi nhap vao dia chi:");
		gets_s(reader[vitri].DiaChi);
		printf("Moi nhap vao ngay lap the:\n");
		{
			printf("\tNgay:");
			scanf_s("%i", &reader[vitri].ngaylapthe.ngay);
			printf("\tThang:");
			scanf_s("%i", &reader[vitri].ngaylapthe.thang);
			printf("\tNam:");
			scanf_s("%i", &reader[vitri].ngaylapthe.nam);
		}
		printf("\nSUA THONG TIN DOC GIA THANH CONG!\n");
		ghiDuLieu(reader, n);
	}
}
	
//Hàm tìm một độc giả theo Mã độc giả
int Tim_MS_DocGia(DocGia *reader, int n,char c[20])
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
int Tim_CMND_DocGia(DocGia *reader, int n,char check[20])
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
	while ((i < n) && (strcmp(reader[i].HoTen, check) != 0))
		i++;
	if (i >= n)
		return -1;
	else
		return i;
}
//Hàm in thông tin 1 độc giả tại vị trí: vitri
void print_1_DocGia(DocGia *reader,int n, int vitri)
{
	printf("\tMa doc gia:");
	puts(reader[vitri].MaDocGia);
	printf("\n\tHo va ten doc gia:");
	puts(reader[vitri].HoTen);
	printf("\n\tSo CMND:");
	puts(reader[vitri].CMND);
	printf("\n\tNgay thang nam sinh:%i/%i/%i", reader[vitri].daB.ngay, reader[vitri].daB.thang, reader[vitri].daB.nam);
	printf("\n\tGioi tinh:");
	puts(reader[vitri].GioiTinh);
	printf("\n\tDia chi Email:");
	puts(reader[vitri].Email);
	printf("\n\tDia nha nha :");
	puts(reader[vitri].DiaChi);
	printf("\n\tNgay lap the:%i/%i/%i", reader[vitri].ngaylapthe.ngay, reader[vitri].ngaylapthe.thang, reader[vitri].ngaylapthe.nam);
	printf("\n\n");
}
//In độc giả tìm thấy theo HoTen
void print_DocGia_HoTen()
{
	DocGia*reader;
	int n;
	docDuLieu(reader, n);
	char check[50];
	rewind(stdin);
	printf("Nhap vao ten doc gia ma ban muon tim:");
	gets_s(check);
	int vitri;
	vitri = Tim_HoTen_DocGia(reader, n, check);
	if (vitri == -1)
		printf("Khong tim thay doc gia nay trong thu vien!\n");
	else
	{
		printf("\nTIM THAY DOC GIA!\n");
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
	printf("Nhap vao so CMND ma ban muon tim:");
	gets_s(check);
	int vitri;
	vitri =Tim_CMND_DocGia(reader, n, check);
	if (vitri == -1)
		printf("Khong tim thay doc gia nay trong thu vien!\n");
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
	printf("\n\t\XOA THONG TIN DOC GIA\n");
	rewind(stdin);
	printf("Nhap vao ma so cua doc gia:");
	gets_s(ms);
	vitri = Tim_MS_DocGia(reader, n, ms);
	if (vitri == -1)
		printf("Khong co vi tri nay trong danh sach!\n");
	else
	{
		printf("Tim thay doc gia trong thu vien!\nThong tin doc gia ma ban muon xoa la:\n");
		print_1_DocGia(reader, n, vitri);
		printf("Ban co chac muon xoa doc gia nay khong( Chac:1 , khong:0)\n");
		if (getchar() == '1')
		{
			{
				for (int i = vitri; i < n - 1; i++)
				{
					reader[i] = reader[i + 1];
				}
				n--;
			}
			printf("Xoa thanh cong!\n");
			reader = (DocGia*)realloc(reader, sizeof(DocGia)*n);
			countReader(n);
			ghiDuLieu(reader, n);
		}
		else
		{
			printf("Ban da khong xoa doc gia nao!\n");
		}
	}
}