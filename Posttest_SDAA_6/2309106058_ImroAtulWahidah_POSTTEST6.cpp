#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
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

void add(Node **head, string nama, string platMobil, string jenisLayanan, double harga)
{
    Node *newNode = new Node();
    newNode->data.nama = nama;
    newNode->data.platMobil = platMobil;
    newNode->data.jenisLayanan = jenisLayanan;
    newNode->data.harga = harga;

    if (*head == nullptr)
    {
        newNode->next = nullptr;
        *head = newNode;
        antrianBelakang = newNode;
    }
    else
    {
        newNode->next = *head;
        *head = newNode;
    }
}

int length(Node *head)
{
    int count = 0;
    Node *temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int min(int x, int y)
{
    return (x <= y) ? x : y;
}

void displayCustomerData(Node *node)
{
    cout << "Nama: " << node->data.nama
         << ", Plat: " << node->data.platMobil
         << ", Layanan: " << node->data.jenisLayanan
         << ", Harga: Rp" << fixed << setprecision(2) << node->data.harga << endl;
}

// Fibonacci Search untuk mencari berdasarkan harga
void fibonacciSearch(Node *head, double x, int n)
{
    bool found = false;
    cout << "\nHasil pencarian harga 'Rp" << fixed << setprecision(2) << x << "':" << endl;

    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    Node *current = head;

    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);
        Node *temp = head;
        for (int j = 0; j <= i; j++)
        {
            if (temp != nullptr)
                temp = temp->next;
        }

        if (temp == nullptr || temp->data.harga < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->data.harga > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
        {
            displayCustomerData(temp);
            found = true;
            break;
        }
    }

    // Check remaining elements
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.harga == x)
        {
            displayCustomerData(temp);
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "Harga tidak ditemukan." << endl;
}

// Jump Search untuk mencari berdasarkan harga
double getNodeHarga(Node *head, int idx)
{
    for (int i = 0; i < idx; i++)
    {
        head = head->next;
    }
    return head->data.harga;
}

void jumpSearch(Node *head, double x, int n)
{
    bool found = false;
    cout << "\nHasil pencarian harga 'Rp" << fixed << setprecision(2) << x << "':" << endl;

    int step = sqrt(n);
    Node *current = head;
    Node *prev = nullptr;

    // Finding the block where element may be present
    while (current != nullptr && getNodeHarga(head, min(step, n) - 1) < x)
    {
        prev = current;
        for (int i = 0; i < step && current != nullptr; i++)
            current = current->next;
        if (current == nullptr)
            break;
    }

    // Linear search in the identified block
    if (prev != nullptr)
    {
        Node *temp = prev;
        while (temp != current)
        {
            if (temp->data.harga == x)
            {
                displayCustomerData(temp);
                found = true;
            }
            temp = temp->next;
        }
    }

    // Check remaining elements if any
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.harga == x)
        {
            displayCustomerData(temp);
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "Harga tidak ditemukan." << endl;
}

// Boyer-Moore Search untuk mencari nama
const int NO_OF_CHARS = 256;

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
        badChar[i] = -1;

    for (int i = 0; i < size; i++)
        badChar[(int)str[i]] = i;
}

void searchNama(Node *head, string pat)
{
    bool found = false;
    cout << "\nHasil pencarian nama '" << pat << "':" << endl;

    transform(pat.begin(), pat.end(), pat.begin(), ::tolower);

    while (head != nullptr)
    {
        string txt = head->data.nama;
        transform(txt.begin(), txt.end(), txt.begin(), ::tolower);

        int m = pat.size();
        int n = txt.size();

        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);

        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pat[j] == txt[s + j])
                j--;

            if (j < 0)
            {
                cout << "Nama: " << head->data.nama
                     << ", Plat: " << head->data.platMobil
                     << ", Layanan: " << head->data.jenisLayanan
                     << ", Harga: Rp" << fixed << setprecision(2) << head->data.harga << endl;
                found = true;
                break;
            }
            else
                s += max(1, j - badChar[txt[s + j]]);
        }
        head = head->next;
    }
    if (!found)
        cout << "Nama tidak ditemukan." << endl;
}

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

    int n = length(antrianDepan);
    Pelanggan *arr = new Pelanggan[n];
    linkedList2Array(antrianDepan, arr, n);

    if (ascending)
    {
        sort(arr, arr + n, [](const Pelanggan &a, const Pelanggan &b)
             { return a.harga < b.harga; });
    }
    else
    {
        shellSort(arr, n);
    }

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". Nama: " << arr[i].nama
             << ", Plat: " << arr[i].platMobil
             << ", Layanan: " << arr[i].jenisLayanan
             << ", Harga: Rp" << fixed << setprecision(2) << arr[i].harga << endl;
    }

    delete[] arr;
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

void searchMenu()
{
    int pilihan;
    double hargaCari;
    string namaCari;

    cout << "\nMenu Pencarian Antrian:" << endl;
    cout << "1. Cari berdasarkan harga (Fibonacci Search)" << endl;
    cout << "2. Cari berdasarkan harga (Jump Search)" << endl;
    cout << "3. Cari berdasarkan nama (Boyer-Moore)" << endl;
    cout << "4. Kembali ke menu utama" << endl;
    cout << "Pilih opsi (1-4): ";
    cin >> pilihan;

    switch (pilihan)
    {
    case 1:
        if (antrianDepan == nullptr)
        {
            cout << "Antrian kosong." << endl;
            return;
        }
        cout << "Masukkan harga yang dicari: Rp";
        cin >> hargaCari;
        fibonacciSearch(antrianDepan, hargaCari, length(antrianDepan));
        break;
    case 2:
        if (antrianDepan == nullptr)
        {
            cout << "Antrian kosong." << endl;
            return;
        }
        cout << "Masukkan harga yang dicari: Rp";
        cin >> hargaCari;
        jumpSearch(antrianDepan, hargaCari, length(antrianDepan));
        break;
    case 3:
        if (antrianDepan == nullptr)
        {
            cout << "Antrian kosong." << endl;
            return;
        }
        cout << "Masukkan nama yang dicari: ";
        cin.ignore();
        getline(cin, namaCari);
        searchNama(antrianDepan, namaCari);
        break;
    case 4:
        return;
    default:
        cout << "Pilihan tidak valid." << endl;
    }
}

int main()
{
    Node *head = nullptr;

    add(&head, "Nayla Zean", "KT 1234 CD", "Cuci Mobil Premium", 100000);
    add(&head, "Via Rama", "KT 5678 EF", "Cuci Mobil Reguler", 50000);
    add(&head, "Putri Jasmine", "KT 9012 GH", "Cuci Mobil Express", 75000);
    add(&head, "iim", "KT 3456 IJ", "Cuci Mobil Premium", 100000);
    add(&head, "Bobi boba", "KT 7890 KL", "Cuci Mobil Reguler", 50000);

    antrianDepan = head;
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
        cout << "7. Menu Pencarian Antrian" << endl;
        cout << "8. Keluar" << endl;
        cout << "Pilih opsi (1-8): ";
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
            searchMenu();
            break;
        case 8:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
    } while (pilihan != 8);
    return 0;
}