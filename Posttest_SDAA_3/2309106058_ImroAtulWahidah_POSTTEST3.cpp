#include <iostream>
#include <cstring>
using namespace std;

struct Mobil {
    char platNomor[10];
    char tipeMobil[20];
    char status[10];
    Mobil *next;
};

struct RiwayatCucian {
    char platNomor[10]; 
    char tipeMobil[20];   
    RiwayatCucian *next;  
};

void tambahMobil(Mobil *&head, const char *platNomor, const char *tipeMobil) {
    Mobil *newMobil = new Mobil;
    strcpy(newMobil->platNomor, platNomor); 
    strcpy(newMobil->tipeMobil, tipeMobil);     
    strcpy(newMobil->status, "antri");     
    newMobil->next = nullptr;               

    if (head == nullptr) {
        head = newMobil; 
    } else {
        Mobil *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next; 
        }
        temp->next = newMobil; 
    }
    cout << "Mobil dengan nomor plat " << platNomor << " telah ditambahkan ke antrian.\n";
}

void tambahRiwayat(RiwayatCucian *&head, const char *platNomor, const char *tipeMobil) {
    RiwayatCucian *newEntry = new RiwayatCucian;
    strcpy(newEntry->platNomor, platNomor);
    strcpy(newEntry->tipeMobil, tipeMobil);
    newEntry->next = nullptr;

    if (head == nullptr)
    {
        head = newEntry;
    }
    else
    {
        RiwayatCucian *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newEntry;
    }
}

void hapusMobil(Mobil *&head, RiwayatCucian *&historyHead, bool isFinished) {
    if (head != nullptr) {
        Mobil *temp = head;
        head = head->next; 
        if (isFinished) {
            tambahRiwayat(historyHead, temp->platNomor, temp->tipeMobil); 
        }
        delete temp; 
    }
}

void tampilkanAntrian(Mobil *head) {
    if (head == nullptr) {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "Antrian saat ini:\n";
    int position = 1;
    Mobil *current = head;
    while (current != nullptr) {
        cout << position << ". Plat: " << current->platNomor
             << ", Jenis: " << current->tipeMobil
             << ", Status: " << current->status << "\n";
        current = current->next; 
        position++;
    }
}

void tampilkanRiwayat(RiwayatCucian *head) {
    if (head == nullptr) {
        cout << "Riwayat cucian kosong.\n";
        return;
    }

    cout << "Riwayat cucian:\n";
    int position = 1;
    RiwayatCucian *current = head;
    while (current != nullptr) {
        cout << position << ". Plat: " << current->platNomor
             << ", Jenis: " << current->tipeMobil << "\n";
        current = current->next; 
        position++;
    }
}

int main() {
    Mobil *antriHead = nullptr;
    RiwayatCucian *historyHead = nullptr;
    int choice;
    char platNomor[10], tipeMobil[20];

    do {
        cout << "\n===== Sistem Antrian Layanan Carwash =====\n";
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
                tambahMobil(antriHead, platNomor, tipeMobil);
                break;
            case 2:
                if (antriHead != nullptr) {
                    cout << "Mulai mencuci mobil dengan plat " << antriHead->platNomor << endl;
                    strcpy(antriHead->status, "dicuci");
                } else {
                    cout << "Antrian kosong.\n";
                }
                break;
            case 3:
                if (antriHead != nullptr && strcmp(antriHead->status, "dicuci") == 0) {
                    hapusMobil(antriHead, historyHead, true); 
                    cout << "Cucian mobil selesai dan ditambahkan ke riwayat.\n";
                }
                else {
                    cout << "Tidak ada mobil yang sedang dicuci.\n";
                }
                break;
            case 4:
                if (antriHead != nullptr) {
                    hapusMobil(antriHead, historyHead, false);
                    cout << "Cucian mobil dibatalkan dan dihapus dari antrian.\n";
                } else {
                    cout << "Antrian kosong.\n";
                }
                break;
            case 5:
                tampilkanAntrian(antriHead); 
                break;
            case 6:
                tampilkanRiwayat(historyHead); 
                break;
            case 7:
                cout << "Terima kasih telah menggunakan sistem kami.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 7);

    while (antriHead != nullptr) {
        hapusMobil(antriHead, historyHead, false);
    }
    
    while (historyHead != nullptr) {
        RiwayatCucian *temp = historyHead;
        historyHead = historyHead->next;
        delete temp;
    }

    return 0;
}