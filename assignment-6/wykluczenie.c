#include "obsluga.h"

int main() {
    sem_t *adres = otworz_semafor("/semafor");
    int i;
    // czesc wlasna programu
    printf("Program nie pracuje na wspoldzielonych zasobach");
    // czesc krytyczna programu
    zablokuj(adres);
    printf("Program  PRACUJE na wspoldzielonych zasobach");

    FILE *plik = fopen("numer.txt", "r"); 
    fscanf(plik, "%d", &i); 
    i = i + 1;
    sleep(rand()% 5);
    fclose(plik);
    plik = fopen("numer.txt", "w"); 
    fprintf(plik, "%d", i);
    fclose(plik);
    odblokuj(adres);
    //
    printf("Program nie pracuje na wspoldzielonych zasobach");
    _exit(0);
}
