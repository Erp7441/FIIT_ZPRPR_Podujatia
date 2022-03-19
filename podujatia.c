/*

--------------------------------------------------------------------------
|                                Podujatia                               |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

//*---------------------------------------------------- Preprocesor ---------------------------------------------------

// Program bol naprogramovaný v Visual Studio Code s GCC kompilátorom

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VELKOST_BUFFERA 200

void podpis(char const* zadanie, char const* meno, char const* aisID);
void v(FILE** subor, size_t* velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum);
void o(FILE* subor, size_t velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum);
void n(FILE** subor, size_t* velkost, char*** nazvyPodujati, char*** menaAutorov, char*** typPrezentovania, int** casPrezentovania, int** datum);
void s(size_t velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum);
void h(size_t velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum);
void z(size_t* velkost, char*** nazvyPodujati, char*** menaAutorov, char*** typPrezentovania, int** casPrezentovania, int** datum);
void p(size_t* velkost, char*** nazvyPodujati, char*** menaAutorov, char*** typPrezentovania, int** casPrezentovania, int** datum);
void dealokovat2D(char** ptr, int velkost);
void dealokovat1D(void* ptr);

//TODO Ocheckovat vsetky vstupy

int main(){

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char vyber;
    size_t velkost = 0;
    FILE* subor = NULL;
    char** nazvyPodujati = NULL;
    char** menaAutorov = NULL;
    char** typPrezentovania = NULL;
    int* casPrezentovania = NULL;
    int* datum = NULL;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    podpis("Podujatia", "Martin Szabo", "116304");

//*------------------------------------------------------- Menu -------------------------------------------------------

    do{

        //*----------------------------------------------- Inicializácia ----------------------------------------------
        
        printf("\n\n-------------------------------------");
        printf("\n\t\t\t\t    |");
        printf("\nv - Vypis\t\t\t    |");
        printf("\no - Sort\t\t\t    |");
        printf("\nn - Nacitaj\t\t\t    |");
        printf("\ns - Zobraz\t\t\t    |");
        printf("\nh - Histogram\t\t\t    |");
        printf("\nz - Zmazat\t\t\t    |");
        printf("\np - Pridat\t\t\t    |");
        printf("\nk - Exit\t\t\t    |");
        printf("\n\t\t\t\t    |");
        printf("\n-------------------------------------");
        
        printf("\nVolba: ");
        scanf(" %c", &vyber);
        getchar();

        //*---------------------------------------------- Výber možnosti ----------------------------------------------
        
        printf("\n--------------------------------------------------------------------------\n\n");

        switch (vyber){
            case 'v':
                v(&subor, &velkost, nazvyPodujati, menaAutorov, typPrezentovania, casPrezentovania, datum);
                break;
            case 'o':
                o(subor, velkost, nazvyPodujati, menaAutorov, typPrezentovania, casPrezentovania, datum);
                break;
            case 'n':
                n(&subor, &velkost, &nazvyPodujati, &menaAutorov, &typPrezentovania, &casPrezentovania, &datum);
                break;
            case 's':
                s(velkost, nazvyPodujati, menaAutorov, typPrezentovania, casPrezentovania, datum);
                break;
            case 'h':
                h(velkost, nazvyPodujati, menaAutorov, typPrezentovania, casPrezentovania, datum);
                break;
            case 'z':
                z(&velkost, &nazvyPodujati, &menaAutorov, &typPrezentovania, &casPrezentovania, &datum);
                break;
            case 'p':
                p(&velkost, &nazvyPodujati, &menaAutorov, &typPrezentovania, &casPrezentovania, &datum);
                break;
            case 'k':
                if(fclose(subor) == EOF){
                    printf("Chyba pri zatvarani suboru");
                }
                dealokovat2D(nazvyPodujati, velkost);
                dealokovat2D(menaAutorov, velkost);
                dealokovat2D(typPrezentovania, velkost);
                free(casPrezentovania);
                free(datum);
                casPrezentovania = NULL;
                datum = NULL;
                return 0;
            default:
                printf("Chyba: Zly vyber");
                break;
        }
        printf("\n\n--------------------------------------------------------------------------");

    } while (vyber != 'x');
    return 0;
}

int pocetZaznamov(FILE* subor){
    char riadok[VELKOST_BUFFERA];
    int dlzka = 0;
    while(fgets(riadok, VELKOST_BUFFERA, subor)){
        if(strcmp(riadok, "\n") == 0){
            dlzka++;
        }
    }
    dlzka++;
    fseek(subor, 0, SEEK_SET);
    return dlzka; 
}

void vypisPoZnakoch(char* retazec){
    for(size_t i = 0; i < strlen(retazec); i++){
        if(retazec[i] == '\n' || retazec[i] == '#'){ break; }
        printf("%c", retazec[i]);
    }
}

char** alokovat2D(int pocetRiadkov, int velkostRiadka){
    char** ptr = (char**) malloc(pocetRiadkov * sizeof(char*));
    for(int i = 0; i < pocetRiadkov; i++){
        ptr[i] = (char *) calloc(velkostRiadka, sizeof(char));
    }
    return ptr;
}

void dealokovat2D(char** ptr, int velkost){
    for(int i = 0; i < velkost; i++){
        free(ptr[i]);
        ptr[i] = NULL;
    }
    free(ptr);
    ptr = NULL;
}

void podpis(char const* zadanie, char const* meno, char const* aisID){

//*-------------------------------------------------- Dĺžka reťazca ---------------------------------------------------

    // Zistenie dĺžky reťazcov (vhodne keď nechcem použiť char*.h knižnicu)
    size_t dlzkaZadania = 0, dlzkaMena = 0, dlzkaAisID = 0;
    if(zadanie){
        for (size_t i = 0; zadanie[i] != '\0'; i++){
            dlzkaZadania++;
        }
    }
    if(meno){
        for (size_t i = 0; meno[i] != '\0'; i++){
            dlzkaMena++;
        }
    }
    if(aisID){ 
        for (size_t i = 0; aisID[i] != '\0'; i++){
            dlzkaAisID++;
        }
    }

//*----------------------------------------------- Veľkosť ohraničenia ------------------------------------------------

    size_t velkostOhranicenia = 50 + dlzkaZadania + dlzkaMena + dlzkaAisID;
    if(velkostOhranicenia % 2 == 1){velkostOhranicenia++;}
    
    if(dlzkaZadania == 0 && dlzkaMena == 0 && dlzkaAisID == 0){
        printf("Nezadali ste ziadne udaje");
        return;
    }

//*--------------------------------------------------- Vrchný rám -----------------------------------------------------

    for (size_t i = 0; i < velkostOhranicenia; i++){
        printf("-");
    }
    printf("\n");
    
//*----------------------------------------------------- Zadanie ------------------------------------------------------

    if(zadanie && dlzkaZadania > 0){
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++){
            printf(" "); // Do polovičky ohraničenia vypíšeme medzery...
        }
        printf("%s", zadanie); // ...Potom vypíšeme zadanie...
        if(dlzkaZadania % 2 == 1){dlzkaZadania++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++){
            printf(" "); // Následne dopíšeme zvyšné medzery...
        }
        // Na koniec zakončíme riadok
        printf("|\n");
    }

//*------------------------------------------------------- Meno -------------------------------------------------------

    if(meno && dlzkaMena > 0){
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaMena - 1)/2; i++){
            printf(" ");
        }
        printf("%s", meno);
        if(dlzkaMena % 2 == 1){dlzkaMena++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaMena - 1)/2; i++){
            printf(" ");
        }
        printf("|\n");
    }

//*------------------------------------------------------ AIS ID ------------------------------------------------------

    if(aisID && dlzkaAisID > 0){
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaAisID - 1)/2; i++){
            printf(" ");
        }
        printf("%s", aisID);
        if(dlzkaAisID % 2 == 1){dlzkaAisID++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaAisID - 1)/2; i++){
            printf(" ");
        }
        printf("|\n");
    }

//*---------------------------------------------------- Spodný rám ---------------------------------------------------

    for (size_t i = 0; i < velkostOhranicenia; i++){
        printf("-");
    }

    return;    
}

void v(FILE** subor, size_t* velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum){

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char riadok[VELKOST_BUFFERA];
    char zdroj = 'p';

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!*subor){
        *subor = fopen("OrganizaciePodujatia.txt", "r");
        if(!*subor){
            printf("Neotvoreny subor");
            return;
        }
    }

    if(!nazvyPodujati || !menaAutorov || !typPrezentovania || !casPrezentovania || !datum){
        zdroj = 'f';
    }

    if(ftell(*subor) != 0){
        fseek(*subor, 0, SEEK_SET);
    }

//*------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    if(zdroj == 'f'){
        for(size_t i = 0; fgets(riadok, VELKOST_BUFFERA, *subor); i++){
            switch (i){
                case 0:
                    printf("Nazov prispevku: ");
                    break;
                case 1:
                    printf("Mena autorov: ");
                    break;
                case 2:
                    printf("Typ prezentovania: ");
                    break;
                case 3:
                    printf("Cas prezentovania: ");
                    break;
                case 4:
                    printf("Datum: ");
                    break;
                case 5:
                    i = -1; // ked skonci tento case tak sa este prirata I takze -1 + 1 = 0;
                    break;
                default:
                    break;
            }
            printf("%s", riadok);
        }
        printf("\n");
    }

//*-------------------------------------------------- Čítanie z poli --------------------------------------------------

    else if(zdroj == 'p'){
        for(size_t i = 0; i < *velkost; i++){
            printf("Nazov prispevku: ");
            printf("%s", nazvyPodujati[i]);
            printf("Mena autorov: ");
            printf("%s", menaAutorov[i]);
            printf("Typ prezentovania: ");
            printf("%s", typPrezentovania[i]);
            printf("Cas prezentovania: ");
            printf("%d\n", casPrezentovania[i]);
            printf("Datum: ");
            printf("%d\n\n", datum[i]);
        }
    }
}

void o(FILE* subor, size_t velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------
    
    int vstupDatum = 0;
    char zdroj = 'p';

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    scanf("%d", &vstupDatum);

    if(!subor){
        printf("Neotvoreny subor");
        return;
    }
    
    if(!nazvyPodujati || !menaAutorov || !typPrezentovania || !casPrezentovania || !datum){
        zdroj = 'f';
    }

    if(ftell(subor) != 0){
        fseek(subor, 0, SEEK_SET);
    }

//*------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    if(zdroj == 'f'){

        int index = 0;
        char riadok[VELKOST_BUFFERA];
        int velkostPoli = pocetZaznamov(subor);

        char** nazvy = alokovat2D(velkostPoli, 150);
        char** mena =  alokovat2D(velkostPoli, 100);
        char** typy = alokovat2D(velkostPoli, 4);
        int* casy = (int*)calloc(velkostPoli,sizeof(int));
        int* datumy = (int*)calloc(velkostPoli,sizeof(int));

        for(size_t i = 0; fgets(riadok, VELKOST_BUFFERA, subor); i++){
            switch (i){
                case 0:
                    strcpy(nazvy[index], riadok);
                    break;
                case 1:
                    strcpy(mena[index], riadok);
                    break;
                case 2:
                    strcpy(typy[index], riadok);
                    break;
                case 3:
                    casy[index] = atoi(riadok);
                    break;
                case 4:
                    datumy[index] = atoi(riadok);
                    break;
                case 5:
                    i = -1;
                    index++;
                    break;
                default:
                    break;
            }
        }
        for(int i = 0; i < velkostPoli; i++){
            if(datumy[i] == vstupDatum){
                printf("%d\t", casy[i]);
                vypisPoZnakoch(typy[i]);
                printf("\t");
                vypisPoZnakoch(mena[i]);
                printf("\t%s", nazvy[i]);
            }
        }
        dealokovat2D(nazvy, velkost);
        dealokovat2D(mena, velkost);
        dealokovat2D(typy, velkost);
        free(casy);
        free(datumy);
        casy = NULL;
        datumy = NULL;

    }

//*-------------------------------------------------- Čítanie z poli --------------------------------------------------

    else if(zdroj == 'p'){
        for(size_t i = 0; i < velkost; i++){
            if(datum[i] == vstupDatum){
                printf("%d\t", casPrezentovania[i]);
                vypisPoZnakoch(typPrezentovania[i]);
                printf("\t");
                vypisPoZnakoch(menaAutorov[i]);
                printf("\t%s", nazvyPodujati[i]);
            }
        }
    }
}

void n(FILE** subor, size_t* velkost, char*** nazvyPodujati, char*** menaAutorov, char*** typPrezentovania, int** casPrezentovania, int** datum){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------

    char riadok[VELKOST_BUFFERA];
    int index = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!*subor){
        *subor = fopen("OrganizaciePodujatia.txt", "r");
        if(!*subor){
            printf("Neotvoreny subor");
            return;
        }
    }

    if(ftell(*subor) != 0){
        fseek(*subor, 0, SEEK_SET);
    }

    if(*nazvyPodujati || *menaAutorov || *typPrezentovania || *casPrezentovania || *datum){
        dealokovat2D(*nazvyPodujati, *velkost);
        dealokovat2D(*menaAutorov, *velkost);
        dealokovat2D(*typPrezentovania, *velkost);
        free(*casPrezentovania);
        free(*datum);
        *casPrezentovania = NULL;
        *datum = NULL;
    }

    *velkost = pocetZaznamov(*subor);

    *nazvyPodujati = alokovat2D(*velkost, 150);
    *menaAutorov = alokovat2D(*velkost, 100);
    *typPrezentovania = alokovat2D(*velkost, 4);
    *casPrezentovania = (int*)calloc(*velkost, sizeof(int));
    *datum = (int*)calloc(*velkost, sizeof(int));

//*------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    for(size_t i = 0; fgets(riadok, VELKOST_BUFFERA, *subor); i++){
        switch (i){
            case 0:
                strcpy((*nazvyPodujati)[index], riadok);
                break;
            case 1:
                strcpy((*menaAutorov)[index], riadok);
                break;
            case 2:
                strcpy((*typPrezentovania)[index], riadok);
                break;
            case 3:
                (*casPrezentovania)[index] = atoi(riadok);
                break;
            case 4:
                (*datum)[index] = atoi(riadok);
                break;
            case 5:
                i = -1;
                index++;
                break;
            default:
                break;
        }
    }
    printf("Nacitane data");
}

void s(size_t velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------
    
    int vstupDatum = 0;
    char* vstupTyp = (char*)calloc(VELKOST_BUFFERA, sizeof(char));

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    scanf("%d %s", &vstupDatum, vstupTyp);

    if(!nazvyPodujati || !menaAutorov || !typPrezentovania || !casPrezentovania || !datum){
        printf("Polia nie su vytvorene\n");
        return;
    }

//*-------------------------------------------------- Čítanie z poli --------------------------------------------------

    for(size_t i = 0; i < velkost; i++){
        if(datum[i] == vstupDatum){
            if(strncmp(typPrezentovania[i], vstupTyp, 2) == 0) {
                printf("%d\t", casPrezentovania[i]);
                vypisPoZnakoch(menaAutorov[i]);
                printf("\t%s", nazvyPodujati[i]);
            }
        }
    }
}

void h(size_t velkost, char** nazvyPodujati, char** menaAutorov, char** typPrezentovania, int* casPrezentovania, int* datum){
    
//*-------------------------------------------------- Inicializácia ---------------------------------------------------
    
    if(!nazvyPodujati || !menaAutorov || !typPrezentovania || !casPrezentovania || !datum){
        printf("Polia nie su vytvorene");
        return;
    }

//*----------------------------------------------------- Premenné -----------------------------------------------------

    int* UP = (int*)calloc(6, sizeof(int));
    int* UD = (int*)calloc(6, sizeof(int));
    int* PP = (int*)calloc(6, sizeof(int));
    int* PD = (int*)calloc(6, sizeof(int));

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    for(size_t i = 0; i < velkost; i++){ 
        if(casPrezentovania[i] >= 800 && casPrezentovania[i] < 1000){
            if(strncmp(typPrezentovania[i], "UP", 2) == 0) {
                UP[0]++; 
            }
            else if(strncmp(typPrezentovania[i], "UD", 2) == 0) {
                UD[0]++; 
            }
            else if(strncmp(typPrezentovania[i], "PP", 2) == 0){
                PP[0]++; 
            }
            else if(strncmp(typPrezentovania[i], "PD", 2) == 0){
                PD[0]++; 
            }
        }
        else if(casPrezentovania[i] >= 1000 && casPrezentovania[i] < 1200){
            if(strncmp(typPrezentovania[i], "UP", 2) == 0) {
                UP[1]++; 
            }
            else if(strncmp(typPrezentovania[i], "UD", 2) == 0) {
                UD[1]++; 
            }
            else if(strncmp(typPrezentovania[i], "PP", 2) == 0){
                PP[1]++; 
            }
            else if(strncmp(typPrezentovania[i], "PD", 2) == 0){
                PD[1]++; 
            }
        }
        else if(casPrezentovania[i] >= 1200 && casPrezentovania[i] < 1400){
            if(strncmp(typPrezentovania[i], "UP", 2) == 0) {
                UP[2]++; 
            }
            else if(strncmp(typPrezentovania[i], "UD", 2) == 0) {
                UD[2]++; 
            }
            else if(strncmp(typPrezentovania[i], "PP", 2) == 0){
                PP[2]++; 
            }
            else if(strncmp(typPrezentovania[i], "PD", 2) == 0){
                PD[2]++; 
            }
        }
        else if(casPrezentovania[i] >= 1400 && casPrezentovania[i] < 1600){
            if(strncmp(typPrezentovania[i], "UP", 2) == 0) {
                UP[3]++; 
            }
            else if(strncmp(typPrezentovania[i], "UD", 2) == 0) {
                UD[3]++; 
            }
            else if(strncmp(typPrezentovania[i], "PP", 2) == 0){
                PP[3]++; 
            }
            else if(strncmp(typPrezentovania[i], "PD", 2) == 0){
                PD[3]++; 
            }
        }
        else if(casPrezentovania[i] >= 1600 && casPrezentovania[i] < 1800){
            if(strncmp(typPrezentovania[i], "UP", 2) == 0) {
                UP[4]++; 
            }
            else if(strncmp(typPrezentovania[i], "UD", 2) == 0) {
                UD[4]++; 
            }
            else if(strncmp(typPrezentovania[i], "PP", 2) == 0){
                PP[4]++; 
            }
            else if(strncmp(typPrezentovania[i], "PD", 2) == 0){
                PD[4]++; 
            }
        }
        else if(casPrezentovania[i] >= 1800 && casPrezentovania[i] < 2000){
            if(strncmp(typPrezentovania[i], "UP", 2) == 0) {
                UP[5]++; 
            }
            else if(strncmp(typPrezentovania[i], "UD", 2) == 0) {
                UD[5]++; 
            }
            else if(strncmp(typPrezentovania[i], "PP", 2) == 0){
                PP[5]++; 
            }
            else if(strncmp(typPrezentovania[i], "PD", 2) == 0){
                PD[5]++; 
            }
        }
    }

    printf("hodiny\t\t\tUP\tUD\tPP\tPD\n");
    for(int i = 0; i < 6; i++) {
        switch (i){
            case 0:
                printf("08:00 - 09:59 :");
                break;
            case 1:
                printf("10:00 - 11:59 :");
                break;
            case 2:
                printf("12:00 - 13:59 :");
                break;
            case 3:
                printf("14:00 - 15:59 :");
                break;
            case 4:
                printf("16:00 - 17:59 :");
                break;
            case 5:
                printf("18:00 - 19:59 :");
                break;
            default:
                break;
        }
        printf("\t\t%d\t%d\t%d\t%d\n",UP[i], UD[i], PP[i], PD[i]);
    }

}

void z(size_t* velkost, char*** nazvyPodujati, char*** menaAutorov, char*** typPrezentovania, int** casPrezentovania, int** datum){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------

    char vstupNazov[VELKOST_BUFFERA];
    int bZacat = 0;
    size_t pocetZmazanych = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------
        
    if(!nazvyPodujati || !menaAutorov || !typPrezentovania || !casPrezentovania || !datum){
        printf("Polia nie su vytvorene");
        return;
    }

    fgets(vstupNazov, VELKOST_BUFFERA, stdin);

    while(bZacat != -1){        
        for (size_t i = 0; i < *velkost; i++){
            if(i+1 == *velkost && bZacat == 0){
                bZacat = -1;
                break;
            }
            if(strcmp((*nazvyPodujati)[i], vstupNazov) == 0){ bZacat = 1; }
            if(bZacat == 1 && i < *velkost - 1){
                strcpy((*nazvyPodujati)[i], (*nazvyPodujati)[i + 1]);
                strcpy((*menaAutorov)[i], (*menaAutorov)[i + 1]);
                strcpy((*typPrezentovania)[i], (*typPrezentovania)[i + 1]);
                (*casPrezentovania)[i] = (*casPrezentovania)[i + 1];
                (*datum)[i] = (*datum)[i + 1];
            }
        }

        if(bZacat == 1){
            (*velkost)--;
            *nazvyPodujati = (char**)realloc(*nazvyPodujati, (*velkost) * sizeof(char*));
            *menaAutorov = (char**)realloc(*menaAutorov, (*velkost) * sizeof(char*));
            *typPrezentovania = (char**)realloc(*typPrezentovania, (*velkost) * sizeof(char*));
            *casPrezentovania = (int*)realloc(*casPrezentovania, (*velkost) * sizeof(int));
            *datum = (int*)realloc(*datum, (*velkost) * sizeof(int));
            pocetZmazanych++;
            bZacat = 0;
        }
    }
    printf("Vymazalo sa : %ld zaznamov !\n", pocetZmazanych);
}

void p(size_t* velkost, char*** nazvyPodujati, char*** menaAutorov, char*** typPrezentovania, int** casPrezentovania, int** datum){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------

    char vstupNazov[VELKOST_BUFFERA];
    char vstupMeno[VELKOST_BUFFERA];
    char vstupTyp[VELKOST_BUFFERA];
    char vstupCas[VELKOST_BUFFERA];
    char vstupDatum[VELKOST_BUFFERA];

//*-------------------------------------------------- Inicializácia ---------------------------------------------------
    
    if(!nazvyPodujati || !menaAutorov || !typPrezentovania || !casPrezentovania || !datum){
        printf("Polia nie su vytvorene");
        return;
    }

    fgets(vstupNazov, VELKOST_BUFFERA, stdin);
    fgets(vstupMeno, VELKOST_BUFFERA, stdin);
    fgets(vstupTyp, VELKOST_BUFFERA, stdin);
    fgets(vstupCas, VELKOST_BUFFERA, stdin);
    fgets(vstupDatum, VELKOST_BUFFERA, stdin);

    (*velkost)++;
    *nazvyPodujati = (char**)realloc(*nazvyPodujati, (*velkost) * sizeof(char*));
    *menaAutorov = (char**)realloc(*menaAutorov, (*velkost) * sizeof(char*));
    *typPrezentovania = (char**)realloc(*typPrezentovania, (*velkost) * sizeof(char*));
    *casPrezentovania = (int*)realloc(*casPrezentovania, (*velkost) * sizeof(int));
    *datum = (int*)realloc(*datum, (*velkost) * sizeof(int));

    (*nazvyPodujati)[(*velkost)-1] = (char *) calloc(150, sizeof(char));
    (*menaAutorov)[(*velkost)-1] = (char *) calloc(100, sizeof(char));
    (*typPrezentovania)[(*velkost)-1] = (char *) calloc(4, sizeof(char));

//*------------------------------------------------- Pridanie do poli -------------------------------------------------

    strncpy((*nazvyPodujati)[(*velkost)-1], vstupNazov, 150);
    strncpy((*menaAutorov)[(*velkost)-1], vstupMeno, 100);
    strncpy((*typPrezentovania)[(*velkost)-1], vstupTyp, 4);
    (*casPrezentovania)[(*velkost)-1] = atoi(vstupCas);
    (*datum)[(*velkost)-1] = atoi(vstupDatum);

    printf("Zaznam sa podarilo pridat.");
}
