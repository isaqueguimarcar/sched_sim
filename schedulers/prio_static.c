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

struct proc * scheduler(struct proc * current)
{
    int prob;
    struct proc * selected;

    prob = rand() % 100;

    if(prob < 70)
    {
        if(!isempty(ready))
        {
            selected = dequeue(ready);
        }
        else if(!isempty(ready2))
        {
            selected = dequeue(ready2);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        if(!isempty(ready2))
        {
            selected = dequeue(ready2);
        }
        else if(!isempty(ready))
        {
            selected = dequeue(ready);
        }
        else
        {
            return NULL;
        }
    }

    return selected;
}