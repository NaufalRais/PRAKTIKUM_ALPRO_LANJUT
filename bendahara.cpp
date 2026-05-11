#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
using namespace std;

int menu;
char kembali;

struct Pemasukan {
    string nama;
    int nominal;
    int tanggal, bulan, tahun;
    int id;
};

struct Pengeluaran {
    string nama;
    int nominal;
    int tanggal, bulan, tahun;
    int id;
};

Pemasukan daftarPemasukan[100];
Pengeluaran daftarPengeluaran[100];
int jumlahPemasukan = 0;
int jumlahPengeluaran = 0;
int nomorCatatan = 1;

void menuUtama();
void CatatPemasukkan(Pemasukan *p, int *jumlahPemasukan);
void CatatPengeluaran(Pengeluaran *p, int *jumlahPengeluaran);
void TampilCatatan();
void riwayat();
void kosong();
void TampilPemasukan();
void TampilPengeluaran();
void TampilPemasukanTahunan();
void TampilPemasukanBulanan();
void TampilPengeluaranTahunan();
void TampilPengeluaranBulanan();

// Deklarasi fungsi sorting
void sortTanggalPemasukan();
void sortTanggalPengeluaran();
void sortTahunPemasukan();
void sortTahunPengeluaran();
void sortBulanPemasukan();
void sortBulanPengeluaran();
void sortSemuaPemasukan();
void sortSemuaPengeluaran();

bool validasiTanggal(int tanggal, int bulan, int tahun);
bool inputTanggal(int &tanggal, int &bulan, int &tahun);

int main(){
    do{
        menuUtama();
        switch(menu){
            case 1: system("cls"); CatatPemasukkan(daftarPemasukan, &jumlahPemasukan); break;
            case 2: system("cls"); CatatPengeluaran(daftarPengeluaran, &jumlahPengeluaran); break;
            case 3: system("cls"); TampilCatatan(); break;
            case 4: system("cls"); riwayat(); break;
            case 0: 
                cout << "Terima kasih!\n";
                return 0;
            default:
                system("cls");
                cout << "==================\n";
                cout << "| Menu tidak ada |\n";
                cout << "==================\n";
                break;
        }

        if (menu != 0) {
            cout << "\nApakah anda ingin kembali ke menu? (y/t) : ";
            cin >> kembali;
        }

    } while (kembali == 'y' || kembali == 'Y');
}

void menuUtama(){
    system("cls");
    cout << "============================\n";
    cout << "|           MENU           |\n";
    cout << "============================\n";
    cout << "| 1. Catat Pemasukan       |\n";
    cout << "| 2. Catat Pengeluaran     |\n";
    cout << "| 3. Tampilkan Data        |\n";
    cout << "| 4. Riwayat Aktifitas     |\n";
    cout << "============================\n";
    cout << "| 0. Keluar                |\n";
    cout << "============================\n";
    cout << "Pilih menu : ";
    cin >> menu;
}

