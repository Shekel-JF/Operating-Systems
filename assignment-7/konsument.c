#include <stdio.h>
#include <string.h>
#include "semafory.c"
#include "obsluga.c"

int main()
{
    int fd = otworz_bufor(SHARED_MEMORY);
    sem_t *producent = otworz_semafor("producent", NBUF);
    sem_t *konsument = otworz_semafor("konsument", 0);
    SegmentPD *buffer = mapuj_bufor(fd);
    char element[NELE];

    for(int i=0; i<N; i++)
    {
        opusc(konsument);
        strcpy(element, buffer->tab[buffer->wyjmij]);
        strcpy(buffer->tab[buffer->wyjmij], "puste");
        printf("wyjalem z pozycji %d\n", buffer->wyjmij);
        buffer->wyjmij = (buffer->wyjmij + 1) % NBUF;
        sleep(1);
        podnies(producent);
    }

    munmap(buffer, sizeof(SegmentPD));
    close(fd);
    return 0;
}
