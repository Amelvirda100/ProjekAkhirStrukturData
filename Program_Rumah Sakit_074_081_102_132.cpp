#include <iostream>
#include <cstring>
using namespace std;

const int table_size = 100; // Ukuran tabel hash
const int max_deleted = 100; // Jumlah maksimal riwayat pasien yang dihapus

// Struktur data untuk informasi pasien
struct Patient {
    string name;
    int patientID;
    string roomCategory;
    int duration;
    Patient* next;

    Patient(const string& n, int id, const string& category, int d)
        : name(n), patientID(id), roomCategory(category), duration(d), next(nullptr) {}
};

// Struktur data untuk menyimpan data pasien yang dihapus
struct DeletedPatient {
    string name;
    int patientID;
    string roomCategory;
    int duration;
};

//menghindari overflow
int isPrime(int n) {
    if (n <= 1) return 0; // 0 dan 1 bukan bilangan prima
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // Bukan bilangan prima jika bisa dibagi
    }
    return 1; // Jika tidak ada pembagi, itu adalah bilangan prima
}

int findNextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

// Fungsi hash sederhana untuk ID pasien
int hashFunction(int patientID, int table_size) {
    // Pastikan bahwa table_size adalah bilangan prima
    table_size = findNextPrime(table_size);
    
    return patientID % table_size;
}

// Fungsi untuk mengecek apakah tabel hash kosong atau tidak
bool isHashTableEmpty(Patient* table[], int table_size) {
    for (int i = 0; i < table_size; ++i) {
        if (table[i] != nullptr) {
            return false;  // Terdapat data pada indeks i
        }
    }
    return true; // Semua elemen tabel bernilai nullptr, tabel kosong
}

bool isNumberUsed(int usedNumbers[], int size, int number) {
    for (int i = 0; i < size; ++i) {
        if (usedNumbers[i] == number) {
            return true; // Angka sudah digunakan
        }
    }
    return false; // Angka belum digunakan
}

int generateUniqueRandomNumber(int usedNumbers[], int size, int range) {
    int randomNumber;
    do {
        // Menghasilkan angka acak antara 1 dan range
        randomNumber = rand() % range + 1;
    } while (isNumberUsed(usedNumbers, size, randomNumber));

    return randomNumber;
}

// Fungsi untuk memeriksa apakah string dimulai dengan huruf besar
bool startsWithUppercase(const string& str) {
    return !str.empty() && isupper(str[0]);
}

// Fungsi untuk menambahkan data pasien ke dalam tabel hash
void addPatient(Patient* table[], const string& name, int patientID, const string& roomCategory, int duration) {
    int index = hashFunction(patientID, table_size);
    Patient* newPatient = new Patient(name, patientID, roomCategory, duration);
    newPatient->next = table[index];
    table[index] = newPatient;
}

// Fungsi untuk menampilkan semua data pasien
void displayPatientHash(Patient* table[]) {
      for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
                cout << "  Nama            : " << current->name << endl;
                cout << "  ID Pasien       : " << current->patientID << endl;
                cout << "  Golongan Ruang  : " << current->roomCategory << endl;
                cout << "  Lama Rawat Inap : " << current->duration << " hari" << endl;
				
                // Menghitung total biaya
                int harga;
                if (current->roomCategory == "A") {
                    harga = 150000;
                } else if (current->roomCategory == "B") {
                    harga = 200000;
                } else if (current->roomCategory == "C") {
                    harga = 250000;
                } else if (current->roomCategory == "D") {
                    harga = 300000;
                } else if (current->roomCategory == "E") {
                    harga = 350000;
                } else {
                    harga = 0; // Golongan ruang tidak valid
                }

                int totalBiaya = harga * current->duration;
                cout << "  Total Biaya     : " << totalBiaya << endl;

                cout << endl << " ===================================\n\n";
             current = current->next;
            }
        }
    }
   
