// 2309106058
// ImroAtulWahidah
// program rekursif segitiga pascal siku - siku 3 tingkat

#include <iostream>
using namespace std;

void printPascal(int n, int baris, int kolom, int C) {
    if (baris == n)
        return;
    if (kolom > baris) {
        cout << endl;
        printPascal(n, baris + 1, 0, 1);
    } else {
        cout << C << " ";
        C = C * (baris - kolom) / (kolom + 1);
        printPascal(n, baris, kolom + 1, C);
    }
}

int main() {
    int n = 3;
    int baris = 0;
    int kolom = 0;
    int C = 1;
    printPascal(n, baris, kolom, C);
    return 0;
}