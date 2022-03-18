#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#define jmlchar 15

struct film //membuat tipe data baru bernama film
{
    char 	kode[4];
    char 	judul[50];
    char 	genre[50];
    char 	durasi[15];
    char 	sutradara[50];
    char 	ratingusia[10];
    char 	tgl[50];
    char 	jam[15];
    int 	jmlseat;
    int 	harga;
};

struct booking
{
    char 	kode[4]; 			// kode film
    int 	jumlahseat;			// jumlah tempat duduk yang telah dipesan
    int		seat[40]; 			// tempat duduk yang sudah di pesan
};

struct transaksi
{
	char 	kodefilm[4]; 		// kode film
	int 	kodetransaksi;		// kode transaksi
	char 	nama[50]; 			// nama pelanggan
	char 	noHP[14]; 			// nomor hp pelanggan
	int 	jmltiket; 			// jumlah tiket yang dibeli
	char 	seat[20];			// nomor kursi
	int 	harga;				// harga film
	int 	totalharga;			// total yg dibayarkan

};

struct database
{
char name[jmlchar];
char password[jmlchar];
};


struct film datafilm[50]; 			//membuat array bernama datafilm dg tipe data film
struct transaksi datatransaksi[50];
struct booking databooking[50];
struct database;
int countfilm = 50; 				// jumlah film yg tersedia--automatis terupdate (50 adalah jlmh max)
int counttransaksi = 1;
int countbooking = 0;
int array[25][40];

// fungsi prototype
void login();
void getfield(char line[], int recno);
void read_datafile();
void border1();
void border2();
void next(int* a);
void prev(int* a);
void lihat(int i);
void masukpw();
void carifilm();
void belitiket();
void tambahfilm();
void transaksi();
void menuUtama();
void lihatTranskasi();

void login()
{
	system("cls");
    struct database user[5]=
    {
	    {"maulyta.nf","Maulyta"},
	    {"syahrul.toha","Syahrul"},
	    {"r.surya","Surya"},
	    {"renata.p","Renata"},
	    {"alfina.j","Alfina"},
    };

    struct database datalogin;
    int n, i;

    printf("======================================\n");
    printf("\tSELAMAT DATANG DI TIX ID\t\n");
    printf("======================================\n");
    printf("\t*****LOGIN APLIKASI*****\n\n");

   	printf("Enter Username : ");
    scanf("%s",datalogin.name);
    printf("Enter Password : ");
    scanf("%s",datalogin.password);

    for(i=0;i<5;i++)
    {
		if(strcmp(datalogin.name,user[i].name)==0 && strcmp(datalogin.password,user[i].password)==0)
    	{
			printf("============Login Berhasil============\n");
			getch();
			break;

		}

	    else if (i==4)
	    {
			printf("!! Username atau Password Salah !!\n");
			getch();
	    	login();
		}
    }
}


void getfieldfilm(char line[], int recno)
{
    char* token;
    token = strtok(line, ";");
    int fieldno = 0;
    while( token != NULL ) {
        if(fieldno == 0){
            strcpy(datafilm[recno].kode, token);
        } else if(fieldno == 1){
            strcpy(datafilm[recno].judul, token);
        } else if(fieldno == 2){
            strcpy(datafilm[recno].genre, token);
        } else if(fieldno == 3){
            strcpy(datafilm[recno].durasi, token);
        } else if(fieldno == 4){
            strcpy(datafilm[recno].sutradara, token);
        } else if(fieldno == 5){
            strcpy(datafilm[recno].ratingusia, token);
        } else if(fieldno == 6){
            strcpy(datafilm[recno].tgl, token);
        } else if(fieldno == 7){
            strcpy(datafilm[recno].jam, token);
        } else if(fieldno == 8){
            datafilm[recno].jmlseat = atoi(token);
        } else if(fieldno == 9){
            datafilm[recno].harga = atoi(token);
        }
        fieldno++;
        token = strtok(NULL, ";");
    }
}

