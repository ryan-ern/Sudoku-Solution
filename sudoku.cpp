/*
Ryan Ernanda 120140154
Muhammad Hadi Arsa 120140150
*/
#include <iostream>
#include <fstream>
#define N 9 // sudoku 9x9
using namespace std;
int grid[N][N];// sudoku grid

bool AdadiCol(int col, int num){ //periksa apakah num ada dalam col atau tidak
   for (int row = 0; row < N; row++)// periksa setiap baris
      if (grid[row][col] == num)// jika num ada dalam baris
         return true;
   return false;
}
bool AdadiRow(int row, int num){ //periksa apakah num ada di baris atau tidak
   for (int col = 0; col < N; col++)// periksa setiap kolom
      if (grid[row][col] == num)// jika num ada di kolom
         return true;
   return false;
}
bool AdadiBox(int mulairow, int mulaicol, int num){//periksa apakah num ada di kotak 3x3 atau tidak
   for (int row = 0; row < 3; row++)// periksa setiap baris
      for (int col = 0; col < 3; col++)// periksa setiap kolom
         if (grid[row+mulairow][col+mulaicol] == num)// jika num ada di kotak
            return true;
   return false;
}
void SudokuGrid(){ //cetak isi sudoku setelah dipecahkan
   for (int row = 0; row < N; row++){// periksa setiap baris
      for (int col = 0; col < N; col++){// periksa setiap kolom
         if(col == 3 || col == 6)// jika kolom 3 atau 6
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){// jika baris 2 atau 5
         cout << endl;
         for(int i = 1; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
}
bool TemukanTempatKosong(int &row, int &col){ //dapatkan lokasi kosong dan perbarui baris dan kolom
   for (row = 0; row < N; row++)// periksa setiap baris
      for (col = 0; col < N; col++)// periksa setiap kolom
         if (grid[row][col] == 0) //ditandai 0 dengan nilai kosong
            return true;
   return false;
}
bool TempatyangBenar(int row, int col, int num){//periksa apakah num dapat dimasukkan ke sudoku
   return !AdadiRow(row, num) && !AdadiCol(col, num) && !AdadiBox(row - row%3, col - col%3, num);// jika num tidak ada di baris, kolom, dan kotak 3x3
}
bool SudokuSelesai(){//sudoku diselesaikan dengan cara mencari lokasi kosong dan mencari nilai yang valid untuk lokasi kosong
   int row, col;
   if (!TemukanTempatKosong(row, col))// jika tidak ada lokasi kosong
      return true; //ketika semua tempat terisi
   for (int num = 1; num <= 9; num++){ //nomor yang valid adalah 1 - 9
      if (TempatyangBenar(row, col, num)){ //periksa validasi, jika ya, masukkan nomornya ke dalam kotak
         grid[row][col] = num;// masukkan nomor ke dalam kotak
         if (SudokuSelesai()) //secara rekursif pergi ke kotak lain di grid
            return true;
         grid[row][col] = 0; //beralih ke kotak yang tidak ditetapkan ketika kondisinya tidak terpenuhi
      }
   }
   return false;
}
int main(){
   grid[N][N];// sudoku 9x9
   fstream inputfile;// file input
	fstream outputfile;// file output
	cout << "Masukkan Nama File Sudoku: ";
	string fileName, outputFileName;// nama file input dan output
	cin >> fileName;// masukkan nama file input
	inputfile.open(fileName, ios::in);// membuka file input

	cout << "Masukan Nama File Untuk Menyimpan Hasil Sudoku: ";
	cin >> outputFileName;// masukkan nama file output
	outputfile.open(outputFileName, ios::out);// membuka file output
	
	if (!inputfile.is_open() || !outputfile.is_open())// jika file tidak dapat dibuka
    {
        cout << "Error membuka file";
        return 0;
    }
    cout<< "\nSudoku Berhasil Diselesaikan" << endl;
    for (int row = 0; row < N; row++)// periksa setiap baris
        for (int col = 0; col < N; col++)// periksa setiap kolom
            inputfile >> grid[row][col];// masukkan isi file ke dalam grid
    if (SudokuSelesai())// jika sudoku dapat diselesaikan
        SudokuGrid();
    else
        cout << "Tidak ada solusi";// jika tidak dapat diselesaikan
    inputfile.close();

    outputfile << "Hasil sudoku yang diselesaikan: " << endl;// menuliskan isi sudoku ke file output
      for (int row = 0; row < N; row++){// periksa setiap baris
         for (int col = 0; col < N; col++){// periksa setiap kolom
               if(col == 3 || col == 6)// jika kolom 3 atau 6
                  outputfile << " | ";
               outputfile << grid[row][col] <<" ";// menuliskan isi sudoku ke file output
         }
         if(row == 2 || row == 5){// jika baris 2 atau 5
               outputfile << endl;
               for(int i = 1; i<N; i++)// menuliskan garis bawah
                  outputfile << "---";
         }
         outputfile << endl;
      }
}