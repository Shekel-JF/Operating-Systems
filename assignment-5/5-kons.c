#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void usun_potok()
{
    if (remove("potok") == 0)
		printf("Usunieto potok");
    else
        printf("Wystapil blad przy usuwaniu potoku");
}

int main()
{
	int i = atexit(usun_potok);
    char bufor2[1];
    char plik2[] = "lorem2.txt";
    char info[] = "\nProces potomny odczytal 1 bajt z potoku\n";
    int bajty;
    int plik2_desc = open(plik2, O_WRONLY | O_CREAT, 0644);
    int potok_desc = open("potok", O_RDONLY);
    while((bajty = read(potok_desc, bufor2, 1)) > 0 )
    {
        sleep(rand() % 5);
        bajty = write(1, info, strlen(info));
        bajty = write(plik2_desc, bufor2, 1);
    }
    close(potok_desc);
    close(plik2_desc);

    return 0;
}
