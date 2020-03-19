#include"stdafx.h"
#include"Function3.h"
#include "UI.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<Windows.h>

#define listBook "C:\\LibManagement\\bookList.bin"
#define numbersOfBook "C:\\LibManagement\\countbook.bin"

void bookFunctionMenu(int rank, char **currenUser)
{
	Book *book;
	int n;
	system("cls");

	printf("\n\t\t     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»");
	printf("\n\t\t     º                            QUAN LY SACH                              º");
	printf("\n\t\t     ÌÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¹");
	printf("\n\t\t     º                                  ³                                   º");
	printf("\n\t\t     º1 .TIM KIEM SACH THEO ISBN        ³2. TIM KIEM SACH THEO TEN SACH     º");	
	printf("\n\t\t     º                                  ³                                   º");
	if (rank != 2)
	{
		printf("\n\t\t     º3. XEM DANH SACH SACH             ³4. THEM SACH                       º");
		printf("\n\t\t     º                                  ³                                   º");
		printf("\n\t\t     º5. CHINH SUA THONG TIN SACH       ³6. XOA THONG TIN SACH              º");
		printf("\n\t\t     º                                  ³                                   º");
	}
	
	printf("\n\t\t     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
	printf("\t\t      0. Quay lai man hinh chinh \n");
	printf("\n\t\tNHAP CHUC NANG MUON THUC HIEN: ");

	int ch;
	scanf_s("%i", &ch);
	switch (ch)
	{
	case 0:
		system("cls");
		menu(rank, currenUser);
		break;
	case 1:
		print_TimSach_ISBN();
		break;
	case 2:
		print_TimSach_TheoTen();
		break;
	case 3:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay! \n");
			break;
		}
		else
		{
			inToanBoSach();
			break;
		}
	case 4:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay! \n");
			break;
		}
		else
		{
			themSach(book,n);
			break;
		}
	case 5:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay! \n");
			break;
		}
		else
		{
			suaThongTinSach();
			break;
		}
	case 6:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay! \n");
			break;
		}
		else
		{
			xoa_Sach();
			break;
		}
	default:
		printf("Khong co chuc nang nay! \n");
		break;
	}

	Select:
	printf("\n\t\tNHAN ENTER DE TIEP TUC / NHAN ESC DE QUAY LAI MAN HINH CHINH: ");
	char c = _getch();
	if (c == 13)
	{
		system("cls");
		bookFunctionMenu(rank, currenUser);
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
	while (i<n && strcmp(_strupr(a[i].tenSach), _strupr(check_Name)) != 0)
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
	printf("\n\n");
	printf("\t\t\t\t\t\tTHEM MOT DAU SACH MOI VAO THU VIEN\n\n");
	while (k != 0)
	{
		a = (Book*)realloc(a, sizeof(Book)*n);
		printf("\t\t\tQuyen sach thu %i:\n", i + 1);
		rewind(stdin);
		printf("\t\t\t\tNhap vao ma sach(ISBN:xxxxxxxxxxxxx 13 ky tu): ");
		gets_s(a[i].ISBN);
		if (Tim_MS_Sach(a, n - 1, a[i].ISBN) != -1)
		{
			int vitri = Tim_MS_Sach(a, n - 1, a[i].ISBN);
			printf("\t\t\t\tMa sach da co!\n");
			n--;
			i--;
			a = (Book*)realloc(a, sizeof(Book)*n);
			int t;
			printf("\t\t\t\tMoi nhap vao so luong sach ma ban muon them vao:");
			scanf_s("%d", &t);
			a[vitri].soLuong += t;
			goto kiemtra;
		}
		printf("\t\t\t\tTen sach: ");
		gets_s(a[i].tenSach);
		printf("\t\t\t\tTac gia: ");
		gets_s(a[i].tacGia);
		printf("\t\t\t\tNha xuat ban: ");
		gets_s(a[i].nxb);
		printf("\t\t\t\tNam xuat ban: ");
		scanf_s("%i", &a[i].namXB);
		rewind(stdin);
		printf("\t\t\t\tThe loai sach: ");
		gets_s(a[i].theLoai);
		printf("\t\t\t\tVi tri sach trong thu vien: ");
		gets_s(a[i].viTri);
		do
		{
			printf("\t\t\t\tSo luong sach: ");
			scanf_s("%d", &a[i].soLuong);
			if (a[i].soLuong <= 0)
				printf("\t\t\tSo luong sach khong duoc <=0, vui long nhap lai!\n");
		} while (a[i].soLuong <= 0);
		printf("\t\t\t\tNhap vao gia sach:");
		scanf_s("%f", &a[i].giaSach);
	kiemtra:	printf("\n\t\t\tNhap tiep sach nhan 1, nhap xong nhan 0:");
		scanf_s("%d", &k);
		if (k != 1 && k != 0)
		{
			printf("\t\t\tChi duoc nhap 1 hoac 0, vui long nhap lai\n ");
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
		printf("\t\t\tDa xay ra loi!\n");
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
	printf("\t\t\t\t\t\tTHEM MOT DAU SACH MOI VAO THU VIEN                  \n\n");
	int k = 1, i = n;
	n++;
	while (k != 0)
	{
		a = (Book*)realloc(a, sizeof(Book)*n);
		printf("\t\t\tQuyen sach thu %i:\n", i + 1);
		rewind(stdin);
		printf("\t\t\t\tNhap vao ma sach(ISBN:xxxxxxxxxxxxx 13 ky tu): ");
		gets_s(a[i].ISBN);
		if (Tim_MS_Sach(a, n - 1, a[i].ISBN) != -1)
		{
			int vitri = Tim_MS_Sach(a, n - 1, a[i].ISBN);
			printf("\t\t\t\tMa sach da co!\n");
			n--;
			i--;
			a = (Book*)realloc(a, sizeof(Book)*n);
			int t;
			printf("\t\t\t\tMoi nhap vao so luong sach ma ban muon them vao:");
			scanf_s("%d", &t);
			a[vitri].soLuong += t;
			goto kiemtra;
		}
		printf("\t\t\t\tTen sach: ");
		gets_s(a[i].tenSach);
		printf("\t\t\t\tTac gia: ");
		gets_s(a[i].tacGia);
		printf("\t\t\t\tNha xuat ban: ");
		gets_s(a[i].nxb);
		printf("\t\t\t\tNam xuat ban: ");
		scanf_s("%i", &a[i].namXB);
		rewind(stdin);
		printf("\t\t\t\tThe loai sach: ");
		gets_s(a[i].theLoai);
		printf("\t\t\t\tVi tri sach trong thu vien: ");
		gets_s(a[i].viTri);
		do
		{
			printf("\t\t\t\tSo luong sach: ");
			scanf_s("%d", &a[i].soLuong);
			if (a[i].soLuong <= 0)
				printf("\t\t\tSo luong sach khong duoc <=0, vui long nhap lai!\n");
		} while (a[i].soLuong <= 0);
		printf("\t\t\t\tNhap vao gia sach:");
		scanf_s("%f", &a[i].giaSach);
	kiemtra:	printf("\n\t\t\tNhap tiep sach nhan 1, nhap xong nhan 0:");
		scanf_s("%d", &k);
		if (k != 1 && k != 0)
		{
			printf("\t\t\tChi duoc nhap 1 hoac 0, vui long nhap lai\n ");
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
		printf("\t\t\tDanh sach chua duoc tao!\n");
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
	FILE* f_count = fopen(numbersOfBook, "ab+");
	if (f_count == NULL)
	{
		printf("\t\t\tThu vien khong co sach,vui long them sach!\n");
		exit(0);
	}
	else
	{
		fread(&tongSach, sizeof(int), 1, f_count);
	}
	fclose(f_count);
	n = tongSach;
	FILE* f = fopen(listBook, "ab+");
	if (f == NULL)
	{
		printf("\t\t\tDa xay ra loi!\n");
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
	printf("\n\t\t\t\t\t\t\t\tDANH SACH CAC SACH CO TRONG THU VIEN LA");
	printf("\nÉÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍ»");
	printf("\nº     ISBN    ³             TEN SACH              ³            TAC GIA           ³ NXB ³          NHA XUAT BAN             ³      THE LOAI      ³VI TRI³  SL ³GIA SACH º");
	printf("\nÌÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍÍÍÍÍ¹");
	for (int i = 0; i<n; i++)
	{
		printf("\nº%-13s", a[i].ISBN);
		printf("³%-35s", a[i].tenSach);
		printf("³%-30s", a[i].tacGia);
		printf("³%5d", a[i].namXB);
		printf("³%-35s", a[i].nxb);
		printf("³%-20s", a[i].theLoai);
		printf("³%-6s", a[i].viTri);
		printf("³%5d", a[i].soLuong);
		printf("³%9.0fº", a[i].giaSach);
	}
	printf("\nÈÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍ¼");
	printf("\n");
}
void in_1_QuyenSach(Book* a, int n, int vitri)
{
	docDuLieu(a, n);
	printf("\n\t\t\t\t\t\t\t\tTHONG TIN QUYEN SACH VUA TIM DUOC LA");
	printf("\nÉÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÑÍÍÍÍÍÍÑÍÍÍÍÍÑÍÍÍÍÍÍÍÍÍ»");
	printf("\nº   ISBN      ³             TEN SACH                   ³            TAC GIA           ³ NXB ³          NHA XUAT BAN        ³      THE LOAI      ³VI TRI³  SL ³GIA SACH º");
	printf("\nÌÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍØÍÍÍÍÍÍØÍÍÍÍÍØÍÍÍÍÍÍÍÍÍ¹");
	{
		printf("\nº%-13s", a[vitri].ISBN);
		printf("³%-40s", a[vitri].tenSach);
		printf("³%-30s", a[vitri].tacGia);
		printf("³%5d", a[vitri].namXB);
		printf("³%-30s", a[vitri].nxb);
		printf("³%-20s", a[vitri].theLoai);
		printf("³%-6s", a[vitri].viTri);
		printf("³%5d", a[vitri].soLuong);
		printf("³%9.0fº", a[vitri].giaSach);
	}
	printf("\nÈÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÏÍÍÍÍÍÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍÍ¼");
	printf("\n");
}
void suaThongTinSach()
{
	Book * a;
	int n, vitri;
	docDuLieu(a, n);
	char check[20];
	rewind(stdin);
	printf("\t\t\tVui long nhap vao ma so sach muon sua thong tin:");
	gets_s(check);
	vitri = Tim_MS_Sach(a, n, check);
	if (vitri == -1)
		printf("\t\t\tKhong co ma so sach nay!\n");
	else
	{
		//Xuất ra thông tin của cuốn sách có mã số vitri cho người dùng sửa.
		printf("\t\t\tThong tin quyen sach ma ban muon sua la:\n");
		in_1_QuyenSach(a, n, vitri);
		//---- Sửa thông tin sách tại vị trí vitri vừa tìm được
		printf("\t\t\tMoi ban sua thong tin:\n");
		int choice;
		printf("\n\t\t\t\t1. Sua ten.");
		printf("\n\t\t\t\t2. Sua tac gia.");
		printf("\n\t\t\t\t3. Sua nha xuat ban.");
		printf("\n\t\t\t\t4. Sua nam xuat ban.");
		printf("\n\t\t\t\t5. Sua the loai.");
		printf("\n\t\t\t\t6. Sua vi tri.");
		printf("\n\t\t\t\t7. Sua gia sach.");
		printf("\n\t\t\t\t8. Sua so luong sach.");
		int k = 1;
		while (k != 0)
		{
			printf("\n\t\t\tNhap vao thong tin ma ban muon sua:");
			scanf_s("%i", &choice);
			rewind(stdin);
			switch (choice)
			{
			case 1:
				printf("\t\t\t\tTen sach:");
				gets_s(a[vitri].tenSach);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			case 2:
				printf("\t\t\t\tTac gia: ");
				gets_s(a[vitri].tacGia);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);

				break;
			case 3:
				printf("\t\t\t\tNha xuat ban: ");
				gets_s(a[vitri].nxb);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			case 4:
				printf("\t\t\t\tNam xuat ban: ");
				scanf_s("%i", &a[vitri].namXB);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			case 5:
				rewind(stdin);
				printf("\t\t\t\tThe loai sach:");
				gets_s(a[vitri].theLoai);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			case 6:
				printf("\t\t\t\tVi tri sach trong thu vien: ");
				gets_s(a[vitri].viTri);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			case 7:
				printf("\t\t\t\tGia sach:");
				scanf_s("%f", &a[vitri].giaSach);
				printf("\t\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			case 8:
				do
				{
					printf("\t\t\t\tSo luong sach: ");
					scanf_s("%d", &a[vitri].soLuong);
					if (a[vitri].soLuong <= 0)
						printf("\t\t\tSo luong sach khong duoc <=0, vui long nhap lai!\n");
				} while (a[vitri].soLuong <= 0);
				printf("\t\t\tSUA THONG TIN QUYEN SACH THANH CONG!\n");
				ghiDuLieu(a, n);
				break;
			default:
				printf("\t\t\tYeu cau khong hop le!\n");
				break;
			}
			printf("\n\t\t\tBan co muon sua tiep khong?\n");
			printf("\t\t\t\t0. No!\n\t1. Yes!\n");
			scanf_s("%d", &k);
		}
	}
}
void xoa_Sach()
{
	printf("\n\n");
	printf("\t\t\t\t\t\t\tXOA MOT QUYEN SACH \n");
	Book*a;
	int n;
	docDuLieu(a, n);
	char check[20];
	rewind(stdin);
	printf("\t\t\tNhap vao ma so sach ma ban muon xoa: ");
	gets_s(check);
	int ms = Tim_MS_Sach(a, n, check);
	if (ms == -1)
		printf("\t\t\tKhong tim thay ma sach nay trong thu vien!\n");
	else
	{
		printf("----------------------------------------------\n");
		printf("\t\t\t\tTHONG TIN CUON SACH MA BAN MUON XOA!\n");
		in_1_QuyenSach(a, n, ms);
		printf("\t\t\tNhan ENTER de xoa sach");
		printf("\t\t\tBan co chac muon xoa quyen sach nay khong!\n1.Co\n2.Khong\n");
		if (getchar() == '1')
		{
			for (int i = ms; i < n - 1; i++)
			{
				a[i] = a[i + 1];
			}
			n--;
			a = (Book*)realloc(a, n * sizeof(Book));
			printf("\t\t\tXOA THANH CONG!\n ");
			countBook(n);
			ghiDuLieu(a, n);
		}
		else
			printf("\t\t\tKhong quyen sach nao duoc XOA!\n");
	}
}
void print_TimSach_TheoTen()
{
	Book *a;
	int n;
	docDuLieu(a, n);
	char check_Name[100];
	rewind(stdin);
	printf("\t\t\tNhap vao ten quyen sach ma ban muon tim: ");
	gets_s(check_Name);
	int check = tim_Sach_TenSach(a, n, check_Name);
	if (check == -1)
		printf("\t\t\tKhong tim thay ten sach nay trong thu vien!\n");
	else
	{
		printf("\t\t\t\tTIM SACH THANH CONG!\n");
		printf("\t\t\t\tThong tin quyen sach la\n\n");
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
	printf("\t\t\tNhap vao  ma sach (ISBN)ban muon tim: ");
	gets_s(ms);
	int check = Tim_MS_Sach(a, n, ms);
	if (check == -1)
		printf("\t\t\tKhong tim thay ma sach(ISBN)  nay trong thu vien!\n");
	else
	{
		printf("\t\t\t\tTIM SACH THANH CONG!\n");
		printf("\t\t\t\tThong tin quyen sach la\n\n");
		in_1_QuyenSach(a, n, check);
	}
}

void timSachTheoISBN(char *ISBN, char tenSach[])
{
	Book book;
	FILE *f = fopen(listBook, "rb");
	while (!feof(f))
	{
		fread(&book, sizeof(Book), 1, f);
		if (strcmp(book.ISBN, ISBN) == 0)
		{
			strcpy(tenSach, book.tenSach);
			break;
		}
	}
}