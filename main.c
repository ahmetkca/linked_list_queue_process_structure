#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 256

typedef struct proc {
    char name[MAX_LENGTH];
    int priority;
    int pid;
    int runtime;
} proc_t;

typedef struct node {
    proc_t *process;
    struct node *next;
} node_t;

node_t *head = NULL;

struct node *push(proc_t *process);
struct proc *pop();
struct proc *delete_by_name(char *name);
struct proc *delete_by_pid(int pid);
bool is_head(struct node *n);
void display_process(const struct proc * pro);

int main(int argc, char **argv)
{
    char buffer[MAX_LENGTH];
    FILE *fd = fopen("processes.txt", "r");
    while (fgets(buffer, MAX_LENGTH, fd) != NULL ) {
        // printf("%s\n", buffer);
        char *token = strtok(buffer, ",");
        proc_t *pro = (struct proc *) malloc(sizeof(struct proc));
        int i = 0;
        while (token != NULL && i >= 0 && i < 4) {
            if (i == 0) {
                memset(&pro->name[0], 0, MAX_LENGTH);
                strncpy(pro->name, token, MAX_LENGTH);
            } else if (i == 1) {
                pro->priority = atoi(token);
            } else if (i == 2) {
                pro->pid = atoi(token);
            } else if (i == 3) {
                pro->runtime = atoi(token);
            }
            token = strtok(NULL, ",");
            i++;
        }
        memset(&buffer[0], 0, sizeof(buffer));
        push(pro);
    }

//    printf("Pop first pushed element\n");
//    proc_t *pop1 = pop();
//    display_process(pop1);
//    free(pop1);
//
//    printf("Remove node by process name\n");
//    proc_t *del1 = delete_by_name("processA");
//    display_process(del1);
//    free(del1);
//
//    printf("Remove node by process name\n");
//    proc_t *del2 = delete_by_name("processE");
//    if (del2 != NULL) {
//        display_process(del2);
//        free(del2);
//    }
//
//    printf("Remove node by process name\n");
//    proc_t *del3 = delete_by_name("vscode");
//    display_process(del3);
//    free(del3);

    node_t *curr_node = head;
    int i = 0;
    while (curr_node) {
        printf("Process #%d\n", i);
        display_process(curr_node->process);
        curr_node = curr_node->next;
        i++;
    }

    printf("Remove each process from queue by using pop\n");
    proc_t *p;
    while ((p = pop()) != NULL) {
        display_process(p);
        free(p);
    }

    return 0;
}

void display_process(const proc_t *pro) {
    printf("\tName: %s\n", pro->name);
    printf("\tPriority: %d\n", pro->priority);
    printf("\tPid: %d\n", pro->pid);
    printf("\tRuntime: %d\n", pro->runtime);
    printf("\n");
}

struct node *push(proc_t *process)
{
    if (!head) {
        /* head is not allocated a memory */
        head = (struct node *) malloc(sizeof(struct node));
        if (!head)
            return NULL;
        head->process = process;
        head->next = NULL;
        return head;
    }
    node_t *tmp_node = head;
    while (tmp_node && tmp_node->next) {
        tmp_node = tmp_node->next;
    }
    node_t *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->process = process;
    new_node->next = NULL;
    tmp_node->next = new_node;
    return new_node;    
}

struct proc *pop() {
    if (!head) /* head is not initialized and allocated memeory in the heap yet */
        return NULL;
    
    if (head && !head->next) {
        proc_t *pro = (struct proc *) malloc(sizeof(struct proc));
        memcpy(pro, head->process, sizeof(struct proc));
        free(head->process);
        free(head);
        head = NULL;
        return pro;
    }


    proc_t *pro = (struct proc *) malloc(sizeof(struct proc));
    memcpy(pro, head->process, sizeof(struct proc));
    node_t *tmp = head;
    head = head->next;
    free(tmp->process);
    free(tmp);
    return pro;
}

struct proc *delete_by_name(char *name) {
    node_t *curr_node = head;
    node_t *prev_node = NULL;
    bool found = false;
    while(curr_node) {
        if (strcmp(curr_node->process->name, name) == 0) {
            found = true;
            break;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    if (!found) {
        return NULL;
    }

    proc_t *pro = (struct proc *) malloc(sizeof(struct proc));
    memcpy(pro, curr_node->process, sizeof(struct proc));
    node_t *next_node = curr_node->next;
    if (prev_node == NULL) {
        head = next_node;
    } else {
        prev_node->next = next_node;
    }
    free(curr_node->process);
    free(curr_node);
    return pro;


}

bool is_head(struct node *n) {
    if (n == NULL || head == NULL)
        return false;
    if (n == head)
        return true;
    return false;
}