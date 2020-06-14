#ifndef QUEUE_H

#define QUEUE_H

typedef struct queue_ Queue;

Queue * create_queue();
void enqueue(Queue * q, int content);
int dequeue(Queue * q);

int empty_queue(Queue * q);

void erase_queue(Queue** q);




#endif