void getfieldtransaksi(char line[], int recno)
{
    char* token;
    token = strtok(line, ";");
    int fieldno = 0;
    while( token != NULL ) {
        if(fieldno == 0){
            strcpy(datatransaksi[recno].kodefilm, token);
        } else if(fieldno == 1){
            datatransaksi[recno].kodetransaksi = atoi(token);
        } else if(fieldno == 2){
            strcpy(datatransaksi[recno].nama, token);
        } else if(fieldno == 3){
            strcpy(datatransaksi[recno].noHP, token);
        } else if(fieldno == 4){
            datatransaksi[recno].jmltiket = atoi(token);
        } else if(fieldno == 5){
			strcpy(datatransaksi[recno].seat, token);
        } else if(fieldno == 6){
        	datatransaksi[recno].harga = atoi(token);
        } else if(fieldno == 7){
            datatransaksi[recno].totalharga = atoi(token);
        }
        fieldno++;
        token = strtok(NULL, ";");
    }
}

void getfieldbooking(char line[], int recno)
{
    char* token;
    char* tmp;
    token = strtok(line, ";");
    int fieldno = 0;
    int seatnumber = 0;
    while( token != NULL ) {
        if(fieldno == 0){
            strcpy(databooking[recno].kode, token);
        }
		else if(fieldno == 1){
			tmp = strtok(token, ",");
  			while(tmp != NULL){
	  			int x = atoi(tmp);
				databooking[recno].seat[seatnumber] = x;
	    		seatnumber++;
	    		tmp = strtok(NULL,",");
			}
			databooking[recno].jumlahseat = seatnumber;
        }
        fieldno++;
        token = strtok(NULL, ";");
    }

}

void read_datafile(char c[])
{
	if(strcmp(c, "DataFilm.txt") == 0){
		FILE* filePointer = fopen(c, "r");
    	char baris[1024];
    	int recno = 0;
	    while(fgets(baris, 1024, filePointer))
	    {
	        char* tmp = strdup(baris);
	        getfieldfilm(tmp, recno);

	        free(tmp);
	        recno++;
	    }
	    countfilm = recno; // update jumlah film
	    fclose(filePointer) ;
	}
	else if(strcmp(c, "DataTransaksi.txt") == 0){

		FILE* filePointer = fopen(c, "r");
    	char baris[1024];
    	int recno = 0;
	    while(fgets(baris, 1024, filePointer))
	    {
	        char* tmp = strdup(baris);
	        getfieldtransaksi(tmp, recno);

	        free(tmp);
	        recno++;
	    }
	    counttransaksi = recno; // update jumlah transaksi
	    fclose(filePointer) ;
	}

	else if(strcmp(c, "DataBooking.txt") == 0){

		FILE* filePointer = fopen(c, "r");
    	char baris[1024];
    	int recno = 0;
	    while(fgets(baris, 1024, filePointer))
	    {
	        char* tmp = strdup(baris);
	        getfieldbooking(tmp, recno);

	        free(tmp);
	        recno++;
	    }
	    countbooking = recno;
	    fclose(filePointer) ;
	}

	else{
		printf("gagal, data tidak ditemukan. cek penamaan");
	}

}


void border1(){
    printf("\n=======================================================\n");
}

//pembatas menu 2
void border2(){
    printf("\n-------------------------------------------------------\n");
}

void datatidakditemukan(){
	system("cls");
	printf("=============================================\n");
    printf("            FILM (Sedang Tayang)			\n");
    printf("=============================================\n\n");
    printf("	data tidak ditemukan					\n\n");
    printf("---------------------------------------------\n");
    printf("   tekan apa saja untuk kembali ke menu utama\n");
    printf("---------------------------------------------\n");
    printf("Input : ");
    getch();
    menuUtama();
}

