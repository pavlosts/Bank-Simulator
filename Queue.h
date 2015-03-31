#ifndef __QUEUE__ 
#define __QUEUE__
#include "Clients.h"

#define CROWD 1000

typedef struct {
	int next;		/*First element in queue*/
	int prev;		/*Last element in queue*/
	int counter;
	Client array[CROWD];	/*Array of elements*/
} Queue;

  
void CreateQueue(Queue *queue);

int	QueueEmpty(Queue queue);

int QueueAddition(Queue *queue, Client element);
int QueueLeave(Queue *queue, Client *element);

int QueueSize(Queue queue);

#endif
