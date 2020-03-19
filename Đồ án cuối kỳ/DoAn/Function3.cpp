``#include"stdafx.h"
#include"Function3.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#define listBook "D:\\DoAn\\bookList.bin"
#define numbersOfBook "D:\\DoAn\\countbook.bin"

void info()
{
	printf("\n			  ***************DO AN NHAP KY THUAT LAP TRINH****************  \n");
	printf("				         CHUONG TRINH QUAN LY THU VIEN  \n\n");
	printf("\t\t\tSINH VIEN 1:\n");
	printf("\t\t\t\tSinh Vien  : Trinh Vu Minh Hung  \n");
	printf("\t\t\t\tLop        : 17CTT1 \n");
	printf("\t\t\t\tMSSV       : 1712049\n");
	printf("\t\t\t\tDien Thoai : 012925112976\n");
	printf("\t\t\t\tEmail      : minhhung.it99@gmail.com\n");
	printf("\n\n");
	printf("\t\t\tSINH VIEN 2:\n");
	printf("\t\t\t\tSinh Vien  : Pham Hoang Phuoc Duy  \n");
	printf("\t\t\t\tLop        : 17CTT1 \n");
	printf("\t\t\t\tMSSV       : 1712018\n");
	printf("\t\t\t\tDien Thoai : 0949063841\n");
	printf("\t\t\t\tEmail      : phuocduypham2502@gmail.com\n");
}
int menu()
{
	int chon;
	system("cls");

	printf("\n			 CHUONG TRINH QUAN LY THU VIEN               ");
	printf("\n     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	printf("\n     º          QUAN LY SACH            ³      QUAN LY PHIEU MUON           º");
	printf("\n     ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹");
	printf("\n     º1 .Them Mot Dau Sach Moi          ³10.Them Phieu Moi                  º");
	printf("\n     º2 .In Thong Tin Sach	          ³11.Sua Thong Tin Phieu Muon        º");
	printf("\n     º3 .Sua Thong Tin Sach             ³12.Xoa Thong Tin Phieu Muon        º");
	printf("\n     º4 .Tim Kiem Thong Tin Sach ISBN   ³13.Tim Thong Tin Phieu Muon        º");
	printf("\n     º5 .Tim Kiem Sach Theo Ten Sach    ³14.Muon Sach                       º");
	printf("\n     º6 . Xoa 1 Quyen Sach              ³15.Tra Sach                        º");
	printf("\n     º7 .Thoat Khoi Chuong Trinh        ³16.In Dach Sach Phieu Muon         º");
	printf("\n     º8 .Cac Sach Duoc Muon Nhieu       ³17.Thong Ke Cac Phieu Muon Qua Han º");
	printf("\n     º9 .Thoat Khoi Chuong Trinh        ³18.Cac Doc Gia Muon Nhieu Sach     º");
	printf("\n     ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹");
	printf("\n     º           Nhan Phim 0 De Xem Thong Tin Tac Gia  Chuong Trinh         º");
	printf("\n     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼");
	printf("\n                   Vui Long Chon Cac Phim Chuc Nang Tuong Ung   \n");
	printf("Moi ban nhap vao chuc nang:");
	scanf_s("%i", &chon);
	system("cls");
	return chon;
}
void back()
{
	printf("\n\n\t\t\t==============================================================\n");
	printf("\t\t\t\t\tNHAN ENTER DE RA MAN HINH CHINH\n");
	_getch();
	system("cls");
}

int Tim_MS_Sach(Book *a, int n, char ms[20]) // Tìm sách theo ISBN
{
	int i = 0;
	while (i<n && strcmp(a[i].ISBN, ms) != 0)
	{
		i++;
	}
	if (i >= n)
		return -1;//Tìm không thấy mã sách đó trong thư viện
	else
		return i;//Tìm thấy và trả về vị trí vừa tìm được
}
int tim_Sach_TenSach(Book*a, int n, char check_Name[100])
{
	rewind(stdin);
	int i = 0;
	while (i<n && strcmp(a[i].tenSach, check_Name) != 0)
	{
		i++;
	}
	if (i >= n) // Tìm không thấy tên sách này trong thư viện
		return -1;// Không return 0 vì lỡ tìm thấy cuốn sách đầu tiền nó là vị trí 0 trong mảng nên sẽ bị trùng
	else
		return i; // trả về vị trí sách thứ i vừa tìm thấy
}
void countBook(int n)
{
	int tongSach = n;
	FILE* f_count = fopen(numbersOfBook, "wb");
	fwrite(&tongSach, sizeof(int), 1, f_count);
	fclose(f_count);
}
void themSach_first(Book*&a, int &n)
{
	int i = 0, k = 1;
	n = 1;
	a = (Book*)malloc(sizeof(Book));
	printf("					THEM MOT DAU SACH MOI VAO THU VIEN                  \n\n");
	while (k != 0)
	{
		a = (Book*)realloc(a, sizeof(Book)*n);
		printf("Quyen sach thu %i:\n", i + 1);
		rewind(stdin);
	nhaplaimasach:	printf("\tNhap vao ma sach:");
		gets_s(a[i].ISBN);
		if (Tim_MS_Sach(a, n - 1, a[i].ISBN) != -1)
		{
			printf("\tMa sach da co, vui long nhap lai!\n");
			goto nhaplaimasach;
		}
		printf("\tTen sach: ");
		gets_s(a[i].tenSach);
		printf("\tTac gia: ");
		gets_s(a[i].tacGia);
		printf("\tNha xuat ban: ");
		gets_s(a[i].nxb);
		printf("\tNam xuat ban: ");
		scanf_s("%i", &a[i].namXB);
		rewind(stdin);
		printf("\tThe loai sach: ");
		gets_s(a[i].theLoai);
		printf("\tVi tri sach trong thu vien: ");
		gets_s(a[i].viTri);
		do
		{
			printf("\tSo luong sach: ");
			scanf_s("%d", &a[i].soLuong);
			if (a[i].soLuong <= 0)
				printf("So luong sach khong duoc <=0, vui long nhap lai!\n");
		} while (a[i].soLuong <= 0);
		getchar();
	kiemtra:	printf("\nNhap tiep sach nhan 1, nhap xong nhan 0:");
		scanf_s("%d", &k);
		if (k != 1 && k != 0)
		{
			printf("Chi duoc nhap 1 hoac 0, vui long nhap lai\n ");
			goto kiemtra;
		}
		if (k == 1)
		{
			n++;
			i++;
		}
	}
	countBook(n);
	ghiDuLieu(a, n);
}
void themSach(Book *&a, int &n)// Thêm n cuốn sách vào mảng (động) sách a
{
	int tongSach = 0;
	FILE*f_count = fopen(numbersOfBook, "rb");
	FILE*f = fopen(listBook, "rb");
	if (f == NULL || f_count == NULL)
	{
		themSach_first(a, n);
		exit('0');
	}
	else
	{
		fread(&tongSach, sizeof(int), 1, f_count);
	}
	fclose(f_count);
	n = tongSach;
	a = (Book*)malloc(sizeof(Book)*n);
	if (f == NULL)
	{
		printf("Da xay ra loi!\n");
		exit('0');
	}
	else
	{
		int i = 0;
		while (i < n)
		{
			fread(&a[i], sizeof(Book), 1, f);
			i++;
		}
	}
	fclose(f);
	printf("					THEM MOT DAU SACH MOI VAO THU VIEN                  \n\n");
	int k = 1, i = n;
	n++;
	while (k!=0)
	{
		a = (Book*)realloc(a, sizeof(Book)*n);
		printf("Quyen sach thu %i:\n", i + 1);
		rewind(stdin);
	nhaplaimasach:	printf("\tNhap vao ma sach:");
		gets_s(a[i].ISBN);
		if (Tim_MS_Sach(a, n-1, a[i].ISBN) != -1)
		{
			printf("\tMa sach da co, vui long nhap lai!\n");
			goto nhaplaimasach;
		}
		printf("\tTen sach: ");
		gets_s(a[i].tenSach);
		printf("\tTac gia: ");
		gets_s(a[i].tacGia);
		printf("\tNha xuat ban: ");
		gets_s(a[i].nxb);
		printf("\tNam xuat ban: ");
		scanf_s("%i", &a[i].namXB);
		rewind(stdin);
		printf("\tThe loai sach: ");
		gets_s(a[i].theLoai);
		printf("\tVi tri sach trong thu vien: ");
		gets_s(a[i].viTri);
		do
		{
			printf("\tSo luong sach: ");
			scanf_s("%d", &a[i].soLuong);
			if (a[i].soLuong <= 0)
				printf("So luong sach khong duoc <=0, vui long nhap lai!\n");
		} while (a[i].soLuong<=0);
		getchar();
	kiemtra:	printf("\nNhap tiep sach nhan 1, nhap xong nhan 0:");
		scanf_s("%d", &k);
		if (k != 1 && k != 0)
		{
			printf("Chi duoc nhap 1 hoac 0, vui long nhap lai\n ");
			goto kiemtra;
		}
		if (k == 1)
		{
			n++;
			i++;
		}
	}
	countBook(n);
	ghiDuLieu(a, n);
}
void ghiDuLieu(Book*& a, int n)
{
	FILE* f = fopen(listBook, "wb");
	if (f == NULL)
		printf("Danh sach chua duoc tao!\n");
	else
	{
		int i = 0;
		while (i<n)
		{
			fwrite(&a[i], sizeof(Book), 1, f);
			i++;
		}
	}
	fclose(f);
}
void docDuLieu(Book *&a, int &n)
{
	Book g;
	int tongSach = 0;
	FILE* f_count = fopen(numbersOfBook, "rb");
	if (f_count == NULL)
	{
		printf("Thu vien khong co sach,vui long them sach!\n");
		exit('0');
	}
	else
	{
		fread(&tongSach, sizeof(int), 1, f_count);
	}
	fclose(f_count);
	n = tongSach;
	FILE* f = fopen(listBook, "rb");
	if (f == NULL)
	{
		printf("Da xay ra loi!\n");
		exit('0');
	}
	else
	{
		a = (Book*)malloc(sizeof(Book)*n);
		for (int i = 0; i < n; i++)
		{
			fread(&g, sizeof(Book), 1, f);
			a[i] = g;
		}
	}
	fclose(f);
}
void inToanBoSach()
{
	Book* a;
	int n;
	docDuLieu(a, n);
	printf("                     THONG TIN CAC QUYEN SACH CO TRONG THU VIEN LA                      \n\n");
	for (int i = 0; i < n; i++)
	{
		printf("Thong tin quyen sach thu %i la:\n", i + 1);
		printf("\t\tMa sach:");
		puts(a[i].ISBN);
		printf("\t\tTen sach:");
		puts(a[i].tenSach);
		printf("\t\tTac gia:");
		puts(a[i].tacGia);
		printf("\t\tNha xuat ban:");
		puts(a[i].nxb);
		printf("\t\tNam xuat ban:%i\n", a[i].namXB);
		printf("\t\tThe loai:");
		puts(a[i].theLoai);
		printf("\t\tVi tri:");
		puts(a[i].viTri);
		printf("\t\tSo luong: %i\n\n", a[i].soLuong);
	}
}
void in_1_QuyenSach(Book *a, int n, int vitri)
{
	printf("\t\t\tMa sach:\t");
	puts(a[vitri].ISBN);
	printf("\t\t\ttTen sach:\t");
	puts(a[vitri].tenSach);
	printf("\t\t\tTac gia:\t");
	puts(a[vitri].tacGia);
	printf("\t\t\tNha xuat ban:\t");
	puts(a[vitri].nxb);
	printf("\t\t\tNam xuat ban:\t%i\n", a[vitri].namXB);
	printf("\t\t\tThe loai:\t");
	puts(a[vitri].theLoai);
	printf("\t\t\ti tri:\t");
	puts(a[vitri].viTri);
	printf("\t\t\tSo luong:\t%i\n\n", a[vitri].soLuong);
	printf("\n");
}
void suaThongTinSach()
{
	Book * a;
	int n,vitri;
	docDuLieu(a, n);
	char check[20];
	rewind(stdin);
	printf("Vui long nhap vao ma so sach muon sua thong tin:");
	gets_s(check);
	vitri = Tim_MS_Sach(a, n, check);
	if (vitri == -1)
		printf("Khong co ma so sach nay!\n");
	else
	{
		//Xuất ra thông tin của cuốn sách có mã số vitri cho người dùng sửa.
		printf("Thong tin quyen sach ma ban muon sua la:\n");
		in_1_QuyenSach(a, n, vitri);
		//---- Sửa thông tin sách tại vị trí vitri vừa tìm được
		printf("Moi ban sua thong tin:\n");
		printf("\tTen sach: ");
		gets_s(a[vitri].tenSach);
		printf("\tTac gia: ");
		gets_s(a[vitri].tacGia);
		printf("\tNha xuat ban: ");
		gets_s(a[vitri].nxb);
		printf("\tNam xuat ban: ");
		scanf_s("%i", &a[vitri].namXB);
		rewind(stdin);
		printf("\tThe loai sach:");
		gets_s(a[vitri].theLoai);
		printf("\tVi tri sach trong thu vien: ");
		gets_s(a[vitri].viTri);
		do
		{
			printf("\tSo luong sach: ");
			scanf_s("%d", &a[vitri].soLuong);
			if (a[vitri].soLuong <= 0)
				printf("So luong sach khong duoc <=0, vui long nhap lai!\n");
		} while (a[vitri].soLuong <= 0);
		printf("  SUA THONG TIN QUYEN SACH THANH CONG!\n  ");
		ghiDuLieu(a, n);
	}
}
void xoa_Sach()
{
	Book*a;
	int n;
	docDuLieu(a, n);
	char check[20];
	rewind(stdin);
	printf("Nhap vao ma so sach ma ban muon xoa: ");
	gets_s(check);
	int ms = Tim_MS_Sach(a, n, check);
	if (ms == -1)
		printf("Khong tim thay ma sach nay trong thu vien!\n");
	else
	{
		printf("----------------------------------------------\n");
		printf("\tTHONG TIN CUON SACH MA BAN MUON XOA!\n");
		in_1_QuyenSach(a, n, ms);
		printf("Nhan ENTER de xoa sach");
		getchar();
		for (int i = ms; i < n - 1; i++)
		{
			a[i] = a[i + 1];
		}
		n--;
		a = (Book*)realloc(a,n*sizeof(Book));
		printf(" XOA THANH CONG!\n ");
		countBook(n);
		ghiDuLieu(a, n);
	}	
}
void print_TimSach_TheoTen()
{
	Book *a;
	int n;
	docDuLieu(a, n);
	char check_Name[100];
	rewind(stdin);
	printf("Nhap vao ten quyen sach ma ban muon tim: ");
	gets_s(check_Name);
	int check=tim_Sach_TenSach(a, n, check_Name);
	if (check == -1)
		printf("Khong tim thay ten sach nay trong thu vien!\n");
	else
	{
		printf("\tTIM SACH THANH CONG!\n");
		printf("\tThong tin quyen sach la\n\n");
		in_1_QuyenSach(a, n, check);
	}
}
void print_TimSach_ISBN()
{
	Book* a;
	int n;
	docDuLieu(a, n);
	char ms[20];
	rewind(stdin);
	printf("Nhap vao  ma ban muon tim: ");
	gets_s(ms);
	int check = Tim_MS_Sach(a, n, ms);
	if (check == -1)
		printf("Khong tim thay ma sach(ISBN)  nay trong thu vien!\n");
	else
	{
		printf("\tTIM SACH THANH CONG!\n");
		printf("\tThong tin quyen sach la\n\n");
		in_1_QuyenSach(a, n, check);
	}
}
