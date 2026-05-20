#include "queue.h"
#include "proc.h"
#include "scheduler.h"
#include "utils.h"
#include "verbose.h"

extern struct queue *ready;
extern struct queue *ready2;
extern struct queue *finished; 

extern int QUANTUM;

static struct proc *select_from_queues()
{
    int r = rand() % 100;

    struct proc *p = NULL;

    // 70% ready
    if (r < 70)
    {
        if (!isempty(ready))
            p = dequeue(ready);
        else if (!isempty(ready2))
            p = dequeue(ready2);
    }
    // 30% ready2
    else
    {
        if (!isempty(ready2))
            p = dequeue(ready2);
        else if (!isempty(ready))
            p = dequeue(ready);
    }

    return p;
}

// scheduler principal
struct proc *scheduler(struct proc *current)
{
    struct proc *p = current;

    // se existe processo atual, reencaminha ele para fila correta
    if (p != NULL)
    {
        // terminou execução
        if (p->state == FINISHED)
        {
            enqueue(finished, p);
            return select_from_queues();
        }

        // saiu por preempção OU E/S (dinâmico quantum)
        if (p->state == READY || p->state == BLOCKED)
        {
            int used = p->process_time;

            // regra do enunciado:
            // < 50% do quantum -> fila 1
            // >= 50% -> fila 2
            if (used < (QUANTUM / 2))
                p->queue = 0;
            else
                p->queue = 1;

            if (p->queue == 0)
                enqueue(ready, p);
            else
                enqueue(ready2, p);
        }
    }

    // seleciona próximo processo
    struct proc *next = select_from_queues();

    if (next != NULL)
        next->state = RUNNING;

    return next;
}