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
        if (current->state == READY)
        {
            current->queue = 0;
            enqueue(ready, current);
        }
        else if (current->state == BLOCKED)
        {
            current->queue = 1;
            enqueue(blocked, current);
        }
        else if (current->state == FINISHED)
        {
            enqueue(finished, current);
        }
    }

    int prob = rand() % 100;

    if (prob < 70)
    {
        if (!isempty(ready))
            p = dequeue(ready);
        else if (!isempty(ready2))
            p = dequeue(ready2);
    }
    else
    {
        if (!isempty(ready2))
            p = dequeue(ready2);
        else if (!isempty(ready))
            p = dequeue(ready);
    }

    return p;
}