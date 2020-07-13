#ifndef EVENT_H 
#define EVENT_H 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define NUM_PRIORITY 100 
#define EVENT_PER_LINE 5 
#define SIZE_DESCRIPTION 2048 
enum EventStatus{ GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char *strEventStatus[]; 
typedef struct
{ int event_no;
  int event_gen_addr; 
  int event_handler_addr;
  int event_pri;  // event_priority
  enum EventStatus eventStatus; //char description[SIZE_DESCRIPTION]; 
} Event;

void initEvent(Event *pEv, int ev_gen_ID, int ev_no, int ev_pri, int ev_handler_addr,enum EventStatus ev_status); 
void printEvent(Event* pEv);
void fprintEvent(FILE *fout, Event* pEv);
void printEventArray(Event* pEv, int size, int items_per_line);
Event *genEvent(Event *pEv, int event_Gen_ID, int event_no, int event_pri);
#endif