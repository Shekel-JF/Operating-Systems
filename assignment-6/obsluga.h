#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

sem_t * otworz_semafor(char *nazwa)
{
    sem_t *semafor = sem_open(nazwa, O_CREAT, 0644, 1);
    if (semafor == SEM_FAILED) 
    {
        perror("Wystapil blad podczas tworzenia/otwierania semaforu");
        exit(1);
    }
    
    return semafor;
}

int stan_semafora(sem_t *adres)
{
    int *wartosc;
    int err = sem_getvalue(adres, wartosc);
    if (err == -1)
    {
        perror("Wystapil blad podczas odczytu wartosci semaforu");
        exit(1);
    }
    
    return *wartosc;
}

void zablokuj(sem_t *adres)
{
    int err = sem_wait(adres);
    if (err == -1)
    {
        perror("Wystapil blad podczas opuszczania semaforu");
        exit(1);
    }
}

void odblokuj(sem_t *adres)
{
    int err = sem_post(adres);
    if (err == -1)
    {
        perror("Wystapil blad podczas podnoszenia semaforu");
        exit(1);
    }
    
}

void zniszcz_semafor(sem_t *adres, char *nazwa)
{
    int err = sem_close(adres);
    if (err == -1)
    {
        perror("Wystapil blad podczas zamykania semaforu");
        exit(1);
    }
    
    err = sem_unlink(nazwa);
    if (err == -1)
    {
        perror("Wystapil blad podczas usuwania semaforu");
        exit(1);
    }
    
}