// Fungsi untuk menampilkan data pasien berdasarkan nama pasien
void displayPatientByName(Patient* table[], const string& name) {
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
            if (current->name == name) {
                cout << " +" << string (34, '=') << "+" << endl;             
                cout << " |            DATA PASIEN           |\n";
                cout << " +" << string (34, '=') << "+" << endl;
                cout << "  Nama            : " << current->name << endl;
                cout << "  ID Pasien       : " << current->patientID << endl;
                cout << "  Golongan Ruang  : " << current->roomCategory << endl;
                cout << "  Lama Rawat Inap : " << current->duration << " hari" << endl;

                // Menghitung total biaya
                int harga;
                if (current->roomCategory == "A") {
                    harga = 150000;
                } else if (current->roomCategory == "B") {
                    harga = 200000;
                } else if (current->roomCategory == "C") {
                    harga = 250000;
                } else if (current->roomCategory == "D") {
                    harga = 300000;
                } else if (current->roomCategory == "E") {
                    harga = 350000;
                } else {
                    harga = 0; // Golongan ruang tidak valid
                }

                int totalBiaya = harga * current->duration;
                cout << "  Total Biaya     : " << totalBiaya << endl;

                cout << " +=================================+\n";
                return; // Keluar dari fungsi setelah menemukan pasien
            }
            current = current->next;
        }
    }
    cout << "  Pasien dengan nama" << endl << "  " <<  name << " tidak ditemukan.\n";
    cout << " ====================================\n";
    }

void displayPatientById(Patient* table[], int id) {
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
            if (current->patientID == id) {
                cout << " +" << string (34, '=') << "+" << endl;             
                cout << " |            DATA PASIEN           |\n";
                cout << " +" << string (34, '=') << "+" << endl;
                cout << "  Nama            : " << current->name << endl;
                cout << "  ID Pasien       : " << current->patientID << endl;
                cout << "  Golongan Ruang  : " << current->roomCategory << endl;
                cout << "  Lama Rawat Inap : " << current->duration << " hari" << endl;

                // Menghitung total biaya
                int harga;
                if (current->roomCategory == "A") {
                    harga = 150000;
                } else if (current->roomCategory == "B") {
                    harga = 200000;
                } else if (current->roomCategory == "C") {
                    harga = 250000;
                } else if (current->roomCategory == "D") {
                    harga = 300000;
                } else if (current->roomCategory == "E") {
                    harga = 350000;
                } else {
                    harga = 0; // Golongan ruang tidak valid
                }

                int totalBiaya = harga * current->duration;
                cout << "  Total Biaya     : " << totalBiaya << endl;

                cout << " +=================================+\n";
                return; // Keluar dari fungsi setelah menemukan pasien
            }
            current = current->next;
        }
    }
    cout << "  Pasien dengan nama" << endl << "  " <<  id << " tidak ditemukan.\n";
    cout << " ====================================\n";
    }
    
// Fungsi untuk menghapus data pasien berdasarkan nama pasien
void removePatientByName(Patient* table[], DeletedPatient history[], int& deletedCount, const string& name) {
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        Patient* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                // Simpan data pasien yang dihapus ke dalam history
                DeletedPatient deletedPatient = {current->name, current->patientID, current->roomCategory, current->duration};
                history[deletedCount++] = deletedPatient;

                if (prev == nullptr) {
                    // Pasien berada di awal linked list
                    table[i] = current->next;
                } else {
                    // Pasien berada di tengah atau akhir linked list
                    prev->next = current->next;
                }

                delete current; // Hapus data pasien
                cout << endl << "  Data pasien dengan nama" << endl << "  " << name << " berhasil dihapus.\n";
                 cout << " +==================================+\n";
                return;
            }

            prev = current;
            current = current->next;
        }
    }

    cout << endl << "  Pasien dengan nama" << endl << "  " << name << " tidak ditemukan.\n";
    cout << " +==================================+\n";
}

void removePatientById(Patient* table[], DeletedPatient history[], int& deletedCount, int id) {
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        Patient* prev = nullptr;

        while (current != nullptr) {
            if (current->patientID == id) {
                // Simpan data pasien yang dihapus ke dalam history
                DeletedPatient deletedPatient = {current->name, current->patientID, current->roomCategory, current->duration};
                history[deletedCount++] = deletedPatient;

                if (prev == nullptr) {
                    // Pasien berada di awal linked list
                    table[i] = current->next;
                } else {
                    // Pasien berada di tengah atau akhir linked list
                    prev->next = current->next;
                }

                delete current; // Hapus data pasien
                cout << endl << "  Data pasien dengan id" << endl << "  " << id << " berhasil dihapus.\n";
                 cout << " +==================================+\n";
                return;
            }

            prev = current;
            current = current->next;
        }
    }

    cout << endl << "  Pasien dengan id" << endl << "  " << id << " tidak ditemukan.\n";
    cout << " +==================================+\n";
}


