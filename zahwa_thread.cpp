#include <iostream>
#include <pthread.h>
using namespace std;

int stok = 100;
pthread_mutex_t mutex_stok;

int hasil_penjualan;
int hasil_pengembalian;
int hasil_restock;

void* penjualan(void* arg)
{
    pthread_mutex_lock(&mutex_stok);

    stok -= 20;
    hasil_penjualan = stok;

    pthread_mutex_unlock(&mutex_stok);

    return NULL;
}

void* pengembalian(void* arg)
{
    pthread_mutex_lock(&mutex_stok);

    stok += 10;
    hasil_pengembalian = stok;

    pthread_mutex_unlock(&mutex_stok);

    return NULL;
}

void* restock(void* arg)
{
    pthread_mutex_lock(&mutex_stok);

    stok += 50;
    hasil_restock = stok;

    pthread_mutex_unlock(&mutex_stok);

    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    pthread_mutex_init(&mutex_stok, NULL);

    pthread_create(&thread1, NULL, penjualan, NULL);
    pthread_create(&thread2, NULL, pengembalian, NULL);
    pthread_create(&thread3, NULL, restock, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    cout << "Thread 1 - Penjualan 20 barang | "
         << "Stok setelah penjualan: " << hasil_penjualan << endl;

    cout << "Thread 2 - Pengembalian 10 barang | "
         << "Stok setelah pengembalian: " << hasil_pengembalian << endl;

    cout << "Thread 3 - Restock 50 barang | "
         << "Stok setelah restock: " << hasil_restock << endl;

    cout << "Stok akhir: " << stok << endl;

    pthread_mutex_destroy(&mutex_stok);

    return 0;
}
