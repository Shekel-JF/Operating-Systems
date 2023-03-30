#include <stdio.h>
#include <string.h>
#include "obsluga.c"
#include "semafory.c"


int main()
{
    int fd = otworz_bufor(SHARED_MEMORY);
    sem_t *producent = otworz_semafor("producent", NBUF);
    sem_t *konsument = otworz_semafor("konsument", 0);
    SegmentPD *buffer = mapuj_bufor(fd);

    for(int i=0; i<N; i++)
    {
        opusc(producent);
        strcpy(buffer->tab[buffer->wstaw], "produkt");
        printf("wstawilem na pozycje %d\n", buffer->wstaw);
        buffer->wstaw = (buffer->wstaw + 1) % NBUF;
        sleep(1);
        podnies(konsument);
    }

    munmap(buffer, sizeof(SegmentPD));
    close(fd);
    return 0;
}
