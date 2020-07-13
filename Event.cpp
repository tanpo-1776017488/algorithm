#include <stdio.h>
#include <stdlib.h>
#include "Event.h" 
const char *strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" }; 

void printEvent(Event* pEv) 
{ 
	char str_pri[6];
	printf("Ev(no:%3d, pri:%2d)  ", pEv->event_no, pEv->event_pri); 
}

void fprintEvent(FILE *fout, Event* pEv) 
{ 
	char str_pri[6]; 
	fprintf(fout, "Ev(no:%3d, pri:%2d)  ", pEv->event_no, pEv->event_pri); 
} 

Event *genEvent(Event *pEv, int event_Gen_ID, int event_no, int event_pri)//event_gen_id는 이 프로그램에서 항상0
{ 
	pEv= (Event *)malloc(sizeof(Event));
	if (pEv== NULL) 
		return NULL; 
	pEv->event_gen_addr= event_Gen_ID;
	pEv->event_handler_addr= -1; // event handler is not defined yet !!
	pEv->event_no= event_no; 
	pEv->event_pri= event_pri;
	
	return pEv;
}
void initEvent(Event *pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr,enum EventStatus ev_status) 
{
	pEv->event_gen_addr = ev_gen_ID;
	pEv->event_handler_addr = -1; // event handler is not defined yet !! 
	pEv->event_no= ev_no; 
	pEv->event_pri= ev_pri; 
	pEv->event_handler_addr= ev_handler_addr;
	pEv->eventStatus= ev_status;
}
void printEventArray(Event* pEv, int size, int items_per_line) 
{ 
	for (int i = 0; i < size; i++)
	{ 
		printEvent(&pEv[i]);
		if (((i + 1) % items_per_line) == 0)
			printf("\n  ");
	} 
}