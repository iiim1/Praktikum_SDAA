#include <iostream>
#include <iomanip>
using namespace std;

struct Pelanggan
{
    string nama;
    string platMobil;
    string jenisLayanan;
    double harga;
};

struct Node
{
    Pelanggan data;
    Node *next;
};

Node *antrianDepan = nullptr;
Node *antrianBelakang = nullptr;
Node *riwayatAtas = nullptr;

Node *SortedMerge(Node *a, Node *b)
{
    Node *result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->data.harga <= b->data.harga)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return result;
}

void FrontBackSplit(Node *source, Node **frontRef, Node **backRef)
{
    Node *fast;
    Node *slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}
void MergeSort(Node **headRef)
{
    Node *head = *headRef;
    Node *a;
    Node *b;

    if (head == nullptr || head->next == nullptr)
        return;

    FrontBackSplit(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *headRef = SortedMerge(a, b);
}

int length(Node *head)
{
    int panjang = 0;
    while (head != nullptr)
    {
        head = head->next;
        panjang++;
    }
    return panjang;
}
void linkedList2Array(Node *head, Pelanggan arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = head->data;
        head = head->next;
    }
}

void array2LinkedList(Node *head, Pelanggan arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        head->data = arr[i];
        head = head->next;
    }
}

void shellSort(Pelanggan arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            Pelanggan temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].harga < temp.harga; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void sortAndDisplayQueue(bool ascending)
{
    if (antrianDepan == nullptr)
    {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "Antrian Pelanggan (diurutkan berdasarkan harga " << (ascending ? "ascending" : "descending") << "):" << endl;

    if (ascending)
    {
        Node *sortedQueue = antrianDepan;
        MergeSort(&sortedQueue);
        int nomor = 1;
        while (sortedQueue != nullptr)
        {
            cout << nomor++ << ". Nama: " << sortedQueue->data.nama
                 << ", Plat: " << sortedQueue->data.platMobil
                 << ", Layanan: " << sortedQueue->data.jenisLayanan
                 << ", Harga: Rp" << fixed << setprecision(2) << sortedQueue->data.harga << endl;
            sortedQueue = sortedQueue->next;
        }
    }
    else
    {
        int n = length(antrianDepan);
        Pelanggan *arr = new Pelanggan[n];
        linkedList2Array(antrianDepan, arr, n);
        shellSort(arr, n);
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << ". Nama: " << arr[i].nama
                 << ", Plat: " << arr[i].platMobil
                 << ", Layanan: " << arr[i].jenisLayanan
                 << ", Harga: Rp" << fixed << setprecision(2) << arr[i].harga << endl;
        }
        delete[] arr;
    }
}

Node *createNode()
{
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

void enqueue()
{
    Node *newNode = createNode();
    if (antrianBelakang == nullptr)
    {
        antrianDepan = antrianBelakang = newNode;
    }
    else
    {
        antrianBelakang->next = newNode;
        antrianBelakang = newNode;
    }
    cout << "Pelanggan " << newNode->data.nama << " ditambahkan ke antrian." << endl;
}

void dequeue()
{
    if (antrianDepan == nullptr)
    {
        cout << "Antrian kosong." << endl;
        return;
    }
    Node *temp = antrianDepan;
    cout << "Melayani pelanggan: " << temp->data.nama << endl;
    antrianDepan = antrianDepan->next;
    if (antrianDepan == nullptr)
    {
        antrianBelakang = nullptr;
    }
    temp->next = riwayatAtas;
    riwayatAtas = temp;
}

void displayQueue()
{
    if (antrianDepan == nullptr)
    {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "Antrian Pelanggan:" << endl;
    Node *temp = antrianDepan;
    int nomor = 1;
    while (temp != nullptr)
    {
        cout << nomor++ << ". Nama: " << temp->data.nama
             << ", Plat: " << temp->data.platMobil
             << ", Layanan: " << temp->data.jenisLayanan
             << ", Harga: Rp" << fixed << setprecision(2) << temp->data.harga << endl;
        temp = temp->next;
    }
}

void displayStack()
{
    if (riwayatAtas == nullptr)
    {
        cout << "Belum ada riwayat transaksi." << endl;
        return;
    }
    cout << "Riwayat Transaksi (dari yang terbaru):" << endl;
    Node *temp = riwayatAtas;
    int nomor = 1;
    while (temp != nullptr)
    {
        cout << nomor++ << ". Nama: " << temp->data.nama
             << ", Plat: " << temp->data.platMobil
             << ", Layanan: " << temp->data.jenisLayanan
             << ", Harga: Rp" << fixed << setprecision(2) << temp->data.harga << endl;
        temp = temp->next;
    }
}

int main()
{
    int pilihan;
    do
    {
        cout << "\nMenu Sistem Carwash:" << endl;
        cout << "1. Tambah Pelanggan ke Antrian (Enqueue)" << endl;
        cout << "2. Layani Pelanggan (Dequeue)" << endl;
        cout << "3. Tampilkan Antrian" << endl;
        cout << "4. Tampilkan Riwayat Transaksi" << endl;
        cout << "5. Tampilkan Antrian Terurut (Berdasarkan Harga Ascending)" << endl;
        cout << "6. Tampilkan Antrian Terurut (Berdasarkan Harga Descending)" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih opsi (1-7): ";
        cin >> pilihan;

        switch (pilihan)
        {
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
            sortAndDisplayQueue(true);
            break;
        case 6:
            sortAndDisplayQueue(false);
            break;
        case 7:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
    } while (pilihan != 7);
    return 0;
}