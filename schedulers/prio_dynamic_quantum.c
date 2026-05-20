#include "queue.h"
#include "proc.h"
#include "scheduler.h"
#include "utils.h"
#include "verbose.h"

extern struct queue *ready;
extern struct queue *ready2;
extern struct queue *blocked;
extern struct queue *finished;

extern int QUANTUM;

static struct proc *select_from_queues()
{
    int r = rand() % 100;

    struct proc *p = NULL;

    if (r < 70)
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

struct proc *scheduler(struct proc *current)
{
    struct proc *p = current;

    if (p != NULL)
    {
        if (p->state == FINISHED)
        {
            enqueue(finished, p);
        }
        else if (p->state == READY)
        {
            int used = p->process_time;

            if (used < (QUANTUM / 2))
                p->queue = 0;
            else
                p->queue = 1;

            if (p->queue == 0)
                enqueue(ready, p);
            else
                enqueue(ready2, p);
        }
        else if (p->state == BLOCKED)
        {
            enqueue(blocked, p);
        }
    }

    struct proc *next = select_from_queues();

    if (next != NULL)
        next->state = RUNNING;

    return next;
}