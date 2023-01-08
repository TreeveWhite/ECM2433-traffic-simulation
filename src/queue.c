/*
 * queue.c
 * This file contains the function definitions for creating
 * a queue and any other operations on queue structures.
 */

#include <queue.h>

/*	Function Definitions 	*/

/*	This function is used to create a new node in 
 *	a queue. Each node represents a car and has a
 *	waiting time integer asigned to it. It can output
 *	a error message to stderr if the malloc is
 *	unsuccessful.					*/
struct QNode* newNode()
{
	struct QNode* temp;
	if (!(temp = (struct QNode*)malloc(sizeof(struct QNode))))
	{
		fprintf(stderr, "error %d: Out of memory creating QNode struct.", errno);
		exit(1);
	}
	temp->waitingTime = 0;
	temp->next = NULL;
	return temp;
}

/*	This function is used to create a new queue,
 *	a queue has a front and end node asigned and 
 *	this function can output an error message to
 *	stderr if the malloc is unsuccessful.		*/
struct Queue* createQueue()
{
	struct Queue* q;
	if (!(q = (struct Queue*)malloc(sizeof(struct Queue))))
	{
		fprintf(stderr, "error %d: Out of memory creating Queue struct.", errno);
		exit(1);
	}
	q->front = q->rear = NULL;
	return q;
}

/*	This function is used to add a new car to a
 *	specific queue, the waiting time of this car
 *	is automatiically started at 0.
 *	The  function outputs to stderr if the malloc
 *	is unsuccessful.				*/
void enQueue(struct Queue* q)
{
	struct QNode* temp = newNode();

	if (q->rear == NULL)
	{
		q->front = q->rear = temp;
		return;
	}

	q->rear->next = temp;
	q->rear = temp;
}

/*	This function is used to remove the front element
 *	of the queue, it simulates the front car leaving
 *	the queue and driving through the protected area.*/
int deQueue(struct Queue* q)
{
	if (q->front == NULL)
        	return;
	
	struct QNode* temp = q->front;

	int tempWaitTime = temp->waitingTime;

	q->front = q->front->next;

	if (q->front == NULL)
        	q->rear = NULL;
 
    	free(temp);

	return tempWaitTime;
}

/*	This function is used to incremenet the waiting
 *	time of all the cars in a queue at the end of a
 *	time period (iteration).			*/
void incrementWaitTime(struct Queue* q)
{
	struct QNode* car;
	car = q->front;
	while (car != NULL)
	{
		car->waitingTime++;
		car = car->next;
	}
}

/*	This function is used to check if a queue is
 *	empty and doesnt contain any nodes (cars).	*/
int isEmpty(struct Queue* q)
{
	if (q->front == NULL)
		return 1;
	else
		return 0;
}	