struct TreeNode {
    Patient* patient;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Patient* p) : patient(p), left(nullptr), right(nullptr) {}
};

TreeNode* insertIntoBST(TreeNode* root, Patient* patient);

TreeNode* buildBinarySearchTree(Patient* table[]) {
    TreeNode* root = nullptr;

    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
            root = insertIntoBST(root, current);
            current = current->next;
        }
    }

    return root;
}

TreeNode* insertIntoBST(TreeNode* root, Patient* patient) {
    if (root == nullptr) {
        return new TreeNode(patient);
    }

    if (patient->patientID < root->patient->patientID) {
        root->left = insertIntoBST(root->left, patient);
    } else {
        root->right = insertIntoBST(root->right, patient);
    }

    return root;
}

TreeNode* searchByName(TreeNode* root, const string& name) {
    if (root == nullptr || root->patient->name == name) {
        return root;
    }

    if (name < root->patient->name) {
        return searchByName(root->left, name);
    } else {
        return searchByName(root->right, name);
    }
}

//masih by id, jadi datanya ya terurut sesuai id bukan sesuai nama
void inorderSearch(TreeNode* root, char startChar, char endChar) {
    if (root != nullptr) {
        inorderSearch(root->left, startChar, endChar);
        
        char firstChar = root->patient->name[0];
        if (firstChar >= startChar && firstChar <= endChar) {
            cout << "  ID Pasien       : " << root->patient->patientID << endl;
            cout << "  Nama            : " << root->patient->name << endl;
            cout << endl << " ===================================\n\n";
        }
        
        inorderSearch(root->right, startChar, endChar);
    }
}

void displayPatientByAlphabetRange(TreeNode* root, char startChar, char endChar) {
    cout << " +" << string(34, '=') << "+" << endl;
    cout << " |            DATA PASIEN           |\n";
    cout << " +" << string(34, '=') << "+" << endl << endl;

    inorderSearch(root, startChar, endChar);
}

// Fungsi untuk menampilkan data pasien dengan metode InOrder pada PTB
void inOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << "  Nama            : " << root->patient->name << endl;
        cout << "  ID Pasien       : " << root->patient->patientID << endl;
        cout << "  Golongan Ruang  : " << root->patient->roomCategory << endl;
        cout << "  Lama Rawat Inap : " << root->patient->duration << " hari" << endl;

        // Menghitung total biaya
        int hargaPerHari;
        if (root->patient->roomCategory == "A") {
            hargaPerHari = 150000;
        } else if (root->patient->roomCategory == "B" ) {
            hargaPerHari = 200000;
        } else if (root->patient->roomCategory == "C" ) {
            hargaPerHari = 250000;
        } else if (root->patient->roomCategory == "D" ) {
            hargaPerHari = 300000;
        } else if (root->patient->roomCategory == "E" ) {
            hargaPerHari = 350000;
        } else {
            hargaPerHari = 0; // Golongan ruang tidak valid
        }

        int totalBiaya = hargaPerHari * root->patient->duration;
        cout << "  Total Biaya     : " << totalBiaya << endl;

        cout << endl << " " << string (36, '=') << endl << endl;
        inOrderTraversal(root->right);
    }
}

// Fungsi untuk menampilkan data pasien dengan metode PostOrder pada PTB
void postOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << "  Nama            : " << root->patient->name << endl;
        cout << "  ID Pasien       : " << root->patient->patientID << endl;
        cout << "  Golongan Ruang  : " << root->patient->roomCategory << endl;
        cout << "  Lama Rawat Inap : " << root->patient->duration << " hari" << endl;

        // Menghitung total biaya
        int hargaPerHari;
        if (root->patient->roomCategory == "A") {
            hargaPerHari = 150000;
        } else if (root->patient->roomCategory == "B" ) {
            hargaPerHari = 200000;
        } else if (root->patient->roomCategory == "C" ) {
            hargaPerHari = 250000;
        } else if (root->patient->roomCategory == "D" ) {
            hargaPerHari = 300000;
        } else if (root->patient->roomCategory == "E" ) {
            hargaPerHari = 350000;
        } else {
            hargaPerHari = 0; // Golongan ruang tidak valid
        }

        int totalBiaya = hargaPerHari * root->patient->duration;
        cout << "  Total Biaya     : " << totalBiaya << endl;

        cout << endl << " "<< string (36, '=') << endl << endl;
    }
}

