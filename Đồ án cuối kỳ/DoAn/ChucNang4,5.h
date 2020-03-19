typedef struct PhieuMuonSach
{
	char maDocGia[6];
	char ngayMuon[11];
	char ngayTraDuKien[11];
	char ISBN[14];
};

typedef struct PhieuTraSach
{
	char maDocGia[6];
	char ngayMuon[11];
	char ngayTraDuKien[11];
	char ngayTraThucTe[11];
	char ISBN[14];
};


void lapPhieuMuonSach(int rank, char **currenUser);
void lapPhieuTraSach(int rank, char **currenUser);
void loadFile(char reader[], int &n);
void recountNumberOfBook(char *ISBN, int key);	// Sua lai so luong cua quyen sach tron thu vien khi duoc muon