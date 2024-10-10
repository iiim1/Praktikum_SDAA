#include <iostream>
#include <iomanip>
using namespace std;

struct Pelanggan {
    string nama;
    string platMobil;
    string jenisLayanan;
    double harga;
};

struct Node {
    Pelanggan data;
    Node *next;
};

Node *antrianDepan = nullptr;
Node *antrianBelakang = nullptr;
Node *riwayatAtas = nullptr;

Node *createNode() {
    Node *newNode = new Node();
    cout << "Masukkan Nama Pelanggan: ";
    cin.ignore();
    getline(cin, newNode->data.nama);
    cout << "Masukkan Plat Mobil: ";
    getline(cin, newNode->data.platMobil);
    cout << "Masukkan Jenis Layanan: ";
    getline(cin, newNode->data.jenisLayanan);
    cout << "Masukkan Harga Layanan: Rp";
    cin >> newNode->data.harga;
    newNode->next = nullptr;
    return newNode;
}

void enqueue() {
    Node *newNode = createNode();
    if (antrianBelakang == nullptr) {
        antrianDepan = antrianBelakang = newNode;
    } else {
        antrianBelakang->next = newNode;
        antrianBelakang = newNode;
    }
    cout << "Pelanggan " << newNode->data.nama << " ditambahkan ke antrian." << endl;
}

void dequeue() {
    if (antrianDepan == nullptr) {
        cout << "Antrian kosong." << endl;
        return;
    }
    Node *temp = antrianDepan;
    cout << "Melayani pelanggan: " << temp->data.nama << endl;
    antrianDepan = antrianDepan->next;
    if (antrianDepan == nullptr) {
        antrianBelakang = nullptr;
    }
    temp->next = riwayatAtas;
    riwayatAtas = temp;
}

void displayQueue() {
    if (antrianDepan == nullptr) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "Antrian Pelanggan:" << endl;
    Node *temp = antrianDepan;
    int nomor = 1;
    while (temp != nullptr) {
        cout << nomor++ << ". Nama: " << temp->data.nama
             << ", Plat: " << temp->data.platMobil
             << ", Layanan: " << temp->data.jenisLayanan
             << ", Harga: Rp" << fixed << setprecision(2) << temp->data.harga << endl;
        temp = temp->next;
    }
}

void displayStack() {
    if (riwayatAtas == nullptr) {
        cout << "Belum ada riwayat transaksi." << endl;
        return;
    }
    cout << "Riwayat Transaksi (dari yang terbaru):" << endl;
    Node *temp = riwayatAtas;
    int nomor = 1;
    while (temp != nullptr) {
        cout << nomor++ << ". Nama: " << temp->data.nama
             << ", Plat: " << temp->data.platMobil
             << ", Layanan: " << temp->data.jenisLayanan
             << ", Harga: Rp" << fixed << setprecision(2) << temp->data.harga << endl;
        temp = temp->next;
    }
}

int main() {
    int pilihan;
    do{
        cout << "\nMenu Sistem Carwash:" << endl;
        cout << "1. Tambah Pelanggan ke Antrian (Enqueue)" << endl;
        cout << "2. Layani Pelanggan (Dequeue)" << endl;
        cout << "3. Tampilkan Antrian" << endl;
        cout << "4. Tampilkan Riwayat Transaksi" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            displayQueue();
            break;
        case 4:
            displayStack();
            break;
        case 5:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
    } while (pilihan != 5);

    return 0;
}