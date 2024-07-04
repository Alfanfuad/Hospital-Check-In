#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "TataCara.h"

struct jadwal
{
	char namaDokter[100];
	char hari[100];
};
typedef struct jadwal jadwal;
// penggunaan struktur
struct form
{
	struct
	{
		char namaPanggilan[100];
		char namaLengkap[100];
	};
	char alamat[100];
	char kontak[100];
	char ktp[100];
	char bank[100];
	int umur;
	jadwal jadwal;
	struct form *next;
};
typedef struct form form;
struct Dokter
{
	char nama[100];
	char spesialis[100];
	bool available[7];
};
typedef struct Dokter Dokter;
// deklarasikan variabel global
void hapusFormulir(form **formulir, Dokter dokter[]);
int getIndexFromHari(const char *hari);
int getIndexFromDokter(const char *nama);
void booking(form *formulir, Dokter *dokter);
void jadwal_dokter();
void hapusAll(form *formulir);
void addFormulir(form **formulir);
void showFormulir(form *formulir);
// program utama

int main()
{

	int opsi, i, j;
	Dokter dokter[5];

	strcpy(dokter[0].nama, "Dr. Saburo");

	strcpy(dokter[0].spesialis, "Kulit");
	strcpy(dokter[1].nama, "Dr. Bineka");
	strcpy(dokter[1].spesialis, "Gigi");
	strcpy(dokter[2].nama, "Dr. Saskeh");
	strcpy(dokter[2].spesialis, "Paru-Paru");
	strcpy(dokter[3].nama, "Dr. Lur Bor");
	strcpy(dokter[3].spesialis, "Jantung");
	strcpy(dokter[4].nama, "Dr. Frutang");
	strcpy(dokter[4].spesialis, "Umum");
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 7; j++)
			dokter[i].available[j] = true;
	}

	form *formulir = NULL;

	printf("		============= Selamat Datang di Rumah Sakit Fisika Farma =============\n\n");
	do
	{
		printf("Silahkan pilih option yang Anda inginkan: ......\n");
		printf("\
		1. Tata Cara Pendaftaran\n\
		2. Info Jadwal Dokter\n\
		3. Formulir Database\n\
		4. Booking Jadwal Check Up\n\
		5. Lihat semua formulir\n\
		6. Hapus berdasarkan nama\n\
		7. Keluar");
		printf("\n>: ");
		scanf("%d", &opsi);
		switch (opsi)
		{
		case 1:			 // penunjukan tata cara pengisian data
			tata_cara(); // pemanggilan function tata_cara
			printf("Tekan apa saja untuk kembali!");
			getch();
			system("cls");
			break;

		case 2:					   // penunjukkan jadwal dokter
			jadwal_dokter(dokter); // pemanggilan function jadwal_dokter
			printf("Tekan apa saja untuk kembali!");
			getch();
			system("cls");
			break;

		case 3:			   // pengisian formulir
			system("cls"); // untuk membersihkan window
			addFormulir(&formulir);
			getch();
			system("cls");
			break;
		case 4:						   // mengisi jadwal
			booking(formulir, dokter);
			getch();
			system("cls"); // pemanggilan function booking
			break;
		case 5:
			showFormulir(formulir);
			getch();
			break;
		case 6:
			hapusFormulir(&formulir, dokter);
			getch();
			break;
		default:
			break;
		}
	} while (opsi != 7);
	printf("\nTerima Kasih, Sampai Jumpa!\n");
	hapusAll(formulir);
}
void hapusFormulir(form ** formulir, Dokter dokter[]){
	char nama[100];
	form *iterator1 = *formulir;
	form *iterator2 = iterator1;
	if (*formulir == NULL){
		return;
	}else{
		printf("Input nama lengkap yang ingin dicari: ");
		scanf(" %101[^\n]s", nama);
		while (iterator1 != NULL){
			if(!strcmp(iterator1->namaLengkap,nama)){
				dokter[getIndexFromDokter(iterator1->jadwal.namaDokter)].available[getIndexFromHari(iterator1->jadwal.hari)] = true;
				if (iterator1 == *formulir){
					*formulir = iterator1->next;
				}else if(iterator1->next == NULL){
					iterator2->next = NULL;
				}else{
					iterator2->next = iterator1->next;
				}
				free(iterator1);
				printf("Form berhasil dihapus!\n");
				return;
			}
			iterator2 = iterator1;
			iterator1 = iterator1->next;
		}
		printf("Nama tidak ditemukan!\n");
		
	}
}
void hapusAll(form *formulir)
{
	form *temp = formulir;
	while (formulir != NULL)
	{
		temp = temp->next;
		free(formulir);
		formulir = temp;
	}
}
void addFormulir(form **formulir)
{
	int tahunLahir;
	int opsiForm;
	int lihatData;

	form *baru = malloc(sizeof(form));
	baru->next = NULL;
	printf("\nFormulir data diri\n");

	printf("\nNama lengkap & Nama Panggilan : ");
	scanf(" %101[^\n]s", baru->namaLengkap);
	printf("\t\t\t\t");
	scanf(" %101[^\n]s", baru->namaPanggilan);
	fflush(stdin);

	printf("\nAlamat\t\t\t: ");
	scanf(" %101[^\n]s", baru->alamat);
	fflush(stdin);

	printf("No HP/WA\t\t: ");
	scanf(" %101[^\n]s", baru->kontak);
	fflush(stdin);

	printf("NIK/KTP\t\t\t: ");
	scanf(" %101[^\n]s", baru->ktp);
	fflush(stdin);

	printf("Tahun Lahir\t\t: ");
	scanf("%d", &tahunLahir);
	baru->umur = 2022 - tahunLahir;
	fflush(stdin);

	printf("Pengguna Bank\t\t: ");
	scanf(" %101[^\n]s", baru->bank);
	fflush(stdin);

	printf("\nApakah Anda ingin melihat bagian pengisian data formulir? \nKetik 1 (ya)/ 0 (tidak)! >: ");
	scanf("%d", &opsiForm);

	system("cls");
	if (opsiForm == 1)
	{

		do
		{
			printf("\nData bagian mana yang ingin Anda lihat?\n1. Nama, 2. Alamat, 3. Nomor HP, 4. NIK/KTP, 5. Pengguna Bank\n(Ketik angka) >: ");
			scanf("%d", &lihatData);
			if (lihatData == 1)
			{
				printf("\nNama lengkap & Nama Panggilan : ");
				printf("\nNama Lengkap\t: %s\n", baru->namaLengkap);
				printf("\nAlamat\t: %s\n", baru->namaPanggilan);
			}
			else if (lihatData == 2)
			{
				printf("Alamat\t: %s\n", baru->alamat);
			}
			else if (lihatData == 3)
			{
				printf("Kontak\t: %s\n", baru->kontak);
			}
			else if (lihatData == 4)
			{
				printf("No. KTP\t: %s\n", baru->ktp);
			}
			else if (lihatData == 5)
			{
				printf("Bank\t: %s\n", baru->bank);
			}

			printf("\ningin melihat data lain? (1 (ya)/0 (tidak)) >: ");
			scanf("%d", &opsiForm);
		} while (opsiForm != 0);
	}
	else
	{
		printf("\nTekan apa saja untuk kembali!");
		getch();
	}
	if (*formulir == NULL)
	{
		*formulir = baru;
	}
	else
	{
		form *iterator = *formulir;
		while (iterator->next != NULL)
		{
			iterator = iterator->next;
		}
		iterator->next = baru;
	}
}
void booking(form *formulir, Dokter dokter[])
{
	system("cls");
	int i;
	int nomorDokter;
	bool booking;
	const char hari[7][10] = {
		{"Senin"},
		{"Selasa"},
		{"Rabu"},
		{"Kamis"},
		{"Jumat"},
		{"Sabtu"},
		{"Minggu"}};
	do
	{
		printf("\nSilahkan pilih Dokter yang tersedia\n1. Dr. Saburo\n2. Dr. Bineka\n3. Dr. Saskeh\n4. Dr. Lur Bor\n5. Dr. Frutang");
		printf("\nPilih (1/2/3/4/5) >: ");
		scanf("%d", &nomorDokter);

		printf("Hari yang tersedia : ");
		for (i = 0; i < 7; i++)
		{
			if (i != 0)
			{
				printf(", ");
			}
			if (dokter[nomorDokter-1].available[i])
			{
				printf("%s", hari[i]);
			}
		}

	} while (nomorDokter < 1 && nomorDokter > 5);
	

	while (formulir->next != NULL)
	{
		formulir = formulir->next;
	}
	printf("Pilih hari: ");
	scanf(" %101[^\n]s", formulir->jadwal.hari);
	
	if (dokter[nomorDokter-1].available[getIndexFromHari(formulir->jadwal.hari)] == false)
	{
		printf("Jadwal tersebut penuh. Silakan coba yang lain nanti\n");
	}
	else
	{
		strcpy(formulir->jadwal.namaDokter, dokter[nomorDokter-1].nama);

		dokter[nomorDokter-1].available[getIndexFromHari(formulir->jadwal.hari)] = false;
	}
}
int getIndexFromDokter(const char *nama){
	if (!strcmp(nama, "Dr. Saburo")){
		return 0;
	}
	else if (!strcmp(nama, "Dr. Bineka"))
	{
		return 1;
	}
	else if (!strcmp(nama, "Dr. Saskeh"))
	{
		return 2;
	}
	else if (!strcmp(nama, "Dr. Lur Bor"))
	{
		return 3;
	}
	else if (!strcmp(nama, "Dr. Frutang"))
	{
		return 4;
	}
	
}
int getIndexFromHari(const char *hari)
{
	if (!strcmp(hari, "Senin"))
	{
		return 0;
	}
	else if (!strcmp(hari, "Selasa"))
	{
		return 1;
	}
	else if (!strcmp(hari, "Rabu"))
	{
		return 2;
	}
	else if (!strcmp(hari, "Kamis"))
	{
		return 3;
	}
	else if (!strcmp(hari, "Jumat"))
	{
		return 4;
	}
	else if (!strcmp(hari, "Sabtu"))
	{
		return 5;
	}
	else if (!strcmp(hari, "Minggu"))
	{
		return 6;
	}
}
void jadwal_dokter(Dokter dokter[])
{
	system("cls");
	int i, j;
	char checklist[7];

	printf("		==================== Jadwal Dokter Desember 2021 ====================\n\n");
	printf("|      Dokter/Hari      |  Senin  |  Selasa  |  Rabu  |  Kamis  |  Jumat  |  Sabtu  |  Minggu  |\n");
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (dokter[i].available[j])
			{
				checklist[j] = 'v';
			}
			else
			{
				checklist[j] = ' ';
			}
		}
		printf("|%s (%s)     |    %c    |    %c     |    %c   |    %c    |    %c    |    %c    |    %c     |\n",
			   dokter[i].nama,
			   dokter[i].spesialis,
			   checklist[0],
			   checklist[1],
			   checklist[2],
			   checklist[3],
			   checklist[4],
			   checklist[5],
			   checklist[6]);
	}
}
void showFormulir(form *formulir)
{
	while (formulir != NULL)
	{
		printf("\nNama lengkap: %s\n", formulir->namaLengkap);
		printf("Nama panggilan: %s\n", formulir->namaPanggilan);
		printf("Alamat: %s\n", formulir->alamat);
		printf("Kontak: %s\n", formulir->kontak);
		printf("NIK: %s\n", formulir->ktp);
		printf("Bank: %s\n", formulir->bank);
		printf("Umur: %d\n", formulir->umur);
		printf("Reservasi dokter: %s\n", formulir->jadwal.namaDokter);
		printf("Reservasi hari: %s\n\n", formulir->jadwal.hari);
		formulir = formulir->next;
	}
}
