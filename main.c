#include <stdio.h>
#include <stdlib.h>

typedef struct proc {
    char name[256];
    int priority;
    int pid;
    int runtime;
} proc_t;

typedef struct node {
    proc_t *process;
    struct node *next;
} node_t;

node_t *head = NULL;

void push(const proc_t *process);

int main(int argc, char **argv)
{
    head = (node_t *) malloc(sizeof(node_t));
    if (head == NULL) {
        return 1;
    }


    return 0;
}

void push(const proc_t *process)
{
    if (!head->next && !head->process) {
        /* memory has been allocated for head but no process or next node initialized */
        head->process
    }
}