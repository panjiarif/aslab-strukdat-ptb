#include <iostream>
#include <iomanip>
using namespace std;

// Struktur node pohon biner
struct Node {
    int nilai;
    Node *kiri, *kanan;
};

// Fungsi membuat node baru
Node* buatNode(int nilai) {
    Node* baru = new Node();
    baru->nilai = nilai;
    baru->kiri = baru->kanan = nullptr;
    return baru;
}

// Fungsi menyisipkan node (insert)
Node* sisipNode(Node* akar, int nilai) {
    if (akar == nullptr)
        return buatNode(nilai);
    if (nilai < akar->nilai)
        akar->kiri = sisipNode(akar->kiri, nilai);
    else if (nilai > akar->nilai)
        akar->kanan = sisipNode(akar->kanan, nilai);
    else
        cout << "Gagal input: Nilai " << nilai << " sudah ada di pohon.\n";
    return akar;
}

// Fungsi mencari node dengan nilai tertentu
bool cariNode(Node* akar, int nilai) {
    if (akar == nullptr)
        return false;
    if (akar->nilai == nilai)
        return true;
    else if (nilai < akar->nilai)
        return cariNode(akar->kiri, nilai);
    else
        return cariNode(akar->kanan, nilai);
}

// Fungsi mencari node dengan nilai minimum
Node* nilaiMinimal(Node* akar) {
    while (akar && akar->kiri != nullptr)
        akar = akar->kiri;
    return akar;
}

// Fungsi menghapus node
Node* hapusNode(Node* akar, int nilai) {
    if (akar == nullptr)
        return akar;
    if (nilai < akar->nilai)
        akar->kiri = hapusNode(akar->kiri, nilai);
    else if (nilai > akar->nilai)
        akar->kanan = hapusNode(akar->kanan, nilai);
    else {
        // Node ditemukan
        if (akar->kiri == nullptr) {
            Node* temp = akar->kanan;
            delete akar;
            return temp;
        }
        else if (akar->kanan == nullptr) {
            Node* temp = akar->kiri;
            delete akar;
            return temp;
        }
        // Node punya dua anak
        Node* temp = nilaiMinimal(akar->kanan);
        akar->nilai = temp->nilai;
        akar->kanan = hapusNode(akar->kanan, temp->nilai);
    }
    return akar;
}

// Fungsi traversal
void inorder(Node* akar) {
    if (akar != nullptr) {
        inorder(akar->kiri);
        cout << akar->nilai << " ";
        inorder(akar->kanan);
    }
}

void preorder(Node* akar) {
    if (akar != nullptr) {
        cout << akar->nilai << " ";
        preorder(akar->kiri);
        preorder(akar->kanan);
    }
}

void postorder(Node* akar) {
    if (akar != nullptr) {
        postorder(akar->kiri);
        postorder(akar->kanan);
        cout << akar->nilai << " ";
    }
}

// Fungsi menampilkan struktur pohon (rotasi 90°)
void tampilkanPohon(Node* akar, int spasi = 0, int jarak = 5) {
    if (akar == nullptr)
        return;
    spasi += jarak;

    tampilkanPohon(akar->kanan, spasi);
    cout << endl;
    for (int i = jarak; i < spasi; i++)
        cout << " ";
    cout << akar->nilai << "\n";
    tampilkanPohon(akar->kiri, spasi);
}

// Fungsi penghapusan seluruh pohon (Dipanggil oleh Destructor atau di main)
void hapusPohon(Node* akar) {
    if (akar == nullptr) return;
    hapusPohon(akar->kiri);
    hapusPohon(akar->kanan);
    delete akar;
}

// Menu utama
void menu() {
    cout << "\n=== PROGRAM POHON TELUSUR BINER ===\n";
    cout << "1. Tambah data\n";
    cout << "2. Hapus data\n";
    cout << "3. Cari data\n";
    cout << "4. Cetak traversal (Inorder/Preorder/Postorder)\n";
    cout << "5. Tampilkan struktur pohon\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu: ";
}

int main() {
    Node* akar = nullptr;
    int pilihan, nilai;
    bool nilaiDitemukan, sudahAda;

    do {
      system("clear"); // gunakan "cls" jika di Windows
        menu();
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "Masukkan nilai yang ingin ditambahkan: ";
            cin >> nilai;
            sudahAda = cariNode(akar, nilai);
            if (sudahAda) {
                akar = sisipNode(akar, nilai);
            } else {
                akar = sisipNode(akar, nilai);
                cout << "Nilai " << nilai << " berhasil ditambahkan.\n";
            }
            break;
        case 2:
            cout << "Masukkan nilai yang ingin dihapus: ";
            cin >> nilai;
            nilaiDitemukan = cariNode(akar, nilai);
            if (nilaiDitemukan) {
                akar = hapusNode(akar, nilai);
                cout << "Nilai " << nilai << " berhasil dihapus.\n";
            } else {
                cout << "Gagal menghapus: Nilai " << nilai << " tidak ditemukan di pohon.\n";
            }
            break;
        case 3:
            cout << "Masukkan nilai yang ingin dicari: ";
            cin >> nilai;
            if (cariNode(akar, nilai))
                cout << "Data ditemukan di pohon.\n";
            else
                cout << "Data tidak ditemukan.\n";
            break;
        case 4:
            cout << "\nInorder   : "; inorder(akar);
            cout << "\nPreorder  : "; preorder(akar);
            cout << "\nPostorder : "; postorder(akar);
            cout << endl;
            break;
        case 5:
            cout << "\nStruktur pohon biner:\n";
            tampilkanPohon(akar);
            break;
        case 0:
            cout << "Terima kasih!\n";
            hapusPohon(akar);
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            cin.ignore();
            cin.get();
        }

        if (pilihan != 0) {
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (pilihan != 0);

    return 0;
}
