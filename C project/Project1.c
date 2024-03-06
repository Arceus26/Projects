#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    while (1 == 1) {
        system("cls");

        printf("---MENIU PRINCIPAL---\n");
        printf("1. Vizualizare carduri\n");
        printf("2. Adaugare carduri\n");
        printf("3. Stergere carduri\n");
        printf("4. Iesire\n ");

        int mod;
        do {
            printf("\n");
            printf("Introduceti varianta dorita: ");
            scanf("%d",&mod);
        } while (mod < 1 || mod > 4);

        system("cls");



        if (mod == 1) {


        printf("      ---Vizualizare carduri---\n");

struct datecard {
char nrcard[20];
char exp[10];
char prenume[20];
char nume[20];
}contacte[100];

FILE *fl = fopen("mmm.txt", "r");
if(fl == NULL) {
    printf("Nu sa putut deschide fisierul");
    exit(1);
}
int nrdate;
fscanf(fl, "%d", &nrdate);
printf("\n");
printf("--- Numarul total de carduri este %d ---\n",nrdate);
printf("\n");
fgetc(fl);

for(int i=0;i<nrdate;++i) {
    fgets(contacte[i].nrcard, 20, fl);
    fgets(contacte[i].exp, 10, fl);
    fgets(contacte[i].prenume, 20, fl);
    fgets(contacte[i].nume, 20, fl);
}
int j=1;
while(j<=nrdate) {


for(int i=0;i<nrdate;i++) {
    printf("\n%d.Numar card: %s",j,contacte[i].nrcard);
    printf("Data expirarii: %s",contacte[i].exp);
    printf("Prenume: %s",contacte[i].prenume);
    printf("Nume: %s",contacte[i].nume);
    j++;
    }
}
printf("\n");
fclose(fl);
printf("\n");
            system("pause");
}



    else if (mod == 2) {


        printf("     ---Agaugare carduri---\n");
        printf("Introduceti numarul noului card:\n");
        long long nrrr;
        scanf("%lld",&nrrr);
        printf("Introduceti data expirarii cardului:\n");
        int luna,an;
        scanf("%d",&luna);
        scanf("%d",&an);
        printf("Introduceti numele si prenumele detinatorului cardului:\n");
        char nume[100],prenume[100];
        scanf("%s",&prenume);
        scanf("%s",&nume);

        FILE *fwrite = fopen("mmm.txt", "a");
        if(fwrite == NULL) {
            printf("\nNu sa putut deschide fisierul.\n");
        }
        else {
            fprintf(fwrite,"\n");
            fprintf(fwrite ,"%lld\n",nrrr);
            fprintf(fwrite ,"%d/%d\n",luna,an);
            fprintf(fwrite ,"%s\n",prenume);
            fprintf(fwrite ,"%s",nume);

            fclose(fwrite);

            FILE *nr;
            int numar;

            nr = fopen("mmm.txt", "r+");
            if(nr == NULL) {
                printf("Nu sa putut deschide fisierul");
                exit(1);
                }
            fscanf(nr, "%d",&numar);
            numar++;

            fseek(nr, 0, SEEK_SET);
            fprintf(nr, "%d",numar);

            fclose(nr);
        }

            printf("Cardul a fost salvat cu succes!\n");

            system("pause");

        }



        else if(mod == 3) {


FILE *nr;
    int numar;

        nr = fopen("mmm.txt", "r+");
        if(nr == NULL) {
            printf("\nNu sa putut deschide fisierul");
            exit(1);
        }
        fscanf(nr, "%d",&numar);

fclose(nr);



FILE *fmm = fopen("mmm.txt", "r");
char ch;
if(fmm == NULL) {
    printf("\nNu sa putut deschide fisierul");
    exit(1);
}

while ((ch = fgetc(fmm)) != EOF) {
        printf("%c", ch);
    }


fclose(fmm);

FILE *fs,*fn;
char line[256];
int line_no = 1;
int delete[4];
int num_delete_lines = 4;

fs = fopen("mmm.txt", "r");

if(fs == NULL) {
    printf("\nNu sa putut deschide fisierul");
    exit(1);
}

fn = fopen("temp.txt", "w");

if(fn == NULL) {
    printf("\nNu sa putut deschide fisierul");
    exit(1);
}
    int alg,i=0,k;
    printf("\n");
    printf("\nAlegeti cardurile care doriti sa le stergeti:\n");
    scanf("%d",&alg);

for(k=(alg*4)-4+2;k<=(alg*4)+1;k++) {
        delete[i] = k;
        i++;
    }

while(fgets(line,sizeof(line),fs)) {
    int delete_line = 0;
    for(int i=0;i<num_delete_lines;i++) {
            if(line_no == delete[i]) {
                delete_line = 1;
                break;
    }
}

    if(delete_line == 0) {
        fputs(line,fn);
    }
    line_no++;
}

    if(numar == alg) {

long pos = ftell(fn);

fseek(fn, pos - 2, SEEK_SET);

ftruncate(fileno(fn), pos - 2);
    }

    fclose(fs);
    fclose(fn);

    remove("mmm.txt");
    rename("temp.txt", "mmm.txt");


    FILE *nrr;
    int numarr;

        nrr = fopen("mmm.txt", "r+");
        if(nrr == NULL) {
            printf("Nu sa putut deschide fisierul");
            exit(1);
        }
        fscanf(nrr, "%d",&numarr);


    numarr--;

    fseek(nrr, 0, SEEK_SET);
    fprintf(nrr, "%d",numarr);

    fclose(nrr);

    printf("Cardul a fost sters cu succes!!!\n");

    system("pause");

}


    else if (mod == 4) {
            return 0;
        }
    }
return 0;
}
