#include <stdio.h>

#include "queue.h"
#include "proc.h"
#include "stats.h"
#include "utils.h"

extern struct queue * ready;
extern struct queue * ready2;
extern struct queue * blocked;
extern struct queue * finished;

extern int MAX_TIME;
extern int QUANTUM;

struct proc * scheduler(struct proc * current)
{
    struct proc *selected;
    struct proc *aux;

    int menor_pid;

    if (current != NULL)
    {
        switch (current->state)
        {
            case READY:

                enqueue(ready, current);

                break;

            case BLOCKED:

                enqueue(blocked, current);

                break;

            case FINISHED:

                enqueue(finished, current);

                break;

            default:

                printf("@@ ERRO no estado do processo %d\n", current->pid);
        }
    }

    if (isempty(ready))
    {
        return NULL;
    }

    aux = ready->head;

    selected = aux;
    menor_pid = aux->pid;

    while (aux != NULL)
    {
        if (aux->remaining_time < selected->remaining_time)
        {
            selected = aux;
            menor_pid = aux->pid;
        }

        aux = aux->next;
    }

    selected = dequeue_bypid(ready, menor_pid);

    selected->state = RUNNING;

    return selected;
}