void CatatPemasukkan(Pemasukan *p, int *jumlahPemasukan){
    cout << "Tambah Catatan Pemasukan" << endl;
    cout << "===========================================\n";
    cout << "Jenis Pemasukan: ";
    cin.ignore();
    getline(cin, p[*jumlahPemasukan].nama);

    if(p[*jumlahPemasukan].nama.empty()) {
        cout << "Nama tidak valid. Catatan tidak disimpan.\n";
        return;
    }
    
    cout << "Nominal: Rp ";
    cin >> p[*jumlahPemasukan].nominal;
    
    if(p[*jumlahPemasukan].nominal <= 0) {
        cout << "Nominal harus lebih dari 0. Catatan tidak disimpan.\n";
        return;
    }
    
    cin.ignore();
    
    bool tanggalValid = false;
    while (!tanggalValid) {
        cout << "\nMasukkan tanggal transaksi:\n";
        cout << "Tanggal (1-31) : ";
        cin >> p[*jumlahPemasukan].tanggal;
        cout << "Bulan (1-12)   : ";
        cin >> p[*jumlahPemasukan].bulan;
        cout << "Tahun          : ";
        cin >> p[*jumlahPemasukan].tahun;
        
        if (validasiTanggal(p[*jumlahPemasukan].tanggal, 
                           p[*jumlahPemasukan].bulan, 
                           p[*jumlahPemasukan].tahun)) {
            tanggalValid = true;
        } else {
            cout << "\n!!! TANGGAL TIDAK VALID !!!" << endl;
            cout << "Silakan masukkan ulang tanggal.\n" << endl;
        }
    }
    
    p[*jumlahPemasukan].id = nomorCatatan;
    
    cout << "\nCatatan berhasil ditambahkan dengan ID: " 
         << p[*jumlahPemasukan].id << endl;
    
    ofstream filePemasukan("data_pemasukan.txt", ios::app);
    if (filePemasukan.is_open()) {
        filePemasukan << p[*jumlahPemasukan].id << ","
                      << p[*jumlahPemasukan].nama << ","
                      << p[*jumlahPemasukan].nominal << ","
                      << p[*jumlahPemasukan].tanggal << "-"
                      << p[*jumlahPemasukan].bulan << "-"
                      << p[*jumlahPemasukan].tahun << endl;
        filePemasukan.close();
        
        cout << "\nCatatan berhasil disimpan ke file!" << endl;
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
    (*jumlahPemasukan)++;
    nomorCatatan++;  
}

void CatatPengeluaran(Pengeluaran *p, int *jumlahPengeluaran){
    cout << "Tambah Catatan Pengeluaran" << endl;
    cout << "===========================================\n";
    cout << "Jenis Pengeluaran: ";
    cin.ignore();
    getline(cin, p[*jumlahPengeluaran].nama);

    if(p[*jumlahPengeluaran].nama.empty()) {
        cout << "Nama tidak valid. Catatan tidak disimpan.\n";
        return;
    }
    
    cout << "Nominal: Rp ";
    cin >> p[*jumlahPengeluaran].nominal;
    
    if(p[*jumlahPengeluaran].nominal <= 0) {
        cout << "Nominal harus lebih dari 0. Catatan tidak disimpan.\n";
        return;
    }
    
    cin.ignore();
    
    bool tanggalValid = false;
    while (!tanggalValid) {
        cout << "\nMasukkan tanggal transaksi:\n";
        cout << "Tanggal (1-31) : ";
        cin >> p[*jumlahPengeluaran].tanggal;
        cout << "Bulan (1-12)   : ";
        cin >> p[*jumlahPengeluaran].bulan;
        cout << "Tahun          : ";
        cin >> p[*jumlahPengeluaran].tahun;
        
        if (validasiTanggal(p[*jumlahPengeluaran].tanggal, 
                           p[*jumlahPengeluaran].bulan, 
                           p[*jumlahPengeluaran].tahun)) {
            tanggalValid = true;
        } else {
            cout << "\n!!! TANGGAL TIDAK VALID !!!" << endl;
            cout << "Silakan masukkan ulang tanggal.\n" << endl;
        }
    }
    
    p[*jumlahPengeluaran].id = nomorCatatan;
    
    cout << "\n✓ Catatan berhasil ditambahkan dengan ID: " 
         << p[*jumlahPengeluaran].id << endl;
    
    ofstream filePengeluaran("data_pengeluaran.txt", ios::app);
    if (filePengeluaran.is_open()) {
        filePengeluaran << p[*jumlahPengeluaran].id << ","
                        << p[*jumlahPengeluaran].nama << ","
                        << p[*jumlahPengeluaran].nominal << ","
                        << p[*jumlahPengeluaran].tanggal << "-"
                        << p[*jumlahPengeluaran].bulan << "-"
                        << p[*jumlahPengeluaran].tahun << endl;
        filePengeluaran.close();
        
        cout << "\nCatatan berhasil disimpan ke file!" << endl;
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
    (*jumlahPengeluaran)++;
    nomorCatatan++;
}

void TampilCatatan(){ 
    if (jumlahPemasukan == 0 && jumlahPengeluaran == 0) {
        kosong();
        return;
    }

    int Menu;
    cout << "Pilih jenis data yang ingin ditampilkan:\n";
    cout << "1. Pemasukan\n";
    cout << "2. Pengeluaran\n";
    cout << "Pilihan: ";
    cin >> Menu;

    switch (Menu){
    case 1: TampilPemasukan(); break;
    case 2: TampilPengeluaran(); break;
    default: cout << "Pilihan tidak valid.\n"; break;
    }   
}

void TampilPemasukan(){
    int menu;
    cout << "\n===== MENU TAMPILAN PEMASUKAN =====\n";
    cout << "1. Berdasarkan Tahun (terurut)\n";
    cout << "2. Berdasarkan Bulan (terurut)\n";
    cout << "3. Berdasarkan Tanggal (terurut lengkap)\n";
    cout << "Pilihan: ";
    cin >> menu;

    switch (menu){
    case 1: TampilPemasukanTahunan(); break;
    case 2: TampilPemasukanBulanan(); break;
    case 3: sortSemuaPemasukan(); break;
    default: cout << "Pilihan tidak valid.\n"; break;
    }
}

void TampilPemasukanTahunan() {
    sortTahunPemasukan();
    
    int tahun;
    cout << "Masukkan tahun pemasukan yang ingin ditampilkan: ";
    cin >> tahun;

    cout << "\n===== DATA PEMASUKAN TAHUN " << tahun << " =====\n";
    bool adaData = false;
    for (int i = 0; i < jumlahPemasukan; i++) {
        if (daftarPemasukan[i].tahun == tahun) {
            cout << "ID: " << daftarPemasukan[i].id 
                 << " | " << daftarPemasukan[i].nama 
                 << " | Rp" << daftarPemasukan[i].nominal
                 << " | " << daftarPemasukan[i].tanggal << "/" 
                 << daftarPemasukan[i].bulan << "/" << daftarPemasukan[i].tahun << endl;
            adaData = true;
        }
    }
    if (!adaData) {
        cout << "Tidak ada catatan pemasukan untuk tahun " << tahun << ".\n";
    }
}

void TampilPemasukanBulanan() {
    sortBulanPemasukan();

    int bulan, tahun;
    cout << "Masukkan bulan (1-12): ";
    cin >> bulan;
    cout << "Masukkan tahun: ";
    cin >> tahun;

    cout << "\n===== DATA PEMASUKAN BULAN " << bulan << " TAHUN " << tahun << " =====\n";
    bool adaData = false;
    for (int i = 0; i < jumlahPemasukan; i++) {
        if (daftarPemasukan[i].bulan == bulan && daftarPemasukan[i].tahun == tahun) {
            cout << "ID: " << daftarPemasukan[i].id 
                 << " | " << daftarPemasukan[i].nama 
                 << " | Rp" << daftarPemasukan[i].nominal
                 << " | " << daftarPemasukan[i].tanggal << "/" 
                 << daftarPemasukan[i].bulan << "/" << daftarPemasukan[i].tahun << endl;
            adaData = true;
        }
    }
    if (!adaData) {
        cout << "Tidak ada catatan pemasukan untuk bulan " << bulan << " tahun " << tahun << ".\n";
    }
}

void TampilPengeluaran() {
    int menu;
    cout << "\n===== MENU TAMPILAN PENGELUARAN =====\n";
    cout << "1. Berdasarkan Tahun (terurut)\n";
    cout << "2. Berdasarkan Bulan (terurut)\n";
    cout << "3. Berdasarkan Tanggal (terurut lengkap)\n";
    cout << "Pilihan: ";
    cin >> menu;

    switch (menu){
    case 1: TampilPengeluaranTahunan(); break;
    case 2: TampilPengeluaranBulanan(); break;
    case 3: sortSemuaPengeluaran(); break;
    default: cout << "Pilihan tidak valid.\n"; break;
    }
}

void TampilPengeluaranTahunan() {
    sortTahunPengeluaran();

    int tahun;
    cout << "Masukkan tahun pengeluaran yang ingin ditampilkan: ";
    cin >> tahun;

    cout << "\n===== DATA PENGELUARAN TAHUN " << tahun << " =====\n";
    bool adaData = false;
    for (int i = 0; i < jumlahPengeluaran; i++) {
        if (daftarPengeluaran[i].tahun == tahun) {
            cout << "ID: " << daftarPengeluaran[i].id 
                 << " | " << daftarPengeluaran[i].nama 
                 << " | Rp" << daftarPengeluaran[i].nominal
                 << " | " << daftarPengeluaran[i].tanggal << "/" 
                 << daftarPengeluaran[i].bulan << "/" << daftarPengeluaran[i].tahun << endl;
            adaData = true;
        }
    }
    if (!adaData) {
        cout << "Tidak ada catatan pengeluaran untuk tahun " << tahun << ".\n";
    }
}

void TampilPengeluaranBulanan() {
    sortBulanPengeluaran();

    int bulan, tahun;
    cout << "Masukkan bulan (1-12): ";
    cin >> bulan;
    cout << "Masukkan tahun: ";
    cin >> tahun;

    cout << "\n===== DATA PENGELUARAN BULAN " << bulan << " TAHUN " << tahun << " =====\n";
    bool adaData = false;
    for (int i = 0; i < jumlahPengeluaran; i++) {
        if (daftarPengeluaran[i].bulan == bulan && daftarPengeluaran[i].tahun == tahun) {
            cout << "ID: " << daftarPengeluaran[i].id 
                 << " | " << daftarPengeluaran[i].nama 
                 << " | Rp" << daftarPengeluaran[i].nominal
                 << " | " << daftarPengeluaran[i].tanggal << "/" 
                 << daftarPengeluaran[i].bulan << "/" << daftarPengeluaran[i].tahun << endl;
            adaData = true;
        }
    }
    if (!adaData) {
        cout << "Tidak ada catatan pengeluaran untuk bulan " << bulan << " tahun " << tahun << ".\n";
    }
}

void riwayat() {
    cout << "===== RIWAYAT AKTIVITAS =====\n";

    int menu;
    cout << "Pilih jenis riwayat yang ingin ditampilkan:\n";
    cout << "1. Tahunan (terurut tahun)\n";
    cout << "2. Bulanan (terurut bulan per tahun)\n";
    cout << "3. Lengkap (terurut tanggal)\n";
    cout << "Pilihan: ";
    cin >> menu;
    
    switch (menu){
    case 1: 
        sortTahunPemasukan();
        sortTahunPengeluaran();
        TampilPemasukanTahunan(); 
        cout << endl; 
        TampilPengeluaranTahunan(); 
        break;
    case 2: 
        sortBulanPemasukan();
        sortBulanPengeluaran();
        TampilPemasukanBulanan(); 
        cout << endl; 
        TampilPengeluaranBulanan(); 
        break;
    case 3:
        sortSemuaPemasukan();
        sortSemuaPengeluaran();
        cout << "\n===== SEMUA DATA PEMASUKAN (TERURUT TANGGAL) =====\n";
        for (int i = 0; i < jumlahPemasukan; i++) {
            cout << "ID: " << daftarPemasukan[i].id 
                 << " | " << daftarPemasukan[i].nama 
                 << " | Rp" << daftarPemasukan[i].nominal
                 << " | " << daftarPemasukan[i].tanggal << "/" 
                 << daftarPemasukan[i].bulan << "/" << daftarPemasukan[i].tahun << endl;
        }
        cout << "\n===== SEMUA DATA PENGELUARAN (TERURUT TANGGAL) =====\n";
        for (int i = 0; i < jumlahPengeluaran; i++) {
            cout << "ID: " << daftarPengeluaran[i].id 
                 << " | " << daftarPengeluaran[i].nama 
                 << " | Rp" << daftarPengeluaran[i].nominal
                 << " | " << daftarPengeluaran[i].tanggal << "/" 
                 << daftarPengeluaran[i].bulan << "/" << daftarPengeluaran[i].tahun << endl;
        }
        break;
    default: 
        cout << "Pilihan tidak valid.\n"; 
        break;
    }

    cout << "\n===== RINGKASAN =====\n";
    cout << "Total Pemasukan  : " << jumlahPemasukan << " catatan\n";
    cout << "Total Pengeluaran: " << jumlahPengeluaran << " catatan\n";
    
    int totalPemasukan = 0;
    for (int i = 0; i < jumlahPemasukan; i++) {
        totalPemasukan += daftarPemasukan[i].nominal;
    }
    
    int totalPengeluaran = 0;
    for (int i = 0; i < jumlahPengeluaran; i++) {
        totalPengeluaran += daftarPengeluaran[i].nominal;
    }
    
    cout << "Total Nominal Pemasukan  : Rp" << totalPemasukan << endl;
    cout << "Total Nominal Pengeluaran: Rp" << totalPengeluaran << endl;
    cout << "Saldo Akhir              : Rp" << (totalPemasukan - totalPengeluaran) << endl;
}

void kosong() {
    cout << "-----------------------------\n";
    cout << "          Kosong             \n";
    cout << "-----------------------------\n";
}

// ================ FUNGSI SORTING LENGKAP ================

// Sorting berdasarkan TAHUN saja (ascending)
void sortTahunPemasukan() {
    for (int i = 0; i < jumlahPemasukan - 1; i++) {
        for (int j = 0; j < jumlahPemasukan - i - 1; j++) {
            if (daftarPemasukan[j].tahun > daftarPemasukan[j + 1].tahun) {
                swap(daftarPemasukan[j], daftarPemasukan[j + 1]);
            }
        }
    }
}

void sortTahunPengeluaran() {
    for (int i = 0; i < jumlahPengeluaran - 1; i++) {
        for (int j = 0; j < jumlahPengeluaran - i - 1; j++) {
            if (daftarPengeluaran[j].tahun > daftarPengeluaran[j + 1].tahun) {
                swap(daftarPengeluaran[j], daftarPengeluaran[j + 1]);
            }
        }
    }
}

// Sorting berdasarkan BULAN per TAHUN (ascending)
void sortBulanPemasukan() {
    for (int i = 0; i < jumlahPemasukan - 1; i++) {
        for (int j = 0; j < jumlahPemasukan - i - 1; j++) {
            if (daftarPemasukan[j].tahun > daftarPemasukan[j + 1].tahun) {
                swap(daftarPemasukan[j], daftarPemasukan[j + 1]);
            }
            else if (daftarPemasukan[j].tahun == daftarPemasukan[j + 1].tahun) {
                if (daftarPemasukan[j].bulan > daftarPemasukan[j + 1].bulan) {
                    swap(daftarPemasukan[j], daftarPemasukan[j + 1]);
                }
            }
        }
    }
}

void sortBulanPengeluaran() {
    for (int i = 0; i < jumlahPengeluaran - 1; i++) {
        for (int j = 0; j < jumlahPengeluaran - i - 1; j++) {
            if (daftarPengeluaran[j].tahun > daftarPengeluaran[j + 1].tahun) {
                swap(daftarPengeluaran[j], daftarPengeluaran[j + 1]);
            }
            else if (daftarPengeluaran[j].tahun == daftarPengeluaran[j + 1].tahun) {
                if (daftarPengeluaran[j].bulan > daftarPengeluaran[j + 1].bulan) {
                    swap(daftarPengeluaran[j], daftarPengeluaran[j + 1]);
                }
            }
        }
    }
}

// Sorting lengkap berdasarkan TANGGAL, BULAN, TAHUN (ascending)
void sortSemuaPemasukan() {
    for (int i = 0; i < jumlahPemasukan - 1; i++) {
        for (int j = 0; j < jumlahPemasukan - i - 1; j++) {
            // Bandingkan tahun dulu
            if (daftarPemasukan[j].tahun > daftarPemasukan[j + 1].tahun) {
                swap(daftarPemasukan[j], daftarPemasukan[j + 1]);
            }
            // Jika tahun sama, bandingkan bulan
            else if (daftarPemasukan[j].tahun == daftarPemasukan[j + 1].tahun) {
                if (daftarPemasukan[j].bulan > daftarPemasukan[j + 1].bulan) {
                    swap(daftarPemasukan[j], daftarPemasukan[j + 1]);
                }
                // Jika bulan sama, bandingkan tanggal
                else if (daftarPemasukan[j].bulan == daftarPemasukan[j + 1].bulan) {
                    if (daftarPemasukan[j].tanggal > daftarPemasukan[j + 1].tanggal) {
                        swap(daftarPemasukan[j], daftarPemasukan[j + 1]);
                    }
                }
            }
        }
    }
    
    // Tampilkan hasil sorting
    cout << "\n===== DATA PEMASUKAN (TERURUT TANGGAL) =====\n";
    for (int i = 0; i < jumlahPemasukan; i++) {
        cout << "ID: " << daftarPemasukan[i].id 
             << " | " << daftarPemasukan[i].nama 
             << " | Rp" << daftarPemasukan[i].nominal
             << " | " << daftarPemasukan[i].tanggal << "/" 
             << daftarPemasukan[i].bulan << "/" << daftarPemasukan[i].tahun << endl;
    }
}

void sortSemuaPengeluaran() {
    for (int i = 0; i < jumlahPengeluaran - 1; i++) {
        for (int j = 0; j < jumlahPengeluaran - i - 1; j++) {
            // Bandingkan tahun dulu
            if (daftarPengeluaran[j].tahun > daftarPengeluaran[j + 1].tahun) {
                swap(daftarPengeluaran[j], daftarPengeluaran[j + 1]);
            }
            // Jika tahun sama, bandingkan bulan
            else if (daftarPengeluaran[j].tahun == daftarPengeluaran[j + 1].tahun) {
                if (daftarPengeluaran[j].bulan > daftarPengeluaran[j + 1].bulan) {
                    swap(daftarPengeluaran[j], daftarPengeluaran[j + 1]);
                }
                // Jika bulan sama, bandingkan tanggal
                else if (daftarPengeluaran[j].bulan == daftarPengeluaran[j + 1].bulan) {
                    if (daftarPengeluaran[j].tanggal > daftarPengeluaran[j + 1].tanggal) {
                        swap(daftarPengeluaran[j], daftarPengeluaran[j + 1]);
                    }
                }
            }
        }
    }
    
    // Tampilkan hasil sorting
    cout << "\n===== DATA PENGELUARAN (TERURUT TANGGAL) =====\n";
    for (int i = 0; i < jumlahPengeluaran; i++) {
        cout << "ID: " << daftarPengeluaran[i].id 
             << " | " << daftarPengeluaran[i].nama 
             << " | Rp" << daftarPengeluaran[i].nominal
             << " | " << daftarPengeluaran[i].tanggal << "/" 
             << daftarPengeluaran[i].bulan << "/" << daftarPengeluaran[i].tahun << endl;
    }
}

// FUNGSI VALIDASI TANGGAL
bool validasiTanggal(int tanggal, int bulan, int tahun) {
    if (bulan < 1 || bulan > 12) {
        return false;
    }
    
    if (tanggal < 1 || tanggal > 31) {
        return false;
    }
    
    if ((bulan == 4 || bulan == 6 || bulan == 9 || bulan == 11) && tanggal > 30) {
        return false;
    }
    
    if (bulan == 2) {
        bool kabisat = (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
        if (kabisat && tanggal > 29) return false;
        if (!kabisat && tanggal > 28) return false;
    }
    
    return true;
}

bool inputTanggal(int &tanggal, int &bulan, int &tahun) {
    string input;
    cout << "Masukkan tanggal (format: DD/MM/YYYY atau DD MM YYYY): ";
    cin >> input;
    
    size_t pos1 = input.find('/');
    if (pos1 != string::npos){
        size_t pos2 = input.find('/', pos1 + 1);
        if (pos2 != string::npos) {
            tanggal = stoi(input.substr(0, pos1));
            bulan = stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
            tahun = stoi(input.substr(pos2 + 1));
            return true;
        }
    }

    cin >> bulan >> tahun;
    tanggal = stoi(input);
    return true;
}