void next(int* a)
{
    *a=*a+1;
    lihat(*a);
}

void prev(int* a)
{
    *a=*a-1;
    lihat(*a);
}

void lihat(int i) //fungsi untuk melihat film yang tersedia
{
    checkpoint:
    system("cls");
    read_datafile("DataFilm.txt");
    int lihat;
    printf("=============================================\n");
    printf("            FILM (Sedang Tayang)\n");
    printf("=============================================\n\n");
    printf(" Kode film   : %s \n",datafilm[i].kode);
    printf(" Judul       : %s \n",datafilm[i].judul);
    printf(" Jam         : %s \n",datafilm[i].jam);
    printf(" Jumlah seat : %d \n",datafilm[i].jmlseat);
    printf(" Harga tiket : %d \n",datafilm[i].harga);
    printf("---------------------------------------------\n");
    printf("<1>Previous                           <2>Next\n");
    printf("              <0>Kembali ke menu\n");
    printf("---------------------------------------------\n");
    printf("Input : ");
    scanf("%d",&lihat);
    printf("\n");
    switch (lihat) {
    case 0 :
      menuUtama(); //kembali ke menu utama
      break;
    case 1 :
      if(i <= 0) // jika data diminta kurang dari indeks 0
      	datatidakditemukan();
      else
	  	prev(&i);
      break;
    case 2 :
      if(i >= countfilm - 1) // jika data yang diminta lebih dari jumlah film
        datatidakditemukan();
      else
        next(&i);
      break;
    default: //case untuk input selain yang disediakan
      goto checkpoint; //kembali ke baris untuk memasukkan input menu yang diinginkan
    }
}

void masukpw()
{
	int i=0;
	int a,x;
    char c=' ';
    char pword[10],code[10];
    char pass[10]="admin";

	printf("\t      MASUKKAN PASSWORD: ");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';

	i=0;
	if(strcmp(pword,"admin")==0)
	{
		printf("\n\n\n\t       Password Benar ");
		printf("\n\n\n\nKlik untuk melanjutkan...");
	    getch();
	}
	else
	{
        printf("\n\n\t     !!Password Salah!!\t");
		printf("\n\n  <1>coba lagi       <lainnya>kembali ke menu");
		printf("\n----------------------------------------------\n");

	    printf("Input : ");
	    scanf("%d",&a);
	    if(a==1)
	        masukpw();
	    else
	    	menuUtama();// kembali ke menu utama
	}
}

void carifilm(){
    system("cls");
    char choice[10],location;
    int found=0,pilihan;
    read_datafile("DataFilm.txt");

    border1();
    printf("\t\t        Cari Film ");
    border1();
    printf("\n\t\t   *** Daftar Film *** \n\n");
    for (int i = 0; i < countfilm; i++){
        printf(" < %s > %s \n",datafilm[i].kode,datafilm[i].judul);
    }
    printf("\n\n Input kode film yang ingin anda cari!\n");
    border2();
    printf("input : \t\t\t\t");
    scanf("%s", &choice);

    for (int i = 0; i < countfilm; i++){
        if (strcmp(choice,datafilm[i].kode)==0)
        {
            found=1;
            location=i;
	        system("cls");
	        border1();
	        printf("\t\t         TIX ID ");
	        border1();
	        printf("\n\t\t  *** %s *** \n\n",datafilm[location].judul);
	        printf("Genre       : %s \n",datafilm[location].genre);
	        printf("Durasi      : %s \n",datafilm[location].durasi);
	        printf("sutradara   : %s \n",datafilm[location].sutradara);
	        printf("Rating Usia : %s \n",datafilm[location].ratingusia);
	        border2();
	        printf("Kode Film   : %s \n",datafilm[location].kode);
	        printf("Jadwal      : %s \n",datafilm[location].tgl);
	        printf("Jam         : %s \n",datafilm[location].jam);
	        printf("Sisa Seat   : %d \n",datafilm[location].jmlseat);
	        printf("Harga Tiket : Rp%d \n",datafilm[location].harga);
	        printf("\n\t\t    <1> cari film lagi \n");
	        printf("\t\t    <0> Kembali ke menu \n");
	        border2();
	        printf("input : \t\t\t\t");
	        scanf("%d", &pilihan);
	        switch(pilihan){
		        case 1:
		            carifilm();
		            break;
		        case 0:
		            menuUtama();
		            break;
		        default:
		            do {
		                printf("!! Pilihan yang anda masukkan tidak ada !! ");
		                border1();
		                printf("input : \t\t\t\t");
		                scanf("%d", &pilihan);
	        		}while (pilihan != 0 && pilihan != 1);
	        		if (pilihan==1)
	            		carifilm();
	        		else
						menuUtama();
	        }
        }
    }
    if (found==0){
        printf("!! Pilihan yang anda masukkan tidak ada !! ");
        border1();
		getch();
		carifilm();
    }
}

