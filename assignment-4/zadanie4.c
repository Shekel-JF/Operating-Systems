#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{   
    srand(420);
    int desc[2];
    if (pipe(desc) == -1)
    {
        perror("Pipe failed");
        return 1;
    }

    switch(fork())
    {
        case -1:
            perror("Fork failed");
            return 1;
            break;
        
        // proces potomny (konsument)
        case 0:
            close(desc[1]);
            char bufor2[1];
            char plik2[] = "lorem2.txt";
            char info[] = "\nProces potomny odczytal 1 bajt z potoku\n";
            int bajty;
            int plik2_desc = open(plik2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            while((bajty = read(desc[0], bufor2, 1)) > 0 )
            {
                sleep(rand() % 5);
                bajty = write(1, info, strlen(info));
                bajty = write(plik2_desc, bufor2, 1);
            }
            close(desc[0]);
            close(plik2_desc);
            break;
        
        // proces macierzysty (producent)
        default:
            close(desc[0]);
            char bufor1[1];
            char plik1[] = "lorem.txt";
            char info2[] = "\nProces macierzysty odczytal 1 bajt z pliku: ";
            int bajty2;
            int plik1_desc = open(plik1, O_RDONLY);
            
            while((bajty2 = read(plik1_desc, bufor1, 1)) > 0 )
            {
                bajty2 = write(1, info2, strlen(info2));
                bajty2 = write(1, bufor1, 1);
                bajty2 = write(desc[1], bufor1, 1);
                sleep(rand() % 5);
            }
            close(desc[1]);
            close(plik1_desc);
    }

    return 0;
}
