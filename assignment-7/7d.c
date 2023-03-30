#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include "obsluga.c"
#include "semafory.c"
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/wait.h>


void wyjscie()
{
    usun_bufor("buffer");
    usun_semafor("producent");
    usun_semafor("konsument");
}

int main()
{
    int buff = utworz_bufor(SHARED_MEMORY ,sizeof(SegmentPD));
    sem_t *prod_sem = otworz_semafor("producent", NBUF);
    sem_t *cons_sem = otworz_semafor("konsument", 0);
    atexit(wyjscie);

    SegmentPD *buffer = mapuj_bufor(buff);
    buffer->wstaw = 0;
    buffer->wyjmij = 0;
    for(int i=0; i<NBUF; i++)
    {
        strcpy(buffer->tab[i], "puste");
    }

    munmap(buffer, sizeof(SegmentPD));
    close(buff);

    switch (fork())
    { //spawn producenta
        case 0:
            printf("startowanie producenta\n");
            execl("producentd.x", "producentd.x", NULL);
            break;

        default:
            break;
    }

    switch (fork())
    { //spawn konsumenta
        case 0:
            printf("startowanie konsumenta\n");
            execl("konsumentd.x", "konsumentd.x", NULL);
            break;
            
        default:
            break;
    }
    wait(NULL);

    return 0;
}
