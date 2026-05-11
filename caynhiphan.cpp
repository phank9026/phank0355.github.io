#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <windows.h> // Thư viện điều khiển console Windows

using namespace std;

// --- HÀM ĐIỀU KHIỂN MÀU SẮC ---
void setColor(int color) {
    // 10: Xanh lá, 11: Xanh ngọc, 12: Đỏ, 14: Vàng, 15: Trắng, 13: Hồng tím
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// --- CẤU TRÚC DỮ LIỆU ---
struct HoaDon {
    int soHD;
    string tenKH;
    string ngay;
    double tongTien;
};

struct Node {
    HoaDon data;
    Node* pLeft;
    Node* pRight;
};

typedef Node* Tree;

void Init(Tree &t) { t = NULL; }

// --- QUẢN LÝ CÂY NHỊ PHÂN ---
void ThemNode(Tree &t, HoaDon hd) {
    if (t == NULL) {
        Node* p = new Node;
        p->data = hd;
        p->pLeft = p->pRight = NULL;
        t = p;
    } else {
        if (hd.soHD < t->data.soHD) ThemNode(t->pLeft, hd);
        else if (hd.soHD > t->data.soHD) ThemNode(t->pRight, hd);
    }
}

// --- NHẬP LIỆU AN TOÀN ---
int nhapSoNguyen(string label) {
    int n;
    while (true) {
        setColor(15); cout << label; // Màu trắng cho nhãn nhập liệu
        if (cin >> n && n > 0) return n;
        setColor(12); cout << "   -> Loi: Vui long nhap so nguyen duong!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double nhapSoThuc(string label) {
    double n;
    while (true) {
        setColor(15); cout << label;
        if (cin >> n && n >= 0) return n;
        setColor(12); cout << "   -> Loi: Vui long nhap so tien hop le!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// --- CHỨC NĂNG ---
void NhapDanhSach(Tree &t) {
    int n = nhapSoNguyen("\n[*] Nhap so luong hoa don muon them: ");
    for (int i = 0; i < n; i++) {
        HoaDon hd;
        setColor(11); cout << "\n--- NHAP HOA DON THU " << (i + 1) << " ---" << endl;
        hd.soHD = nhapSoNguyen(" + So hoa don: ");
        cin.ignore();
        setColor(15); cout << " + Ten khach hang: "; getline(cin, hd.tenKH);
        cout << " + Ngay (dd/mm/yyyy): "; getline(cin, hd.ngay);
        hd.tongTien = nhapSoThuc(" + Tong tien: ");
        ThemNode(t, hd);
    }
    setColor(10); cout << "\n[OK] Da them du lieu vao cay thanh cong!" << endl;
}

void XuatDoc(Tree t) {
    if (t != NULL) {
        XuatDoc(t->pLeft);
        setColor(15); cout << "| " << left << setw(8) << t->data.soHD;
        setColor(15); cout << "| " << setw(22) << t->data.tenKH;
        setColor(15); cout << "| " << setw(12) << t->data.ngay;
        setColor(10); cout << "| " << right << setw(15) << fixed << setprecision(0) << t->data.tongTien;
        setColor(15); cout << " |" << endl;
        XuatDoc(t->pRight);
    }
}

void VeBang(Tree t) {
    if (t == NULL) {
        setColor(12); cout << "\n[!] Danh sach dang trong!" << endl;
        return;
    }
    setColor(14); // Màu vàng cho bảng
    cout << "\n" << setw(45) << "DANH SACH HOA DON " << endl;
    cout << "+" << setfill('-') << setw(10) << "+" << setw(23) << "+" << setw(13) << "+" << setw(18) << "+" << endl;
    cout << "| " << left << setfill(' ') << setw(8) << "MA HD" 
         << "| " << setw(21) << "TEN KH" 
         << "| " << setw(11) << "NGAY" 
         << "| " << setw(15) << "TONG TIEN" << " |" << endl;
    cout << "+" << setfill('-') << setw(10) << "+" << setw(23) << "+" << setw(13) << "+" << setw(18) << "+" << endl;
    
    XuatDoc(t);
    
    setColor(14);
    cout << "+" << setfill('-') << setw(10) << "+" << setw(23) << "+" << setw(13) << "+" << setw(18) << "+" << endl;
    setColor(15);
}

Node* TimKiem(Tree t, int ma) {
    if (t == NULL || t->data.soHD == ma) return t;
    if (ma < t->data.soHD) return TimKiem(t->pLeft, ma);
    return TimKiem(t->pRight, ma);
}

void GiaiPhong(Tree &t) {
    if (t != NULL) {
        GiaiPhong(t->pLeft);
        GiaiPhong(t->pRight);
        delete t;
        t = NULL;
    }
}

// --- GIAO DIỆN MENU ---
void hienThiMenu() {
    setColor(13); // Màu hồng tím cho khung Menu
    cout << "\n*************************************" << endl;
    cout << "*  "; setColor(14); cout << "HE THONG QUAN LY HOA DON BST"; setColor(13); cout << "   *" << endl;
    cout << "*************************************" << endl;
    
    setColor(11); // Màu xanh ngọc cho các lựa chọn
    cout << "  [1] "; setColor(15); cout << "Them moi hoa don" << endl;
    setColor(11); cout << "  [2] "; setColor(15); cout << "Hien thi danh sach" << endl;
    setColor(11); cout << "  [3] "; setColor(15); cout << "Tim kiem nhanh theo Ma HD" << endl;
    setColor(11); cout << "  [4] "; setColor(12); cout << "Thoat chuong trinh" << endl;
    
    setColor(13);
    cout << "*************************************" << endl;
}

int main() {
    Tree t;
    Init(t);
    int choice;

    do {
        hienThiMenu();
        choice = nhapSoNguyen("  ==> Nhap lua chon: ");

        switch (choice) {
            case 1: NhapDanhSach(t); break;
            case 2: VeBang(t); break;
            case 3: {
                if(t == NULL) {
                    setColor(12); cout << "\n[!] Cay dang trong, khong co du lieu de tim!" << endl;
                } else {
                    int ma = nhapSoNguyen("\n[?] Nhap Ma HD can tim: ");
                    Node* res = TimKiem(t, ma);
                    if (res) {
                        setColor(10); cout << "\n[+] TIM THAY HOA DON!" << endl;
                        setColor(15); cout << "    Khach hang: " << res->data.tenKH << endl;
                        cout << "    Tong tien:  "; setColor(10); cout << (long long)res->data.tongTien << " VND" << endl;
                    } else {
                        setColor(12); cout << "\n[!] Khong tim thay ma HD nay trong he thong." << endl;
                    }
                }
                break;
            }
            case 4: 
                GiaiPhong(t); 
                setColor(14); cout << "\n[OK] Da giai phong bo nho. Tam biet!" << endl; 
                setColor(15);
                break;
            default: 
                setColor(12); cout << "\n[!] Lua chon khong hop le!" << endl;
        }
    } while (choice != 4);

    return 0;
}