#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "proc.h"

extern struct queue * ready;
extern struct queue * ready2;
extern struct queue * blocked;
extern struct queue * finished;

struct proc * scheduler(struct proc * current)
{
    struct proc * p = NULL;

    if (current != NULL)
    {
        switch(current->state)
        {
            case READY:
                current->queue = 1;

                enqueue(ready2, current);

                break;

            case BLOCKED:

                current->queue = 0;

                enqueue(blocked, current);

                break;

            case FINISHED:

                enqueue(finished, current);

                break;

            default:

                printf("@@ ERRO estado processo %d\n", current->pid);
        }
    }

    int prob = rand() % 100;

    if (prob < 70)
    {
        if (!isempty(ready))
        {
            p = dequeue(ready);
        }
        else if (!isempty(ready2))
        {
            p = dequeue(ready2);
        }
    }
    else
    {
        if (!isempty(ready2))
        {
            p = dequeue(ready2);
        }
        else if (!isempty(ready))
        {
            p = dequeue(ready);
        }
    }

    if (p != NULL)
    {
        p->state = RUNNING;
    }

    return p;
}