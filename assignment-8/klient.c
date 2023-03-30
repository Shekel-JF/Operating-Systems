#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include "kolejki.h"
#include <errno.h>
#include <string.h>


int main()
{
	int val1, val2;
	char operator;
	printf("Enter an operation: ");
	scanf("%d %c %d", &val1, &operator, &val2);
	struct mq_attr attrs;
	attrs.mq_flags = 0;
	attrs.mq_maxmsg = 10;
	attrs.mq_msgsize = 256;
	attrs.mq_curmsgs = 0;

	struct my_Struct mystruct_1;
	mystruct_1.val1 = val1;
	mystruct_1.val2 = val2;
	mystruct_1.operator = operator;
	sprintf(mystruct_1.result_queue, "/%d", getpid());

	const char* bytes = to_bytes(&mystruct_1);

	mqd_t client = mq_open(mystruct_1.result_queue, O_CREAT | O_RDONLY, 0777, &attrs);
	mqd_t server = mq_open("/queue", O_WRONLY, 0777, &attrs);

	char buf[256];
	memcpy(buf, bytes, sizeof(struct my_Struct));

	mq_send(server, buf, sizeof(buf), 0);
	int received_bytes = mq_receive(client, buf, sizeof(buf), NULL);
	printf("Received result with [%d] bytes...\n", received_bytes);
	int* server_result = (int*)buf;
	printf("Result: %d\n", *server_result);
	mq_close(client);

	mq_close(server);
	mq_unlink(mystruct_1.result_queue);
}