void belitiket(){
	int pilihan, sisaseat;
    char choice[10],location;
    int found = 0;
	int ketemu = 0;
	int terambil = 0;
    int i,j,n, letakfilm;
    struct transaksi t;
    read_datafile("DataFilm.txt");
    read_datafile("DataTransaksi.txt");
    read_datafile("DataBooking.txt");
    // print menu pemilihan film
    system("cls");
    border1();
    printf("\t\t         TIX ID ");
    border1();
    printf("\n\t\t   *** Daftar Film *** \n\n");
    for (int i = 0; i < countfilm; ++i){
        printf(" < %s > %s \n",datafilm[i].kode,datafilm[i].judul);
    }
    printf("\n\n Input kode film yang ingin anda beli.\n");
    border2();
    printf("input : \t\t\t\t");
    scanf("%s", &choice);
	strcpy(t.kodefilm, choice);
	// tampilkan menu pembelian sesuai kode yang dimasukkan

    for (int i = 0; i < countfilm; ++i){
        if (strcmp(choice,datafilm[i].kode)==0)
        {
        	found=1;
            location=i;
	        system("cls");
	        border1();
	        printf("\t\t         TIX ID ");
	        border1();
	        printf("\n\t\t   *** Beli Tiket *** \n\n");
	        printf("\n\t\t    --------------- \n");
	        printf("\n\t\t     LAYAR BIOSKOP  \n");
	        printf("\n\t\t    --------------- \n");

	        // cari data booking dari film yang dipilih
			for(j = 0; j < countbooking; j++){
        		if(strcmp(choice, databooking[j].kode) == 0){
					// menentukan letak data
					ketemu = 1;
					letakfilm = j;
					for (int k=1;k<=40;k++)
					{
						int ada = 0;

						for(int l = 0; l<databooking[j].jumlahseat; l++){
							if (k == databooking[j].seat[l]){
								ada = 1;
								break;
							}

						}
						if(ada == 1){
							printf("*\t");
							ada = 0;
						}
						else{
							printf("%d\t", k);
						}
						if(k%8==0)
							printf("\n\n");
					}
					sisaseat = 40-databooking[j].jumlahseat;
					printf("\n\t\tSisa seat : %d \n", sisaseat);
					border2();
					break;
				}

			}

			// jika data booking tidak ditemukan
			if(ketemu == 0){
			    for (i=1;i<=40;i++)
				{
					printf("%d\t",i);
					if(i%8==0)
						printf("\n\n");
				}
				sisaseat = datafilm[location].jmlseat;
				printf("\n\t\tSisa seat : %d \n", sisaseat);
				border2();
			}

        }
    }

    // apabila kode yang dimasukan tidak benar
    if (found==0){
        printf("!! Kode film yang Anda masukkan tidak ada !! ");
        getch();
		belitiket(); // kembali ke menu cari film
    }

    // menerima input pesanan tiket apabila kode ditemukan
    fflush(stdin);
    t.kodetransaksi = 1001 + counttransaksi;
    printf("Input Nama Pemesanan : ");
    gets(t.nama);
    printf("Input No. HP : ");
    gets(t.noHP);
    printf("Input Jumlah Tiket : ");
    scanf("%d",&n);
    t.jmltiket = n;
    int seat[n];
    for(i = 1; i <= n; i++){
    	printf("\nPilih No. Seat ke-%d : ",i);
    	int x;
    	scanf("%d", &x);
    	seat[i-1] = x;
	}
	int harga = datafilm[location].harga;
	printf("\nHarga per tiket : Rp. %d", harga);
	t.harga = harga;
	printf("\nTotal Harga : %d",n*harga);
	t.totalharga = harga*n;

	printf("\nLanjutkan Pembelian Tiket? ");

	printf("\n<1>Ya\t <2>Tidak ");
	border2();
	printf("\ninput : ");
	scanf("%d", &pilihan);

	//cek ketersedian tempat duduk jika ada data booking
	if(ketemu == 1){
		for(int i = 0; i< n; i++){
		  for(int l = 0; l<databooking[letakfilm].jumlahseat; l++){
			if (seat[i] == databooking[letakfilm].seat[l]){
				terambil = 1;
				break;
			}
		  }
		}
	}

	if (sisaseat == 0){
		// jik
		system("cls");
		border1();
		printf("\n\t\tMaaf tiket habis. \n\tAnda tidak dapat melanjutkan pemesanan\t");
		printf("\n\tTekan <1> untuk beli tiket");
		printf("\n\tTekan <0> untuk kembali ke menu");
		border2();
		printf("\ninput : ");
		scanf("%d", &pilihan);
		if(pilihan == 1)
		  belitiket();
		else
		  menuUtama();
	}

	else if(terambil == 1){
		//pilihan seat sudah terisi
		system("cls");
		printf("\nMaaf no seat yang anda pilih telah terisi. Silahkan pilih no. seat yang lain");
		getch();
		belitiket(); // kembali ke menu inputan
	}

	else if(pilihan == 1){
		// cek apakah seat yg tersisa cukup
		// kalau sisa seat 0

		// tampilkan tiket
		printf("\n\t\t   Selamat! Anda berhasil membeli tiket \n\n");
		system("cls");
		border1();
		printf("\t\tTIKET\t");
	  	border1();

		printf("\nKode Transaksi : %d", t.kodetransaksi);
		printf("\nNama Pembeli : %s", t.nama);
		printf("\nNo. HP : %s", t.noHP);

		printf("\n\t\t\t %s", datafilm[location].judul);
		printf("\n\t\t\t Jadwal : %s",datafilm[location].tgl);
		printf("\n\t\t\t Jam : %s", datafilm[location].jam);
		printf("\n\t\t\t Jumlah seat : %d", n);
		printf("\n\t\t\t No seat : ");
		for(i = 1; i <= n; i++){
			if(i == n)
				printf("%d", seat[i-1]);
	    	else
	    		printf("%d, ", seat[i-1]);
		}

		printf("\n\t\t\t Total Harga : %d",n*harga);

		// simpan data booking tempat duduk
		FILE* fp=fopen("DataBooking.txt","a");
		FILE* temp=fopen("DataBooking1.txt","a");

		if(fp == NULL)
		{
			printf("FIle not Found");
		}

		else
		{
			found = 0;
			for(j = 0; j < countbooking; j++){
        		if(strcmp(choice, databooking[j].kode) == 0){
        			found = 1;
        			fprintf(temp,"%s;",databooking[j]);
        			for(int k = 0; k < databooking[j].jumlahseat; k++){
        				if(k == databooking[j].jumlahseat - 1)
        					fprintf(temp, "%d", databooking[j].seat[k]);
        				else
        					fprintf(temp, "%d,", databooking[j].seat[k]);
					}

					for(i = 1; i <= n; i++){
				    		fprintf(temp, ",%d", seat[i-1]);
					}

					fprintf(temp, "\n");

        		}

	        	else{
					int batas = databooking[j].jumlahseat;
	        		fprintf(temp,"%s;",databooking[j]);
        			for(int k = 0; k < batas; k++){
        				if(k == batas-1 )
        					fprintf(temp, "%d", databooking[j].seat[k]);
        				else
        					fprintf(temp, "%d,", databooking[j].seat[k]);
					}
					fprintf(temp, "\n");
				}

        	}

        	// jika data tidak ditemukan, tambah data baru
        	if(found == 0){
        		fprintf(temp,"%s;",choice);
					for(i = 1; i <= n; i++){
						if(i == 1)
				    		fprintf(temp, "%d", seat[i-1]);
				    	else
				    		fprintf(temp, ",%d", seat[i-1]);
					}

					fprintf(temp, "\n");
			}

		}
		fclose(fp);
		fclose(temp);
		remove("DataBooking.txt");
		rename("DataBooking1.txt", "DataBooking.txt");
		printf("\n");


		// simpan data transaksi pelanggan
		fp=fopen("DataTransaksi.txt","a");

		if(fp == NULL)
		{
			printf("FIle not Found");
		}

		else
		{
			fprintf(fp,"%s;%d;%s;%s;%d;",t.kodefilm,t.kodetransaksi,t.nama,t.noHP,t.jmltiket);
			for(i = 1; i <= n; i++){
				if(i == n)
					fprintf(fp, "%d", seat[i-1]);
		    	else
		    		fprintf(fp, "%d,", seat[i-1]);
			}
			fprintf(fp, ";%d;%d \n",t.harga, t.totalharga);
		}
		printf("\n");
		fclose(fp);

		border2();
		printf(" Tekan <0> untuk kembali ke menu");
		border2();

		printf("\ninput : ");
		getch();
		menuUtama();
	}

	else{
		system("cls");
		printf("\n\t\tPembelian Tiket Dibatalkan\t");
		printf("\n\tTekan <1> untuk beli tiket");
		printf("\n\tTekan <0> untuk kembali ke menu");
		border2();
		scanf("%d", &pilihan);
		if(pilihan == 1)
		  belitiket();
		else
		  menuUtama();
	}

}

