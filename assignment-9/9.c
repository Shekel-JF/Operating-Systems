#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


pthread_mutex_t lock;
int loaded;

void gotoxy(unsigned x, unsigned y)
{
	printf("\033[%d;%dH\033[2K", y, x);
}

struct my_Struct
{
	int *calls;
	int index;
};

void* Thread_numbers(void* thread_context)
{	
	int i, n;
	struct my_Struct *struct_ptr = (struct my_Struct*) thread_context;

	for(i = 0; i < 3; i++)
	{
		int k =	pthread_mutex_trylock(&lock);
		if(k==0)
		{
			printf("\033[%d;%dH\033[2K Index: %d | Calls: %d", struct_ptr->index, 40, struct_ptr->index, *struct_ptr->calls);
			sleep(1);
			for(n = 0; n < loaded; n++)
			{	
				(*struct_ptr->calls)++;
			}
			pthread_mutex_unlock(&lock);
		}
		else
		{
			i--;
			printf("\033[%d;%dH\033[2K Waiting for an operation", struct_ptr->index, 0);
			sleep(1);
		}
	}
	printf("\033[%d;%dH\033[2K Done!", struct_ptr->index, 0);
	return 0;
}


int main(void)
{
	system("clear");
	printf("Enter the number of function calls that each thread will make\n");
	scanf("%d", &loaded);
	const int total_number_of_threads = 10;
	pthread_t* threads = malloc(sizeof(pthread_t) * total_number_of_threads);
	int calls = 0;
	int n;
	int thread_number = 0;
	struct my_Struct *mystruct_1 = malloc(sizeof(struct my_Struct) * total_number_of_threads);
	pthread_mutex_init(&lock, NULL);
	
	for(n = total_number_of_threads; n > 0; n--)
	{
		mystruct_1[n-1].index = n;
		mystruct_1[n-1].calls = &calls;
		int i = pthread_create(&threads[n-1], NULL, Thread_numbers, &mystruct_1[n-1]);
		if (i == 0)
		{
			thread_number++;
		}
	}
	
	for(n = total_number_of_threads; n > 0; n--)
	{
		pthread_join(threads[n-1], NULL);
	}
	gotoxy(0, total_number_of_threads);
	printf(" Final number of calls to function: %d\n", calls);
	pthread_mutex_destroy(&lock);
	free(threads);
	free(mystruct_1);
	exit(0);
}
