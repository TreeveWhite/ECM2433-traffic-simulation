/*
 * queue.h
 * This is the header file for the queue.c file.
 */

#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 *	Structure Definitions
 */

struct QNode {
    int waitingTime;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
};

/*
 *	Function Prototypes
 */

struct QNode* newNode();
struct Queue* createQueue();
void enQueue(struct Queue* q);
int deQueue(struct Queue* q);
void incrementWaitTime(struct Queue* q);
int isEmpty(struct Queue* q);

#endif
