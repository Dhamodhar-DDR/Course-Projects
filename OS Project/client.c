// Lab11 MsgQ Tx process
// Compilation of this file
// gcc -o edu_client client.c -lrt
// To exit the programs use command EXIT 0 on the terminal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

#define RX_QUEUE_NAME   "/xmy_msgq_rx"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE sizeof(my_msg_t)
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE * MAX_MESSAGES) 


#define MSG_VAL_LEN  16

typedef struct{
    char function[MSG_VAL_LEN];
    char args[MSG_VAL_LEN];
} my_msg_t;
static my_msg_t tx_msg;


int main (int argc, char **argv)
{
    mqd_t qd_rx;
    int num = 1;

    printf("Enter the commands:\n");

    if ((qd_rx = mq_open (RX_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Msq Tx: mq_open (qd_rx)");
        exit (1);
    }

    my_msg_t out_msg;

    while (1) {
        char function[30];
        char args[100];
        
        scanf("%s %s",function,args);
        
        strcpy(out_msg.function, function);
	    strcpy (out_msg.args, args);
        
        // send message to message queue
        if (mq_send (qd_rx, (char *) &out_msg, sizeof(out_msg), 0) == -1) {
            perror ("Edu Client: Not able to send message to the queue /my_msgq_rx");
            continue;
        }
        printf ("%d: Edu Client: Message sent successfully\n", num);

        if(strcmp(function,"EXIT") == 0) break;
        num++;
    }

    if (mq_close (qd_rx) == -1) {
        perror ("Client: mq_close");
        exit (1);
    }

    printf ("Client: bye\n");

    exit (0);
}
