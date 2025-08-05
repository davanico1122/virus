
# Advanced Virus Simulation Toolkit (Educational)

## 🎯 Tujuan Proyek
Proyek ini merupakan simulasi virus komputer **edukasional** yang dirancang untuk:

- Mendemonstrasikan teknik malware modern secara **aman**
- Meningkatkan **kesadaran keamanan siber**
- Memberikan alat pembelajaran untuk pelatihan **blue team / red team**
- Membantu **pembuat konten YouTube** membuat demo keamanan yang menarik
- Mengajarkan **mitigasi ancaman secara praktis**

> ⚠️ **Peringatan:** Proyek ini hanya untuk tujuan edukasi. Jangan digunakan di sistem utama.

---

## 🧪 Fitur Simulasi

| Efek | Deskripsi |
|------|-----------|
| Inversi Warna | Membalik warna layar (efek negatif) |
| Rotasi Layar | Memutar layar 180° |
| Goyang Jendela | Menggoyangkan semua jendela |
| Suara Beep Acak | Memainkan suara sistem dengan frekuensi acak |
| Spam Desktop | Membuat file teks di Desktop |
| Ganti Wallpaper | Wallpaper sementara dari resource |
| Hijack Clipboard | Mengubah isi clipboard |
| Pesan Error Palsu | Tampilkan `MessageBox` palsu |
| Mouse Jitter | Gerakan acak pada mouse |
| Monitor Browser | Membuka kembali Chrome/Firefox jika ditutup |
| Redirect Browser | Membuka situs prank atau edukasi |
| Balloon Tip | Menampilkan notifikasi efek yang sedang berjalan |

---

## 🖥️ Persyaratan Sistem

### Minimum
- Windows 7 ke atas (x86/x64)
- CPU 1GHz, RAM 512MB, 10MB disk

### Rekomendasi
- Windows 10/11
- CPU 2GHz dual-core, RAM 2GB+
- Jalankan di VirtualBox / VMware

---

## ⚙️ Cara Build (Menjadi .EXE)

### 🔧 Dengan MinGW (GCC)

1. Install MinGW:
```bash
winget install MinGW.MinGW
```

2. Compile:
```bash
gcc -mwindows main.c -o VirusSimulator.exe \
    -lcomctl32 -lwinmm -lgdi32 -lshell32 \
    -O2 -s -fstack-protector-strong
```

3. Jalankan hasilnya:
```bash
VirusSimulator.exe
```

### 💼 Dengan Visual Studio

- Buat project baru: `Windows Desktop Application`
- Tambahkan file `main.c`
- Atur linker:
  - SubSystem = `Windows (/SUBSYSTEM:WINDOWS)`
  - Tambah ke "Additional Dependencies": `comctl32.lib;winmm.lib;gdi32.lib;shell32.lib`
- Build dalam mode `Release`

---

## 🧠 Mekanisme Edukasional

- Semua efek memiliki durasi terbatas dan tidak permanen.
- Hotkey `Ctrl + Alt + End` mengembalikan sistem ke normal.
- Cocok untuk pelatihan keamanan atau pembuatan konten.

---

## 🛡️ Fitur Keamanan

- Tidak ada operasi destruktif
- Tidak menyentuh registry atau file sistem
- Semua perubahan bisa dipulihkan
- Backup & Restore pengaturan
- Ideal dijalankan di sandbox / VM

---

## ❓ FAQ

**Q: Apakah ini virus sungguhan?**  
A: Tidak. Ini hanya simulasi untuk edukasi.

**Q: Apakah bisa merusak sistem?**  
A: Tidak. Efek tidak permanen, dan bisa dihentikan kapan saja.

**Q: Mengapa antivirus mendeteksi sebagai ancaman?**  
A: Karena tekniknya meniru malware, walau tanpa payload berbahaya.

---

## 📜 Lisensi

Licensed under the **Educational Community License v2.0 (ECL-2.0)**

> ❌ Dilarang menyalahgunakan proyek ini untuk:
> - Aktivitas ilegal
> - Penipuan
> - Tujuan merusak

---

**Copyright 2023–2025 Cybersecurity Educator**
