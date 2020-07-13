#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"
#include "PriorityQueue_Event.h"
CircularQueue*initCirQueue(CircularQueue*cirQ, int capacity)
{
	Event * pEv;
	pEv = (Event *)calloc(capacity, sizeof(Event)); 
	
	if (pEv == NULL) 
	{
		printf("Error in memory allocation for Event array of size (%d)\n", capacity);
		exit;
	} 
	cirQ->pEv = pEv; //생성해둔 선형버퍼 안의 구조체에 초기화한 event pEv를 대입
	cirQ->capacity = capacity;//입력받은 capacity를 사용해서 cirq->capacity 에 대입
	cirQ->front = cirQ->end = 0; 
	cirQ->num_elements = 0;
	
	return cirQ;
}
void fprintCirQueue(FILE *fout, CircularQueue *cirQ) 
{
	Event ev;
	int index; 
	
	if ((cirQ == NULL) || (cirQ->pEv == NULL))
	{ 
		printf("Error in printArrayQueue: cirQis NULL or cirQ->array is NULL");
		exit;
	} 
	fprintf(fout, "  %2d Elements in CirQ_Event(index_front:%2d) :\n     ", cirQ->num_elements, cirQ->front);
	
	if (isCirQueueEmpty(cirQ))
	{ 
		fprintf(fout, "CirQ_Eventis Empty"); 
	}

	else 
	{ 
		for (int i = 0; i < cirQ->num_elements; i++) 
		{ 
			index = cirQ->front + i; 
			
			if (index >= cirQ->capacity) 
				index = index % cirQ->capacity; 
			ev = cirQ->pEv[index]; 
			fprintEvent(fout, &ev); 
			
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != cirQ->num_elements)) 
				fprintf(fout, "\n     "); 
		} 
	} 
	fprintf(fout, "\n");
}
void printCirQueue(CircularQueue*cirQ)
{
	Event ev;
	int index;

	if ((cirQ == NULL) || (cirQ->pEv == NULL))
	{
		printf("Error in printArrayQueue: cirQis NULL or cirQ->array is NULL");
		exit;
	}
	printf( "  %2d Elements in CirQ_Event(index_front:%2d) :\n     ", cirQ->num_elements, cirQ->front);

	if (isCirQueueEmpty(cirQ))
	{
		printf( "CirQ_Eventis Empty");
	}

	else
	{
		for (int i = 0; i < cirQ->num_elements; i++)
		{
			index = cirQ->front + i;

			if (index >= cirQ->capacity)
				index = index % cirQ->capacity;
			ev = cirQ->pEv[index];
			printEvent( &ev);

			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != cirQ->num_elements))
				printf( "\n     ");
		}
	}
	printf( "\n");
}
bool isCirQueueFull(CircularQueue*cirQ) 
{ 
	if (cirQ->num_elements == cirQ->capacity) 
		return true;
	else 
		return false;
} 

bool isCirQueueEmpty(CircularQueue*cirQ)
{ 
	if (cirQ->num_elements == 0)
		return true;
	else 
		return false; 
} 

Event *enCirQueue(FILE *fout, CircularQueue *cirQ, Event ev) 
{ 
	if (isCirQueueFull(cirQ)) 
	{
		return NULL;
	}
	cirQ->pEv[cirQ->end] = ev;//cirq_end 를 pev의 인덱스로 사용
	cirQ->num_elements++; 
	cirQ->end++; 
	
	if (cirQ->end >= cirQ->capacity)
		cirQ->end = cirQ->end % cirQ->capacity;
	
	return &(cirQ->pEv[cirQ->end]);
}
Event *deCirQueue(FILE *fout, CircularQueue *cirQ)
{
	if (isCirQueueEmpty(cirQ))
		return NULL;
	Event *pEv = &(cirQ->pEv[cirQ->front]);
	cirQ->front++; //다음인덱스 접근을위해 ++
	
	if (cirQ->front >= cirQ->capacity)
		cirQ->front = cirQ->front % cirQ->capacity;
	cirQ->num_elements--; 
	
	return pEv;
}
void delCirQueue(CircularQueue*cirQ) 
{ 
	if (cirQ->pEv != NULL)
		free(cirQ->pEv);
	cirQ->pEv = NULL;
	cirQ->capacity = 0;
	cirQ->front = cirQ->end = 0;
	cirQ->num_elements = 0;
}