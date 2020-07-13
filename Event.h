#ifndef EVENT_H 
#define EVENT_H 

#include <stdio.h> 
#include "ConsoleDisplay.h"
#include "SimParam.h" 
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3 
#define EVENT_PER_LINE 5

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED }; 
extern const char *strEventStatus[];

typedef struct
{
	int event_no; 
	int event_gen_addr; 
	int event_handler_addr;
	int event_pri;  // event_priority
	LARGE_INTEGER t_gen; //������ ó���ɋ� ������ ����ð� �˻��ϱ� ���ؼ�
	LARGE_INTEGER t_proc; 
	double t_elapsed; // elapsed time for event processing
	EventStatus eventStatus;
} Event; 

void printEvent(Event* pEvt);
void printEvent_withTime(Event* pEv);
void calc_elapsed_time(Event *pEv, LARGE_INTEGER freq);
#endif