#include <stdio.h>
#include <stdlib.h>

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
    struct proc * selected;

    int prob;

    if (current != NULL)
    {
        switch (current->state)
        {
            case READY:
                if (current->queue == 0)
                {
                    enqueue(ready, current);
                }
                else
                {
                    enqueue(ready2, current);
                }

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

    if (isempty(ready) && isempty(ready2))
    {
        return NULL;
    }

    prob = rand() % 100;

    if (prob < 70)
    {
        if (!isempty(ready))
        {
            selected = dequeue(ready);
        }
        else
        {
            selected = dequeue(ready2);
        }
    }
    else
    {
        if (!isempty(ready2))
        {
            selected = dequeue(ready2);
        }
        else
        {
            selected = dequeue(ready);
        }
    }
    selected->state = RUNNING;

    return selected;
}