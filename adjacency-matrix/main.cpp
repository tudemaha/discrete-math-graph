#include <iostream>

using namespace std;

int main() {
    int nodes;

    cout << "===== PROGRAM MATRIKS KETETANGGAAN =====" << endl;

    cout << "Banyak node: ";
    cin >> nodes;

    int matrix[nodes][nodes];

    cout << endl << "Masukkan 1 jika node terhubung, 0 jika tidak terhubung" << endl;
    for(int row = 0; row < nodes; row++) {
        for(int column = 0; column < nodes; column++) {
            cout << "Baris " << row + 1 << ", Kolom " << column + 1 << ": ";
            cin >> matrix[row][column];
        }
    }

    cout << endl << "Matriks ketetanggaan:" << endl;
    for(int row = 0; row < nodes; row++) {
        for(int column = 0; column < nodes; column++) {
            cout << matrix[row][column] << " ";
        }
        cout << endl;
    }

    return 0;
}