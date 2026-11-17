
#include <iostream>

using namespace std;

struct nodeQueue {
    int kode;
    string nama;
    nodeQueue* next;
};

struct nodeStack {
    int kode;
    string nama;
    nodeStack* next;
};

struct nodeTree {
    int kode;
    string nama;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = NULL;
nodeQueue* last = NULL;
nodeStack* top = NULL;
nodeTree* root = NULL;

// menambahkan node baru ke tree berdasarkan kode energi.
// kode lebih kecil masuk ke kiri, kode lebih besar masuk ke kanan.
// mengembalikan akar tree setelah penambahan.
nodeTree* tambah_tree(nodeTree* akar, int kode, string nama) {
    if (akar == NULL) {
        return new nodeTree {kode, nama, NULL, NULL};
    }
    if (kode < akar->kode) {
        akar->kiri = tambah_tree(akar->kiri, kode, nama);
    } else {
        akar->kanan = tambah_tree(akar->kanan, kode, nama);
    }
    return akar;
}

// TODO (Menu 6 & 8): mencari node di tree berdasarkan kode energi.
nodeTree* cari_tree(nodeTree* akar, int kode) {
    // lengkapi logika pencarian BST di sini
    return NULL;
}

// TODO (Menu 8): menghapus node di tree berdasarkan kode energi (3 kasus: 0, 1, 2 anak).
nodeTree* hapus_tree(nodeTree* akar, int kode) {
    // lengkapi logika penghapusan BST di sini
    return akar;
}

// menampilkan isi tree dengan urutan: node, kiri, kanan.
void preorder(nodeTree* akar, int& no) {
    if (akar == NULL) {
        return;
    }
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

// menampilkan isi tree dengan urutan: kiri, node, kanan.
void inorder(nodeTree* akar, int& no) {
    if (akar == NULL) {
        return;
    }
    inorder(akar->kiri, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
    inorder(akar->kanan, no);
}

// menampilkan isi tree dengan urutan: kiri, kanan, node.
void postorder(nodeTree* akar, int& no) {
    if (akar == NULL) {
        return;
    }
    postorder(akar->kiri, no);
    postorder(akar->kanan, no);
    cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
    no++;
}

// 1. Tambah Energi (Enqueue ke posisi paling belakang)
void tambah_energi() {
    int kode;
    string nama;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Kode energi harus berupa angka lebih dari 0!" << endl << endl;
        return;
    }

    nodeQueue* q = front;
    while (q != NULL) {
        if (q->kode == kode) {
            cout << "Kode energi sudah digunakan!" << endl << endl;
            return;
        }
        q = q->next;
    }
    nodeStack* s = top;
    while (s != NULL) {
        if (s->kode == kode) {
            cout << "Kode energi sudah digunakan!" << endl << endl;
            return;
        }
        s = s->next;
    }

    cout << "Masukkan nama energi: ";
    cin.ignore();
    getline(cin, nama);
    if (nama.empty()) {
        cout << "Nama energi tidak boleh kosong!" << endl << endl;
        return;
    }

    nodeQueue* nb = new nodeQueue {kode, nama, NULL};
    if (front == NULL) {
        front = last = nb;
    } else {
        last->next = nb;
        last = nb;
    }
    cout << "Berhasil memasukkan energi!" << endl << endl;
}

// 2. Lihat Energi Dalam Antrean
void lihat_antrean() {
    if (front == NULL) {
        cout << "Antrean energi masih kosong!" << endl << endl;
        return;
    }
    cout << "=== Energi Dalam Antrean ===" << endl << endl;
    nodeQueue* nb = front;
    int no = 1;
    while (nb != NULL) {
        cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

// 3. Proses Energi (Dequeue -> Push Stack & Insert BST)
void proses_energi() {
    if (front == NULL) {
        cout << "Antrean energi masih kosong!" << endl << endl;
        return;
    }

    nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack {hapus->kode, hapus->nama, top};
    top = nb;
    root = tambah_tree(root, hapus->kode, hapus->nama);
    cout << "Berhasil memproses energi " << hapus->nama << "!" << endl << endl;
    front = hapus->next;
    if (front ==