// Fungsi untuk menampilkan data pasien dengan metode PreOrder pada PTB
void preOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        cout << "  Nama            : " << root->patient->name << endl;
        cout << "  ID Pasien       : " << root->patient->patientID << endl;
        cout << "  Golongan Ruang  : " << root->patient->roomCategory << endl;
        cout << "  Lama Rawat Inap : " << root->patient->duration << " hari" << endl;

        // Menghitung total biaya
        int hargaPerHari;
        if (root->patient->roomCategory == "A") {
            hargaPerHari = 150000;
        } else if (root->patient->roomCategory == "B" ) {
            hargaPerHari = 200000;
        } else if (root->patient->roomCategory == "C" ) {
            hargaPerHari = 250000;
        } else if (root->patient->roomCategory == "D" ) {
            hargaPerHari = 300000;
        } else if (root->patient->roomCategory == "E" ) {
            hargaPerHari = 350000;
        } else {
            hargaPerHari = 0; // Golongan ruang tidak valid
        }
        int totalBiaya = hargaPerHari * root->patient->duration;
        cout << "  Total Biaya     : " << totalBiaya << endl;

        cout << endl << " " << string (36, '=') << endl << endl;
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

struct BSTNode {
    DeletedPatient data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const DeletedPatient& d)
        : data(d), left(nullptr), right(nullptr) {}
};

// Fungsi untuk mengecek apakah history kosong atau tidak
bool isHistoryEmpty(DeletedPatient history[], int history_size) {
    for (int i = 0; i < history_size; ++i) {
        if (!history[i].name.empty()) {
            return false;  // Terdapat data pada indeks i
        }
    }
    return true; // Semua elemen history kosong
}

void inorderTraversal(BSTNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        // Tampilkan data pasien yang dihapus
		cout << "  Nama            : " << root->data.name << endl;
        cout << "  ID Pasien       : " << root->data.patientID << endl;
        cout << "  Golongan Ruang  : " << root->data.roomCategory << endl;
        cout << "  Lama Rawat Inap : " << root->data.duration << " hari" << endl;
		cout << endl << " " << string (36, '=') << endl << endl;
        inorderTraversal(root->right);
    }
}

