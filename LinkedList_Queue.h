#ifndef LinkedList_QUEUE_H 
#define LinkedList_QUEUE_H 

#include <Windows.h>
#include <stdio.h> 
#include "Event.h" 

typedef struct ListNode //자기참조구조체 정의시 struct옆에 자기참조한다는 의미를 남겨야함(대게 소문자로 함)
{ 
	ListNode *next; 
	ListNode *prev;  
	Event *pEv; 
} ListNode_Ev;

typedef struct
{
	CRITICAL_SECTION cs_EvQ; 
	int priority; 
	ListNode_Ev *front; 
	ListNode_Ev *back; 
	int num_event; 
} DLL_EvQ;

void initDLL_EvQ(DLL_EvQ *DLL_EvQ, int priority); 
ListNode_Ev *enDLL_EvQ(DLL_EvQ *DLL_EvQ, Event *pEv);
Event *deDLL_EvQ(DLL_EvQ *DLL_EvQ); 
void printDLL_EvQ(DLL_EvQ *DLL_EvQ);

#endif