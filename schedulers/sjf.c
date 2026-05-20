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

struct proc * scheduler(struct proc * current)
{
    struct proc *selected;
    struct proc *aux;

    if(isempty(ready))
        return NULL;

    aux = ready->head;
    selected = aux;

    while(aux != NULL)
    {
        if(aux->remaining_time < selected->remaining_time)
        {
            selected = aux;
        }

        aux = aux->next;
    }


    if(selected->prev != NULL)
    {
        selected->prev->next = selected->next;
    }
    else
    {
        ready->head = selected->next;
    }

    if(selected->next != NULL)
    {
        selected->next->prev = selected->prev;
    }
    else
    {
        ready->tail = selected->prev;
    }

    selected->next = NULL;
    selected->prev = NULL;

    return selected;
}