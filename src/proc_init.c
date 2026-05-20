#include <stdio.h>

#include "queue.h"
#include "proc.h"
#include "stats.h"

extern int NPROC;

extern struct queue * ready;
extern struct queue * ready2;
extern struct queue * blocked;
extern struct queue * finished;

void proc_init()
{
    struct proc *p;

    for (int i = 0; i < NPROC; i++) 
    {
        p = createproc();

        p->tid = createproc_thread(p);

        p->queue = 0;

        enqueue(ready, p);

        count_ready_in(p);
    }
}