void tambahfilm(){
    system("cls");
    printf("\n==============================================\n");
    printf("\t\tTAMBAH FILM\t");
    printf("\n==============================================\n");
    masukpw();
    struct film f;
    char hrg[7];
    system("cls");
    fflush(stdin);
	printf("\n==============================================\n");
    printf("\t\tTAMBAH FILM\t");
    printf("\n==============================================\n");
	printf("Input kode film : ");
	gets(f.kode);
	printf("Input judul film : ");
	gets(f.judul);
	printf("Input genre film : ");
	gets(f.genre);
	printf("Input sutradara film : ");
	gets(f.sutradara);
	printf("Input rating usia : ");
	gets(f.ratingusia);
	printf("Input tanggal tayang : ");
	gets(f.tgl);
	printf("Input jam tayang : ");
	gets(f.jam);
	printf("Input durasi film : ");
	gets(f.durasi);
	f.jmlseat=40;
	printf("Harga film : ");
	gets(hrg);
	f.harga=atoi(hrg);

    FILE* fp=fopen("DataFilm.txt","a");

	if(fp == NULL)
	{
		printf("FIle not Found");
	}

	else
	{
		fprintf(fp,"%s;%s;%s;%s;%s;%s;%s;%s;%d;%d \n",f.kode,f.judul,f.genre,f.durasi,f.sutradara,f.ratingusia,f.tgl,f.jam,f.jmlseat,f.harga);
		//countfilm = countfilm+1; countfilm sudah automatis terupdate
		printf("\nFilm berhasil ditambahkan!");
	}
		printf("\n");
	fclose(fp);
	printf("\n\n     Klik apa saja untuk kembali ke menu\t ");
		printf("\n----------------------------------------------\n");

    getch();
    system("cls");
    menuUtama();
}

