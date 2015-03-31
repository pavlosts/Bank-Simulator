#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

void CreateQueue(Queue *queue )
{
	queue->next =  0;
	queue->prev = 0;
	queue->counter = 0;
}

int QueueEmpty(Queue queue)
{
	return ( queue.counter == 0 );
}

int QueueFull(Queue queue)
{
	int new_prev = (queue.prev+1) % CROWD;
	if (queue.counter == CROWD )
		return 1;
	else 
		return 0;
}

int QueueAddition(Queue *queue, Client element)
{
	if (QueueFull(*queue))
		return 0;
	else
	{
		queue->counter++;
		queue->array[queue->prev] = element;
		queue->prev = (queue->prev + 1) % CROWD;
	}
	return 1;
}

int QueueLeave(Queue *queue, Client *element)
{
	if (QueueEmpty(*queue))
		return 0;
	else
	{
		queue->counter--;
		*element = queue->array[queue->next];
		queue->next = ( queue->next + 1 ) % CROWD;
	}
	return 1;
}

int QueueSize(Queue queue){
	return queue.counter;
}
