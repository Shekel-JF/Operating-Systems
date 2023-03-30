#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

#define NBUF 5
#define NELE 20
#define N 15
#define SHARED_MEMORY "/buffer"

typedef struct
{
    char tab[NBUF][NELE];
    int wstaw, wyjmij;
}
SegmentPD;


int otworz_bufor(const char *name)
{
    int buff = shm_open(name, O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (buff == -1)
    {
        perror("Blad podczas tworzenia bufora");
        return -1;
    };
    return buff;
}

int utworz_bufor(const char *name, off_t len)
{
    int buff = shm_open(name, O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (buff == -1)
    {
        perror("Blad podczas tworzenia bufora");
        return -1;
    };
    if (ftruncate(buff, len) != 0)
    {
        perror("Blad podczas ustawiania rozmiaru bufora");
        return -1;
    };
    return buff;
}

int usun_bufor(const char *name)
{
    if (shm_unlink(name) != 0){
        perror("Blad podczas zwalniania bufora");
        return -1;
    }
    return 0;
}

SegmentPD *mapuj_bufor(int fd)
{
    return (SegmentPD *) mmap(NULL, sizeof(SegmentPD), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
}