void tampilkantransaksi()
{
  read_datafile("DataTransaksi.txt");
  printf("DATA TRANSAKSI : \n\n");
  for (int i = 0; i < counttransaksi; ++i){
    printf("Kode transaksi : %d\n", datatransaksi[i].kodetransaksi);
    printf("Kode film : %s\n", datatransaksi[i].kodefilm);
    printf("Nama : %s\n", datatransaksi[i].nama);
    printf("No HP : %s\n", datatransaksi[i].noHP);
    printf("Jumlah tiket : %d\n", datatransaksi[i].jmltiket);
    printf("Seat : %s\n", datatransaksi[i].seat);
    printf("Harga tiket: %d\n", datatransaksi[i].harga);
    printf("Harga total: %d\n", datatransaksi[i].totalharga);
    printf("\n\n");
  }

  read_datafile("DataBooking.txt");
  printf("DATA BOOKING : \n\n");
  for (int i = 0; i < countbooking; ++i){
    printf("\nKode film : %s\n",databooking[i].kode);
    printf("Jumlah seat yang telah dipesan : %d\n",databooking[i].jumlahseat);
    printf("Seat : ");
    for(int j = 0; j < databooking[i].jumlahseat; j++){
    	printf("%d,", databooking[i].seat[j]);
	}
	printf("\n");
  }
}
void transaksi()
{
  system("cls");
  printf("\n==============================================\n");
  printf("\t    LIHAT SEMUA TRANSAKSI\t");
  printf("\n==============================================\n");
  masukpw();
  system("cls");
  printf("\n==============================================\n");
  printf("\t    LIHAT SEMUA TRANSAKSI\t");
  printf("\n==============================================\n");

  //masukin fungsi lihat transaksi
  tampilkantransaksi();


  printf("\n\n     Klik apa saja untuk kembali ke menu\t ");
		printf("\n----------------------------------------------\n");

  getch();
  system("cls");
  menuUtama();
}


