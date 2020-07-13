#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdio.h> 
#include "Event.h"
#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0 

typedef struct
{ int priority; 
  Event *pEv;
} CBTN_Event;

typedef struct PriorityQueue
{ 
	//CRITICAL_SECTION cs_priQ; 
    char PriQ_name[MAX_NAME_LEN]; 
	int priQ_capacity;
	int priQ_size;
	int pos_last;
	CBTN_Event*pCBT_Ev; 
} PriQ_Ev;

PriQ_Ev*initPriQ_Ev(PriQ_Ev*pPriQ_Ev,const  char *name, int capacity);
int insertPriQ_Ev(PriQ_Ev *pPriQ_Ev, Event *pEv); 
Event *removeMinPriQ_Ev(PriQ_Ev*pPriQ_Ev);
void printPriQ_Ev(PriQ_Ev*pPriQ_Ev);
void fprintPriQ_Ev(FILE *fout, PriQ_Ev *pPriQ_Ev);
void deletePriQ_Ev(PriQ_Ev*pPriQ_Ev);
#endif
