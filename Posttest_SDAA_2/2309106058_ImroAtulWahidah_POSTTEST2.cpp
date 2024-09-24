#include <iostream>
#include <cstring> 
using namespace std;

const int MAX_MOBIL = 100;
const int MAX_PLAT = 10;
const int MAX_TIPE = 20;

struct Mobil {
    char platNomor[MAX_PLAT];
    char tipeMobil[MAX_TIPE];
    char status[10]; 
};

struct RiwayatCucian {
    char platNomor[MAX_PLAT];
    char tipeMobil[MAX_TIPE];
};

void tambahMobil(Mobil *antrian, int &jumlahMobil, const char *platNomor, const char *tipeMobil) {
    if (jumlahMobil >= MAX_MOBIL) {
        cout << "Antrian penuh, tidak dapat menambahkan mobil baru.\n";
        return;
    }

    strcpy(antrian[jumlahMobil].platNomor, platNomor);
    strcpy(antrian[jumlahMobil].tipeMobil, tipeMobil);
    strcpy(antrian[jumlahMobil].status, "antri");
    jumlahMobil++;

    cout << "Mobil dengan nomor plat " << platNomor << " telah ditambahkan ke antrian.\n";
}

void tambahRiwayat(RiwayatCucian *riwayat, int &jumlahRiwayat, const char *platNomor, const char *tipeMobil) {
    if (jumlahRiwayat >= MAX_MOBIL) {
        cout << "Riwayat penuh, tidak dapat menambahkan data baru.\n";
        return;
    }

    strcpy(riwayat[jumlahRiwayat].platNomor, platNomor);
    strcpy(riwayat[jumlahRiwayat].tipeMobil, tipeMobil);
    jumlahRiwayat++;
}

void hapusMobil(Mobil *antrian, int &jumlahMobil, RiwayatCucian *riwayat, int &jumlahRiwayat, bool isFinished) {
    if (jumlahMobil > 0) {
        if (isFinished) {
            tambahRiwayat(riwayat, jumlahRiwayat, antrian[0].platNomor, antrian[0].tipeMobil);
        }

        for (int i = 0; i < jumlahMobil - 1; ++i) {
            antrian[i] = antrian[i + 1]; 
        }
        jumlahMobil--;
    } else {
        cout << "Antrian kosong.\n";
    }
}

void tampilkanAntrian(Mobil *antrian, int jumlahMobil) {
    if (jumlahMobil == 0) {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "Antrian saat ini:\n";
    for (int i = 0; i < jumlahMobil; ++i) {
        cout << (i + 1) << ". Plat: " << antrian[i].platNomor
             << ", Jenis: " << antrian[i].tipeMobil
             << ", Status: " << antrian[i].status << "\n";
    }
}

void tampilkanRiwayat(RiwayatCucian *riwayat, int jumlahRiwayat) {
    if (jumlahRiwayat == 0) {
        cout << "Riwayat cucian kosong.\n";
        return;
    }

    cout << "Riwayat cucian:\n";
    for (int i = 0; i < jumlahRiwayat; ++i) {
        cout << (i + 1) << ". Plat: " << riwayat[i].platNomor
             << ", Jenis: " << riwayat[i].tipeMobil << "\n";
    }
}

int main() {
    Mobil antrian[MAX_MOBIL];
    RiwayatCucian riwayat[MAX_MOBIL];
    int jumlahMobil = 0, jumlahRiwayat = 0;
    int choice;
    char platNomor[MAX_PLAT], tipeMobil[MAX_TIPE];

    do {
        cout << "\n===== Sistem Antrian Layanan Mobilwash =====\n";
        cout << "1. Tambah mobil ke antrian\n";
        cout << "2. Layani mobil (mulai mencuci)\n";
        cout << "3. Selesaikan cucian mobil\n";
        cout << "4. Batalkan cucian mobil\n";
        cout << "5. Tampilkan antrian\n";
        cout << "6. Tampilkan riwayat cucian\n";
        cout << "7. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan nomor plat mobil: ";
                cin >> platNomor;
                cout << "Masukkan jenis mobil: ";
                cin >> tipeMobil;
                tambahMobil(antrian, jumlahMobil, platNomor, tipeMobil);
                break;
            case 2:
                if (jumlahMobil > 0) {
                    cout << "Mulai mencuci mobil dengan plat " << antrian[0].platNomor << endl;
                    strcpy(antrian[0].status, "dicuci");
                } else {
                    cout << "Antrian kosong.\n";
                }
                break;
            case 3:
                if (jumlahMobil > 0 && strcmp(antrian[0].status, "dicuci") == 0) {
                    hapusMobil(antrian, jumlahMobil, riwayat, jumlahRiwayat, true);
                    cout << "Cucian mobil selesai dan ditambahkan ke riwayat.\n";
                } else {
                    cout << "Tidak ada mobil yang sedang dicuci.\n";
                }
                break;
            case 4:
                if (jumlahMobil > 0) {
                    hapusMobil(antrian, jumlahMobil, riwayat, jumlahRiwayat, false);
                    cout << "Cucian mobil dibatalkan dan dihapus dari antrian.\n";
                } else {
                    cout << "Antrian kosong.\n";
                }
                break;
            case 5:
                tampilkanAntrian(antrian, jumlahMobil);
                break;
            case 6:
                tampilkanRiwayat(riwayat, jumlahRiwayat);
                break;
            case 7:
                cout << "Terima kasih telah menggunakan sistem kami.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 7);

    return 0;
}
