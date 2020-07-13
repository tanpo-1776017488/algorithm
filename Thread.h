#ifndef THREAD_H 
#define THREAD_H
#include <Windows.h>
#include <thread> 
#include <process.h>
#include "Event.h"
#include "SimParam.h" 
#include "LinkedList_Queue.h" 

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER }; 
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE }; 
#define EXIT_CODE 7

typedef struct
{
	int eventsGen[NUM_EVENT_GENERATORS];
	int eventsProc[NUM_EVENT_HANDLERS]; 
	int totalEventGen; 
	int totalEventProc;
	int numEventProcs_priH; 
	int numEventProcs_priL; 
	THREAD_FLAG *pFlagThreadTerminate; 
	Event eventProcessed[TOTAL_NUM_EVENTS];
} ThreadStatusMonitor;

typedef struct
{
	FILE *fout; 
	CRITICAL_SECTION *pCS_main; 
	CRITICAL_SECTION *pCS_thrd_mon;
	DLL_EvQ *EvQ_PriH; 
	DLL_EvQ *EvQ_PriL; 
	ROLE role;  
	int myAddr;  
	int maxRound;
	int targetEventGen;
	LARGE_INTEGER PC_freq;  // frequency of performance counter that is used to measure elapsed time  
	ThreadStatusMonitor *pThrdMon;
} ThreadParam_Event; 

unsigned __stdcall Thread_EventHandler(LPVOID pParam);
unsigned __stdcall Thread_EventGenerator(LPVOID pParam);
#endif