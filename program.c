#include <stdio.h>
#include <string.h>
#include <time.h>
struct Data{
        char nim[30];
        char noKomputer[50];
};
void Daftar_Status(){
        system("cls");
        FILE *komputer = fopen("komputer.txt", "r");
        const char pemisah[] = "; ";
        char *token;
        int i;

        if(komputer != NULL)
        {
            char baris[30];
            printf("+---------------------------------------+\n");
            printf("|------ DAFTAR DAN STATUS KOMPUTER -----|\n");
            printf("+---------------------------------------+\n");
            printf("+----------------+----------------------+\n");
            printf("|  No. Komputer  |        Status        |\n");
            printf("+----------------+----------------------+\n");
            while(fgets(baris, sizeof baris, komputer) != NULL)
            {
                token = strtok(baris, pemisah);
                for(i = 0; i < 2; i++)
                {
                    if(i == 0)
                    {
                        printf("|\t%s\t |  ", token);
                        token = strtok(NULL, pemisah);
                    }
                    else {
                        if(atoi(token) == 0){
                            printf("\tTidak Aktif\t|\n");
                        }else if(atoi(token) == 1){
                            printf("\t  Aktif \t|\n");
                        }
                    }
                }
            }
            printf("+----------------+----------------------+\n");
            fclose(komputer);
        }
        else
        {
            perror("komputer.txt");
        }
        printf("\n Tekan tombol apapun untuk kembali ke Menu . . . ");
        getch();
        main();
}
void Tambah_Peminjam(){
        system("cls");
        struct Data data;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char b;
        const char pemisah[] = "; ";
        printf("+-------------------------------------------------------+\n");
        printf("|--------------- TAMBAH DATA PEMINJAMAN ----------------|\n");
        printf("+-------------------------------------------------------+\n");
        printf(" NIM\t\t: "); scanf("%s", data.nim);
        printf(" No Komputer\t: "); scanf("%s", data.noKomputer);
        printf(" Jam Mulai\t: %d:%d\n", tm.tm_hour, tm.tm_min);
        printf(" Jam Selesai\t: %d:%d\n", tm.tm_hour+1, tm.tm_min);

        FILE *peminjam = fopen("peminjam.txt", "a");
        if(peminjam == NULL) {
            printf("\n Gagal Membuka File");
        }
        fprintf(peminjam, "%s; %s; %d:%d; %d:%d \n", data.nim, data.noKomputer, tm.tm_hour, tm.tm_min, tm.tm_hour+1, tm.tm_min);
        fclose(peminjam);

        FILE *komputer = fopen("komputer.txt", "r");
        FILE *temp = fopen("temporary.txt","w");

        if (komputer == NULL || temp == NULL) {
            printf("\n Gagal Membuka File");
        }
        char *token;
        char baris[50];
        char tempBaris[50];
        while((fgets(baris, sizeof baris, komputer)) != NULL)
        {
            strcpy(tempBaris, baris);
            token = strtok(baris, pemisah);
            if(strcmp(token, data.noKomputer) == 0)
            {
                fputs(token, temp);
                fputs("; 1\n", temp);
            }
            else {
                fputs(tempBaris, temp);
            }
        }

        fclose(komputer);
        fclose(temp);

        remove("komputer.txt");
        rename("temporary.txt", "komputer.txt");

        printf("\n Sukses tambah Peminjam!");
        getch();

        printf("\n\n Tekan tombol apapun untuk kembali ke Menu . . . ");
        getch();
        main();
}
void Data_Peminjam(){
        system("cls");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        struct Data data;
        FILE *peminjam = fopen("peminjam.txt", "r");
        const char pemisah[] = "; ";
        char *token;
        char c;
        int i;
        int j = 1;

        if(peminjam != NULL)
        {
            char baris[50];
            printf("+-----------------------------------------------------------------------+\n");
            printf("|---------------------- DATA PEMINJAMAN KOMPUTER -----------------------|\n");
            printf("+-------------------------------------------------------+---------------+\n");
            printf("+-------+---------------+----------------+--------------+---------------+\n");
            printf("|  No.  |  NIM          |  No. Komputer  |  Jam Mulai   |  Jam Selesai  |\n");
            printf("+-------+---------------+----------------+--------------+---------------+\n");
            while(fgets(baris, sizeof baris, peminjam) != NULL)
            {
                token = strtok(baris, pemisah);

                printf("|  %d.\t|  ", j);
                for(i = 0; i < 4; i++)
                {
                    if(i == 0) {
                        printf("%s\t|  ", token);
                        token = strtok(NULL, pemisah);
                    }
                    else if(i == 1) {
                        printf("%s\t\t | ", token);
                        token = strtok(NULL, pemisah);
                    }
                    else if(i == 2){
                        printf("%s\t|  ", token);
                        token = strtok(NULL, pemisah);
                    }
                    else{
                        printf("%s\t|\n", token);
                        token = strtok(NULL, pemisah);
                    }
                }
                j++;
            }
            printf("+-------+---------------+----------------+--------------+---------------+\n");
            fclose(peminjam);
        }
        else
        {
            printf("\n Tidak ada Data Peminjaman, Silakan Tambah Data terlebih dahulu.\n");
        }

        printf("\n Tekan tombol apapun untuk kembali ke Menu . . . ");
        getch();
        main();
}
void Keluar(){
    system("cls");
        printf("\n ----- Program ini dirancang oleh -----\n\n");
        printf(" Rachma Adzima Maulida     (1910511024)\n");
        printf("\n Kelas\t\t: D\n");
        printf(" Mata Kuliah\t: Dasar Pemrograman");
        printf("\n\n Terima Kasih...\n");
}
int main()
{
	int answer = 0;
    system("cls");
    printf("+---------------------------------------+\n");
    printf("|----- PROGRAM PEMINJAMAN KOMPUTER -----|\n");
    printf("|----------- DI PERPUSTAKAAN -----------|\n");
    printf("+---------------------------------------+\n");
    printf("|  1. Daftar dan Status Komputer        |\n");
    printf("|  2. Tambah Peminjam                   |\n");
    printf("|  3. Data Peminjam                     |\n");
    printf("|  4. Keluar                            |\n");
    printf("+---------------------------------------+\n");
    main:
    printf("  Masukkan Pilihan [1..4] : ");
    scanf("%d", &answer);
    printf("\n");

    switch(answer){
    case 1:
        Daftar_Status();
    break;
    case 2:
        Tambah_Peminjam();
    break;
    case 3:
        Data_Peminjam();
    break;
    case 4:
        Keluar();
    break;
    default:
        printf("  Pilihan yang Anda Masukan Salah, Silakan Ulangi.\n\n");
        goto main;
    }
    return 0;
}
