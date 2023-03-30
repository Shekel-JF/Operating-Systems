#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main()
{
 
    char plik1[] = "lorem.txt";
    char info2[] = "\nProces macierzysty odczytal 1 bajt z pliku: ";
    int bajty2;
    char bufor1[1];
    int plik1_desc = open(plik1, O_RDONLY);
    int potok_desc = open("potok", O_WRONLY);

    while((bajty2 = read(plik1_desc, bufor1, 1)) > 0 )
    {
        bajty2 = write(1, info2, strlen(info2));
        bajty2 = write(1, bufor1, 1);
        bajty2 = write(potok_desc, bufor1, 1);
        sleep(rand() % 5);

    }
    close(potok_desc);
    close(plik1_desc);
    return 0;
}