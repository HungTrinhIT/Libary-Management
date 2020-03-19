typedef struct User
{
	struct 
	{
		char username[50];
		char password[50];
	}Account;
	struct 
	{
		char hoten[50];
		char CMND[13];
		char DoB[11];	 // dd/mm/yyyy
		char diachi[100];
		int gioitinh;	 // 1: nam ; 0:nu
	}Information;
	int status;			 // 1: actived ; 0:blocked
	int rank;			 // 0: admin  ; 1: quan ly thu vien   ; 2: chuyen vien
};

char *nhap_pass();
void tao_nguoi_dung();
int dang_nhap(int &rank, char *&currenUser);
void dang_xuat(char currenUser[]);
void doi_mat_khau(char **currenUser);
void cap_nhat_thong_tin(char **currenUser);
void create_userfile();
void phan_quyen_nguoi_dung();
void userFunctionMenu(int rank, char **currenUser);
