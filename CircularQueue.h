#ifndef CIRCULAR_QUEUE_H 
#define CIRCULAR_QUEUE_H
#include "Event.h"
typedef struct
{ 
	Event *pEv; // circular queue for events 
	int capacity;
  int front;
  int end; 
  int num_elements;
} CircularQueue;
CircularQueue*initCirQueue(CircularQueue*pCirQ, int capacity); 
void printCirQueue(CircularQueue*cirQ); 
void fprintCirQueue(FILE *fout, CircularQueue *cirQ); 
bool isCirQueueFull(CircularQueue*cirQ);
bool isCirQueueEmpty(CircularQueue*cirQ); 
Event *enCirQueue(FILE *fout, CircularQueue *cirQ, Event ev);
Event *deCirQueue(FILE *fout, CircularQueue *cirQ); 
void delCirQueue(CircularQueue*cirQ);
#endif