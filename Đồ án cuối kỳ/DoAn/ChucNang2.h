struct date
{
	unsigned int ngay;
	unsigned int thang;
	unsigned int nam;
};
struct DocGia
{
	char MaDocGia[20];
	char HoTen[50];
	char CMND[20];
	date daB;
	char GioiTinh[10];
	char Email[50];
	char DiaChi[100];
	date ngaylapthe;
	date ngayhethan;
};

int check_NamNhuan(int nam);
int check_Thang(int thang, int nam);
void themDocGia(DocGia*& a, int &n);
void ghiDuLieu(DocGia* a, int n);
void docDuLieu(DocGia *&a, int &n);
void inToanBo_DocGia();
void sua_ThongTin_DocGia();
int Tim_MS_DocGia(DocGia *a, int n, char c[20]);
int Tim_CMND_DocGia(DocGia *a, int n, char check[20]);
int Tim_HoTen_DocGia(DocGia *a, int n, char check[50]);
void print_1_DocGia(DocGia *a, int n, int vitri);
void print_DocGia_HoTen();
void print_DocGia_CMND();
void xoaDocGia(DocGia *&a, int &n);