void menuUtama() //fungsi untuk menampilkan menu utama
{
	system("cls");
    int menu;
    printf("=============================================\n");
    printf("                   TIX ID\n");
    printf("=============================================\n\n");
    printf("                *** MENU ***\n\n");
    printf("<1> Lihat semua film\n");
    printf("<2> Cari film\n");
    printf("<3> Beli tiket\n");
    printf("<4> Tambah film (hanya admin)\n");
    printf("<5> Lihat semua transaksi (hanya admin)\n");
    printf("<0> Exit\n\n");
    printf("---------------------------------------------\n");
    inputs:
    printf("Input : ");
    scanf("%d",&menu);
    printf("\n");
    switch (menu) {
    case 0 :
      exit(0); //keluar dari program
    case 1 :
      lihat(0); //memanggil fungsi untuk melihat semua film
      break;
    case 2 :
      carifilm(); //memanggil fungsi untuk mencari film
      break;
    case 3 :
	  belitiket(); //memanggil fungsi untuk membeli tiket
      break;
    case 4 :
      tambahfilm(); //memanggil fungsi untuk mebambah film
      break;
    case 5 :
      transaksi(); //memanggil fungsi untuk melihat transaksi
      break;
    default: //case untuk input selain yang disediakan
      printf("\n  !! Pilihan yang anda masukkan tidak ada !! \n");
      printf("----------------------------------------------\n");
      goto inputs; //kembali ke baris untuk memasukkan input menu yang diinginkan
    }
}

int main()
{
	login();	// memanggil fungsi login
    menuUtama(); //memanggil fungsi menuUtama
    return 0;
}
