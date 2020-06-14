#include "queue.h"
#include<stdio.h>
#include<stdlib.h>
#define MAX 100



struct queue_{
    int  elements[MAX];
    int front;
    int rear;
    int size;
};

Queue * create_queue(){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    if(q != NULL){
        q->front=0;
        q->rear=0;
        q->size=0;
    }
    return q;
}

void enqueue(Queue * q, int content){
   
    if(q!=NULL && q->size<MAX){
        q->elements[q->rear] = content;
        q->size++;
        q->rear = (q->rear+1+MAX)%MAX;
    }
}

int dequeue(Queue * q){
    if(q != NULL && q->size>0){
        int c = q->elements[q->front];
        q->size--;
        q->front = (q->front +1 +MAX)%MAX;
        return c;
    }
    return -1;
}

int empty_queue(Queue * q){
    if(q!=NULL && q->size == 0)
        return 1;
    return 0;
}

void erase_queue(Queue** q){
    free(*q);
    q = NULL;
}



