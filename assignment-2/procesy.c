#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
	{	
		printf("Proces potomny\n");
		printf("UID: %d\n", getuid());
		printf("GID: %d\n", getgid());
		printf("PID: %d\n", getpid());
		printf("PPID: %d\n", getppid());
		printf("PGID: %d\n", getpgid(0));
		return 0;
	}
