struct Book
{
	char ISBN[20];
	char tenSach[100];
	char tacGia[50];
	char nxb[100];
	int namXB;
	char theLoai[50];
	char viTri[10];
	int soLuong;
	float giaSach;
};

void themSach(Book *&a, int &n);
void themSach_first(Book*&a, int &n);
void countBook(int n);
void inToanBoSach();
void ghiDuLieu(Book*& a, int n);
void docDuLieu(Book *&a, int &n);
void suaThongTinSach();
void xoa_Sach();
int Tim_MS_Sach(Book *a, int n, char ms[20]);
int tim_Sach_TenSach(Book*a, int n, char check_Name[100]);// Tìm theo tên sách
void print_TimSach_ISBN();
void print_TimSach_TheoTen();
void bookFunctionMenu(int rank, char **currenUser);
void timSachTheoISBN(char *ISBN, char tenSach[]);