void preorderTraversal(BSTNode* root) {
    if (root != nullptr) {
        // Tampilkan data pasien yang dihapus
        cout << "  Nama            : " << root->data.name << endl;
        cout << "  ID Pasien       : " << root->data.patientID << endl;
        cout << "  Golongan Ruang  : " << root->data.roomCategory << endl;
        cout << "  Lama Rawat Inap : " << root->data.duration << " hari" << endl;
		cout << endl << " " << string (36, '=') << endl << endl;
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(BSTNode* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        // Tampilkan data pasien yang dihapus
        cout << "  Nama            : " << root->data.name << endl;
        cout << "  ID Pasien       : " << root->data.patientID << endl;
        cout << "  Golongan Ruang  : " << root->data.roomCategory << endl;
        cout << "  Lama Rawat Inap : " << root->data.duration << " hari" << endl;
		cout << endl << " " << string (36, '=') << endl << endl;
    }
}


BSTNode* insertToBST(BSTNode* root, const DeletedPatient& data) {
    if (root == nullptr) {
        return new BSTNode(data);
    }

    if (data.patientID < root->data.patientID) {
        root->left = insertToBST(root->left, data);
    } else if (data.patientID > root->data.patientID) {
        root->right = insertToBST(root->right, data);
    }

    return root;
}



int main() {
    int pilih;
     Patient* patientTable[table_size] = {nullptr}; // Inisialisasi elemen-elemen tabel dengan nullptr
    DeletedPatient deletedPatientHistory[max_deleted]; // Larik untuk menyimpan riwayat pasien yang dihapus
    int deletedCount = 0; // Menghitung jumlah riwayat pasien yang dihapus
    int numPatients;
    
    do {
        system("cls");
        cout << " +" << string (34, '=') << "+" << endl;
        cout << " |" << string (8, ' ') << " RUMAH SAKIT SAVV " << string (8, ' ') << "|" << endl;
        cout << " +" << string (34, '=') << "+" << endl;
        cout << "  1. Lihat Data Semua Pasien\n";
        cout << "  2. Input Data Pasien\n";
        cout << "  3. Tampil Data Pasien\n";
        cout << "  4. Hapus Data Pasien\n";
        cout << "  5. Cari Pasien\n";
        cout << "  6. Lihat History Pasien\n";
        cout << "  0. Keluar\n\n";
        cout << "  Masukkan pilihan Anda : "; cin >> pilih;
        cout << " +" << string (34, '=') << "+" << endl;

        switch(pilih) {
            case 1: {
                // Tambahkan logika untuk menampilkan semua data pasien              
                int pilih1, done1 = 0;
                int pilihc, done0 = 0;
                
                if (isHashTableEmpty(patientTable, table_size)) {
                    cout << endl << "  Data Pasien Kosong.\n";
                    cout << "  Silahkan Input data dahulu.\n\n";
                    cout << " +" << string (34, '=') << "+" << endl << endl << "  ";
                    system("pause");
                    break;  
                } 
                else{
                system("cls");
                cout << " +" << string (34, '=') << "+" << endl;
                cout << " |" << string (6, ' ') << "LIHAT DATA SEMUA PASIEN" << string (5, ' ') << "|" << endl;
                cout << " +" << string (34, '=') << "+" << endl;
                cout << "  1. Berdasarkan Hash Table\n";
                cout << "  2. Berdasarkan PTB\n\n";
                do {
                done0 = 0;
                cout << "  Masukkan pilihan Anda : "; cin >> pilihc;
                cout << endl << " +" << string (34, '=') << "+" << endl;
                TreeNode* rootBST = buildBinarySearchTree(patientTable);
                switch(pilihc) {
                    case 1 : {
						cout << " |" << string (6, ' ') << "   BERDASARKAN HASH    " << string (5, ' ') << "|" << endl;
						cout << " +" << string (34, '=') << "+" << endl << endl;
				
						displayPatientHash(patientTable);
               
						cout << "  "; 
						system("pause");
						break;
                    }
                    case 2 : {
                cout << " |" << string (6, ' ') << "    BERDASARKAN PTB    " << string (5, ' ') << "|" << endl;
                cout << " +" << string (34, '=') << "+" << endl;
                cout << "  1. InOrder\n";
                cout << "  2. PostOrder\n";
                cout << "  3. PreOrder\n\n";
                do {
                done1 = 0;
                cout << "  Masukkan pilihan Anda : "; cin >> pilih1;
                cout << endl << " +" << string (34, '=') << "+" << endl;

              
                switch(pilih1) {
                    case 1 : {
                            cout << " |   DATA SEMUA PASIEN (InOrder)    |\n";
                            cout << " +" << string (34, '=') << "+" << endl << endl;
                            inOrderTraversal(rootBST);
                            break;
                    }
                    case 2 : {
                           cout << " |  DATA SEMUA PASIEN (PostOrder)   |\n";
                            cout << " +" << string (34, '=') << "+" << endl << endl;
                            postOrderTraversal(rootBST);
                            break;
                    }
                    case 3 : {
                            cout << " |   DATA SEMUA PASIEN (PreOrder)   |\n";
                            cout << " +" << string (34, '=') << "+" << endl << endl;
                            preOrderTraversal(rootBST);
                            break;
                    }
                    default : {
                        cout << endl << "  Input Menu yang tersedia...\n";
                        cout << endl << " +" << string (34, '=') << "+" << endl;
                        cout << endl;
                        done1 = 1;
                        break;
                    }
                }
                }while(done1 != 0); 
                
                cout << "  "; 
                system("pause");
                break;
                    }   
                    default : {
                        cout << endl << "  Input Menu yang tersedia...\n";
                        cout << endl << " +" << string (34, '=') << "+" << endl;
                        cout << endl;
                        done0 = 1;
                        break;
                    }
                }
                }while(done0 != 0); 
                break;
                 }               
            
                }
            case 2: {
                system("cls");
                cout << " +" << string (34, '=') << "+" << endl;
                cout << " |" << string (8, ' ') << "INPUT DATA PASIEN " << string (8, ' ') << "|" << endl;
                cout << " +" << string (34, '=') << "+" << endl << endl;
                cout << "  Jumlah input data pasien :  ";
                cin >> numPatients;
                cin.ignore(); // Membersihkan newline di buffer

                while(numPatients == 0){
                    cout << endl << "  Input data harus > 0" << endl;
                    cout << "  Jumlah input data pasien :  ";
                    cin >> numPatients;
                    cin.ignore();
                    }
                // Inisialisasi tabel pasien
                // for (int i = 0; i < table_size; ++i) {
                //     patientTable[i] = nullptr;
                // }

                // Menambahkan data pasien
                string name;
                string roomCategory;
                int patientID, duration;
                
                cout << endl << "  Silahkan masukkan data pasien  " << endl << endl;
                cout << " +" << string(34, '=') << "+" << endl ;
                cout << " |" << string(2, ' ') << "Gol. Ruang" << string(2, ' ') << "|" << string(7, ' ') << "Harga" << string(7, ' ') << "|" << endl;
                cout << " +" << string(34, '=') << "+" << endl ;
                cout << " |" << string(6, ' ') << "A" << string(7, ' ') << "|"  << string(3, ' ') << "Rp150.000/hari" << string(2, ' ') << "|" << endl;
                cout << " |" << string(6, ' ') << "B" << string(7, ' ') << "|"  << string(3, ' ') << "Rp200.000/hari" << string(2, ' ') << "|" << endl;
                cout << " |" << string(6, ' ') << "C" << string(7, ' ') << "|"  << string(3, ' ') << "Rp250.000/hari" << string(2, ' ') << "|" << endl;
                cout << " |" << string(6, ' ') << "D" << string(7, ' ') << "|"  << string(3, ' ') << "Rp300.000/hari" << string(2, ' ') << "|" << endl;
                cout << " |" << string(6, ' ') << "E" << string(7, ' ') << "|"  << string(3, ' ') << "Rp350.000/hari" << string(2, ' ') << "|" << endl;
                cout << " +" << string(34, '=') << "+" << endl ;
                for (int i = 0; i < numPatients; ++i) {
                    cout << endl << " " << string (36, '=') << endl;
                    cout << "  Data Pasien ke-" << i + 1 << ":" << endl << endl;
                    cout << "  Input Nama pada awal huruf\n" <<  "  menggunakan huruf besar\n";
                    cout << endl << "  Nama            : " ;
                    
                    getline(cin, name);
                    while(!startsWithUppercase(name)) {
                        cout << endl;
                        cout << "  Input Nama tidak sesuai ketentuan.\n";
                        cout << "  Nama            : " ;
                        getline(cin, name);
                    }
                    cout << "  ID Pasien       : ";
                    const int range = 1000; // Rentang angka acak dari 1 hingga 1000
                    const int numberOfRandoms = 10;
                    int usedNumbers[numberOfRandoms];

        
                    for (int i = 0; i < numberOfRandoms; ++i) {
                        int randomNum = generateUniqueRandomNumber(usedNumbers, i, range);
                        usedNumbers[i] = randomNum;
                        patientID = randomNum;
                    }
                    cout << patientID << endl;
                    cout << "  Golongan Ruang (A-E)   : ";
                    getline(cin, roomCategory);
                    while(roomCategory < "A" || roomCategory > "E") { //klo diinput angka masih jebol
                            cout << endl << "  Input golongan ruang tidak valid.\n";
                            // cout << endl << "  Pilih antara A-E" << endl;
                            cout << "  Golongan Ruang (A-E)   : ";
                            getline(cin, roomCategory); 
                            // system("pause");
                            // break;
                    }
                    cout << "  Lama Rawat Inap (hari) : ";
                    cin >> duration;
                    cin.ignore(); // Membersihkan newline di buffer

                    addPatient(patientTable, name, patientID, roomCategory, duration);
                    cout << " " << string (36, '=') << endl;
               }
                cout << endl << "  ";
                system("pause");
                break;
            }
            case 3: {
                string searchName;
                int searchId;
                int pilih2, done3 = 0;
                
                if (isHashTableEmpty(patientTable, table_size)) {
                    cout << endl << "  Data Pasien Kosong.\n";
                    cout << "  Silahkan Input data dahulu.\n\n";
                    cout << " +" << string (34, '=') << "+" << endl << endl << "  ";
                    system("pause");
                    break;  
                } else {
                    system("cls");
                cout << " +" << string (34, '=') << "+" << endl;
                cout << " |" << string (8, ' ') << "TAMPIL DATA PASIEN " << string (7, ' ') << "|" << endl;
                cout << " +" << string (34, '=') << "+" << endl;
                cout << "  1. Berdasarkan nama pasien" << endl;
                cout << "  2. Berdasarkan id pasien" << endl << endl;
                do {
                done3 = 0;
                cout << "  Masukkan pilihan Anda : ";
                cin >> pilih2;
                cout << " +" << string (34, '=') << "+" << endl;
                
                switch(pilih2){
                    case 1 :{ 
                        cout << endl << "  Masukkan nama pasien : ";
                        cin.ignore(); // Membersihkan newline di buffer
                        getline(cin, searchName);
                        cout << endl; 
                        displayPatientByName(patientTable, searchName);
                        cout << endl << "  ";
                        system("pause");
                        break; }
                    case 2 :{
                        cout << endl << "  Masukkan id pasien : ";
                        cin.ignore(); // Membersihkan newline di buffer
                        cin >> searchId;
                        cout << endl; 
                        displayPatientById(patientTable, searchId);
                        cout << endl << "  ";
                        system("pause");
                        break;  }
                    default:{
                        cout << endl << "  Input Menu yang tersedia...\n";
                        cout << endl << " +" << string (34, '=') << "+" << endl;
                        cout << endl;
                        done3 = 1;
                        break; }
                }
                }while(done3 != 0); 
                break;
            }   
            }
            case 4: {
                int done4 = 0;
                string removeName;
                int pilih3;
                int removeId;
               
                 if (isHashTableEmpty(patientTable, table_size)) {
                    cout << endl << "  Data Pasien Kosong.\n";
                    cout << "  Silahkan Input data dahulu.\n\n";
                    cout << " +" << string (34, '=') << "+" << endl << endl << "  ";
                    system("pause");
                    break;  
                } else {
            system("cls");
                cout << " +" << string (34, '=') << "+" << endl;
                cout << " |" << string (8, ' ') << "HAPUS DATA PASIEN " << string (8, ' ') << "|" << endl;
                cout << " +" << string (34, '=') << "+" << endl;
                cout << "  1. Berdasarkan nama pasien" << endl;
                cout << "  2. Berdasarkan id pasien" << endl << endl;
                do {
                done4 = 0;
                cout << "  Masukkan pilihan Anda : ";
                cin >> pilih3;
                cout << " +" <<  string (34, '=') << "+" << endl;
                
                switch(pilih3){
                    case 1 :{ 
                        cout <<  endl << "  Masukkan nama pasien : ";
                        cin.ignore(); // Membersihkan newline di buffer
                        getline(cin, removeName);
                        removePatientByName(patientTable, deletedPatientHistory, deletedCount, removeName);
                        //cin.ignore(); // Membersihkan newline di buffer setelah selesai mengambil input
                        cout << endl << "  ";
                        system("pause");
                        break; }
                    case 2 :{
                        cout << endl <<  "  Masukkan id pasien : ";
                        cin.ignore(); // Membersihkan newline di buffer
                        cin >> removeId;
                        removePatientById(patientTable, deletedPatientHistory, deletedCount, removeId);
                        //cin.ignore(); // Membersihkan newline di buffer setelah selesai mengambil input
                        cout << endl << "  ";
                        system("pause");
                        break;
                            }
                    default:{
                        cout << endl << "  Input Menu yang tersedia...\n";
                        cout << endl << " +" << string (34, '=') << "+" << endl;
                        cout << endl;
                        done4 = 1;
                        break; }
                }           
                }while(done4 != 0); 
                break;
                
            }   
            }
            case 5: {
				 if (isHashTableEmpty(patientTable, table_size)) {
                    cout << endl << "  Data Pasien Kosong.\n";
                    cout << "  Silahkan Input data dahulu.\n\n";
                    cout << " +" << string (34, '=') << "+" << endl << endl << "  ";
                    system("pause");
                    break;  
                } else {
					TreeNode* rootBST = buildBinarySearchTree(patientTable);
				system("cls");
				cout << " +" << string (34, '=') << "+" << endl;
				cout << " |" << string (3, ' ') << "  CARI DATA PASIEN DIHAPUS  " << string (3, ' ') << "|" << endl;
				cout << " +" << string (34, '=') << "+" << endl << endl;
                char startChar, endChar;
                cout << "  Rentang abjad menggunakan" << endl << "  huruf kapital(A-Z).\n\n";
				cout << "  Masukkan rentang abjad pertama : "; cin >> startChar;
                while(!isupper(startChar)){
					cout << endl << "  Gunakan huruf kapital (A-Z)" << endl;
                    cout << "  Masukkan rentang abjad pertama : "; cin >> startChar;
                }
                cout << "  Masukkan rentang abjad terakhir : "; cin >> endChar;
                while(!isupper(endChar)){
					cout << endl << "  Gunakan huruf kapital (A-Z)" << endl;
                    cout << "  Masukkan rentang abjad terakhir : "; cin >> endChar;
                }

                if (startChar < 'A' || startChar > 'Z' || endChar < 'A' || endChar > 'Z' || startChar > endChar) {
                    cout << "\n  Input rentang abjad tidak valid.\n";
                    cout << " +" << string (34, '=') << "+" << endl << endl;
                    cout << "  ";
                    system("pause");
                    break;
                }

				cout << endl;
                displayPatientByAlphabetRange(rootBST, startChar, endChar);
				cout << "  ";
                system("pause");
                break;}
            }
            case 6: {
				int done6;
                if (isHistoryEmpty(deletedPatientHistory, max_deleted)) {
                    cout << endl << "  History Pasien Masih Kosong.\n\n";
                    cout << " +" << string (34, '=') << "+" << endl << endl << "  ";
                    system("pause");
                    break;  
                }
                else {
                    system("cls");
    cout << " +" << string (34, '=') << "+" << endl;
    cout << " |" << string (3, ' ') << "HISTORY DATA PASIEN DIHAPUS " << string (3, ' ') << "|" << endl;
    cout << " +" << string (34, '=') << "+" << endl << endl;
    // Tampilkan menu untuk pilihan traversal BST
    cout << "  1. Inorder Traversal\n";
    cout << "  2. Preorder Traversal\n";
    cout << "  3. Postorder Traversal\n\n";
    do{
	cout << "  Pilih metode traversal : ";
    int traversalChoice; 
	done6 = 0;	
    cin >> traversalChoice;
    cout << endl << " +" << string (34, '=') << "+" << endl;

    // Buat BST dari data pasien yang dihapus
    BSTNode* bstRoot = nullptr;
    for (int i = 0; i < deletedCount; ++i) {
        bstRoot = insertToBST(bstRoot, deletedPatientHistory[i]);
    }

    // Tampilkan hasil traversal sesuai pilihan user
    switch (traversalChoice) {
        case 1:	
			cout << " |     HISTORY PASIEN (InOrder)     |\n";
			cout << " +" << string (34, '=') << "+" << endl << endl;
            inorderTraversal(bstRoot);
            break;
        case 2:
            cout << " |     HISTORY PASIEN (PreOrder)    |\n";
			cout << " +" << string (34, '=') << "+" << endl << endl;
            preorderTraversal(bstRoot);
            break;
        case 3:
			cout << " |    HISTORY PASIEN (PostOrder)    |\n";
			cout << " +" << string (34, '=') << "+" << endl << endl;
            postorderTraversal(bstRoot);
            break;
        default:
			cout << endl << "  Input Menu yang tersedia...\n";
            cout << endl << " +" << string (34, '=') << "+" << endl;
            cout << endl;
            done6 = 1;
           
            break;
           }
    }while(done6 != 0);
            system("pause");
    break;
    // Hapus BST setelah digunakan
    // (Anda bisa menambahkan fungsi untuk membersihkan seluruh BST)
    }
}

            case 0: {
                cout << endl << "    Semoga lekas sembuh kawan ^-^" << endl;
                cout << endl << " +" << string (34, '=') << "+" << endl << endl;
                exit(0);
                break;
            }
            default: {
                cout << endl << "  Input Menu yang tersedia...\n";
                cout << endl << " +" << string (34, '=') << "+" << endl;
                cout << endl << " ";
                system("pause");
                break;
            }
        }
    } while(pilih != 0);
}
