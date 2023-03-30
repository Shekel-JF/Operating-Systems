#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h> 
#include <time.h>

#define N_THREADS 500

bool wpisywanie[N_THREADS];
int numer[N_THREADS];

int maksimum()
{
    int maks = 0;
    for (int i = 0; i < N_THREADS; i++)
    {
        if (maks < numer[i])
        {
            maks = numer[i];
        }
        
    }
    return maks;
    
}

void blokuj(int i)
{
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 5000000L;
    wpisywanie[i] = true;
    numer[i] = maksimum() + 1;
    wpisywanie[i] = false;

    for (int j = 0; j < N_THREADS; j++)
    {
        while(wpisywanie[j])
        {
            nanosleep(&tim, &tim2);
        }

        while(numer[j] != 0 && (numer[j] < numer[i] || (numer[j] == numer[i] && j < i)))
        {
            nanosleep(&tim, &tim2);
        }
    }
}

void odblokuj(int i)
{
    numer[i] = 0;
}

void* Thread_numbers(void *n_watku)
{
    int nr_watku = *(int *)n_watku;
    blokuj(nr_watku);
    // sekcja krytyczna
    printf("Proces o id: %d, numer: %d\n", nr_watku, numer[nr_watku]);
    odblokuj(nr_watku);

}

int main(void)
{
	//system("clear");
	const int total_number_of_threads = N_THREADS;
	pthread_t* threads = malloc(sizeof(pthread_t) * total_number_of_threads);

	int n;
	int thread_number = 0;

    int *nr_watku = malloc(sizeof(int) * N_THREADS);
    for (n = 0; n < N_THREADS; n++)
    {
        numer[n] = 0;
        wpisywanie[n] = false;
    }
    
	for(n = total_number_of_threads; n > 0; n--)
	{
		nr_watku[n-1] = thread_number;
        
        int i = pthread_create(&threads[n-1], NULL, Thread_numbers, &nr_watku[n-1]);
		if (i == 0)
		{
			thread_number++;         
		}
	}
	
	for(n = total_number_of_threads; n > 0; n--)
	{
		pthread_join(threads[n-1], NULL);
	}

	free(threads);
    free(nr_watku);
	exit(0);
}