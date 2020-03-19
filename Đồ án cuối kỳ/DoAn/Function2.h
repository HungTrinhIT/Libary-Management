struct date
{
	int ngay;
	int thang;
	int nam;
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

void readerFunctionMenu(int rank, char **currenUser);
void resizeConsole(int width, int height);
int check_LeapYear(int year);
int return_day(int month, int year);
bool check_day_month_year(int day, int month, int year);
void themDocGia(DocGia*& reader, int &n);
void countReader(int n);
void ghiDuLieu(DocGia*& reader, int n);
void docDuLieu(DocGia *&reader, int &n);
void inToanBo_DocGia();
void sua_ThongTin_DocGia();
int Tim_MS_DocGia(DocGia *reader, int n, char c[20]);
int Tim_CMND_DocGia(DocGia *reader, int n, char check[20]);
int Tim_HoTen_DocGia(DocGia *reader, int n, char check[50]);
void print_1_DocGia(DocGia *reader, int n, int vitri);
void print_DocGia_HoTen();
void print_DocGia_CMND();
void xoaDocGia();
bool check_Reader(char *maDocGia);
void tenDocGiaTheoMaDG(char *maDocGia, char ten[]);