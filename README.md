# Tugas Kecil 1 IF2211 Strategi Algoritma 2021/2022

13520024 Hilya Fadhilah Imania

## Deskripsi Singkat

Program ini dibuat untuk menyelesaikan permainan mencari kata "word puzzle"
dengan strategi brute force tanpa pendekatan heuristik.

## Requirements dan Instalasi

Program ditulis dalam bahasa C++ standar 2014.
Instalasi dilakukan dengan utility `make` menggunakan compiler `g++` minimal versi 6.
Pada direktori utama repository ini, jalankan perintah berikut:

```
$ make
```

## Menjalankan Program

Program dapat menerima masukan nama file input sebagai argument pertama.

```
$ ./bin/wordpuzzle test/sm-1.txt
```

Program juga dapat menerima masukan melalui standard input.

```
$ ./bin/wordpuzzle < test/sm-1.txt
```

Contoh format file dapat dilihat pada direktori `test`.

> ⚠ Program dibuat dengan asumsi masukan valid.
> Tidak boleh ada kelebihan spasi baik sebelum, sesudah,
> maupun di antara huruf puzzle dan kata yang dicari.

## License

[MIT](https://opensource.org/licenses/MIT)

Copyright (C) 2022, Hilya Fadhilah Imania
