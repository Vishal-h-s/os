#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_KEY 1234
#define MAX_TEXT 512

// Define the message structure
struct message {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    int msgid;
    struct message msg;
    
    // Create the message queue
    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prepare the message to send
    msg.msg_type = 1; // Message type must be a positive number
    strncpy(msg.msg_text, "Hello from sender", MAX_TEXT);

    // Send the message
    if (msgsnd(msgid, &msg, strlen(msg.msg_text) + 1, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Sender: Message sent '%s'\n", msg.msg_text);

    return 0;
}
