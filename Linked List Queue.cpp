#include "LinkedList_Queue.h"
void initDLL_EvQ(DLL_EvQ *DLL_EvQ, int priority)
{ 
	InitializeCriticalSection(&DLL_EvQ->cs_EvQ);
	DLL_EvQ->front = DLL_EvQ->back = NULL;
	DLL_EvQ->num_event = 0;
	DLL_EvQ->priority = priority;//임의로추가함
}
ListNode_Ev *enDLL_EvQ(DLL_EvQ *DLL_EvQ, Event *pEv)//in dubble linked list
{
	ListNode_Ev *pLN_Event;//자기참조구조체
	if (pEv == NULL)//if event not exist
	{ 
		printf("Error in enEventQ:: pEventis NULL !!\n"); 
		printf("Press any key to continue ...\n");
		getc(stdin);
		
		return NULL; 
	} 
	
	pLN_Event = (ListNode_Ev*)calloc(1, sizeof(ListNode_Ev));//creat new empty list
	
	if (pLN_Event == NULL)
	{ 
		printf("Error in enEventQ:: memory allocation for new ListNodefailed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Event->pEv = pEv;//insert created event 
	
	EnterCriticalSection(&DLL_EvQ->cs_EvQ);
	
	if (DLL_EvQ->num_event == 0) // currently empty 
	{ 
		DLL_EvQ->front = DLL_EvQ->back = pLN_Event;//if dubble linked list is empty,front and back is set to created linked list
		pLN_Event->prev= pLN_Event->next = NULL;
		DLL_EvQ->num_event= 1;
	} 
	else
	{
		pLN_Event->prev= DLL_EvQ->back;
		DLL_EvQ->back->next = pLN_Event;
		DLL_EvQ->back = pLN_Event;
		pLN_Event->next = NULL;
		DLL_EvQ->num_event++;
	} 
	LeaveCriticalSection(&DLL_EvQ->cs_EvQ);//set criticalsection in swap front and back
	
	return pLN_Event;
}
Event *deDLL_EvQ(DLL_EvQ *DLL_EvQ)//first in first out
{
	Event *pEvent; 
	ListNode_Ev *pLN_Event_OldFront;
	
	EnterCriticalSection(&DLL_EvQ->cs_EvQ);//
	if (DLL_EvQ->num_event <= 0)
	{
		LeaveCriticalSection(&DLL_EvQ->cs_EvQ);
		return NULL;  // EventQis Empty	
	} 
	else
	{ 
		
		pLN_Event_OldFront= DLL_EvQ->front;
		pEvent= DLL_EvQ->front->pEv;
		DLL_EvQ->front = DLL_EvQ->front->next;
		
		if (DLL_EvQ->front != NULL) 
			DLL_EvQ->front->prev= NULL;
		
		DLL_EvQ->num_event--;
		free(pLN_Event_OldFront); // release memory for the current front ListNode
		LeaveCriticalSection(&DLL_EvQ->cs_EvQ);
		return pEvent; 
	} 
	//LeaveCriticalSection(&DLL_EvQ->cs_EvQ);
	
}
void printDLL_EvQ(DLL_EvQ *DLL_EvQ)
{
	int index = 0, count;
	Event *pEvent; 
	ListNode_Ev*pLN_Event;
	if (DLL_EvQ == NULL)
	{ 
		printf("Error in printEventQ:: pEvQis NULL !!");
		printf("Press any key to continue ...\n");
		getc(stdin); 
	} //printf("EventQ(num_event: %2d):\n   ", DLL_EvQ->num_event);
	
	if (DLL_EvQ->num_event<= 0)
		return;
	pLN_Event= DLL_EvQ->front;
	count = 0;
	
	while (pLN_Event!= NULL)
	{ 
		pEvent= pLN_Event->pEv; 
		if (pEvent== NULL) 
			break;
		printEvent(pEvent);
		printf(", ");
		count++; 
		
		if ((count % 5) == 0) 
			printf("\n   ");
		pLN_Event= pLN_Event->next;
	} 
}