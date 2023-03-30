#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "kolejki.h"

mqd_t server;

void intHandler(int dummy)
{
	printf("Closing server [Ctrl+C]\n");
	exit(0);
}

void my_exit()
{
	printf("Cleanin up...\n");
	mq_close(server);
	mq_unlink("/queue");
}

int main(void)
{
	int val1, val2, result;
	char operator;

	char buf[256];
	char result_queue[32];
	struct mq_attr attrs;
	attrs.mq_flags = 0;
	attrs.mq_maxmsg = 10;
	attrs.mq_msgsize = sizeof(buf);
	attrs.mq_curmsgs = 0;

	server = mq_open("/queue", O_CREAT | O_RDONLY, 0777, &attrs);
	if (server == -1)
	{
		printf("Server cannot start properly. Closing.\n");
		return -1;
	}

	signal(SIGINT, intHandler);
	atexit(my_exit);

	int end = 0;
	while (end == 0)
	{
		int received_bytes = mq_receive(server, buf, sizeof(buf), NULL);
		printf("Received new message of [%d] bytes\n", received_bytes);

		struct my_Struct* buf_struct = from_bytes(buf);

		memcpy(result_queue, buf_struct->result_queue, sizeof(result_queue));
		val1 = buf_struct->val1;
		val2 = buf_struct->val2;
		operator = buf_struct->operator;

		printf("Calculating request: %d %c %d...\n", val1, operator, val2);
		switch (operator)
		{
			case '+':
				result = val1 + val2;
				break;

			case '-':
				result = val1 - val2;
				break;

			case '*':
				result = val1 * val2;
				break;

			case '/':
				result = val1 / val2;
				break;
		}

		printf("Sending result to queue: %s\n", result_queue);

		mqd_t client = mq_open(result_queue, O_WRONLY, 0777, &attrs);
		memcpy(buf, &result, 4);
		mq_send(client, buf, sizeof(buf), 0);
		mq_close(client);
	}
	return 0;
}
