#include <Windows.h> 
#include <time.h>
#include "Thread.h" 
#include "LinkedList_Queue.h" 
#include "Event.h"
unsigned __stdcall Thread_EventHandler(LPVOID pParam)
{
	ThreadParam_Event*pThrdParam;
	DLL_EvQ *pPriH_LLQ, *pPriL_LLQ, *pEvQ; 
	int myRole;
	THREAD_FLAG *pFlagThreadTerminate; 
	int maxRound;
	LARGE_INTEGER PC_freq;
	Event *pEvent, *pEventProc;
	int event_id = 0, event_pri = 0, pkt_gen_count = 0;
	int num_event_processed = 0, targetEventGen;
	int myaddr = -1;
	ThreadStatusMonitor*pThrdMon;
	pThrdParam = (ThreadParam_Event*)pParam; 
	myRole = pThrdParam->role; 
	pPriH_LLQ = pThrdParam->EvQ_PriH;
	pPriL_LLQ = pThrdParam->EvQ_PriL;
	pThrdMon = pThrdParam->pThrdMon; 
	maxRound = pThrdParam->maxRound;
	pEventProc = pThrdParam->pThrdMon->eventProcessed;
	targetEventGen = pThrdParam->targetEventGen;
	PC_freq = pThrdParam->PC_freq;
	
	
	myaddr = pThrdParam->myAddr;
	
	num_event_processed = pThrdMon->eventsProc[myaddr];
	srand(time(NULL));
	
	for (int round = 0; round < maxRound; round++) 
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE) 
			break;
		while ((pEvent = deDLL_EvQ(pPriH_LLQ)) != NULL)//high priorityqueue가 비어있지 않을떄 계속 반복
		{
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);
			QueryPerformanceCounter(&pEvent->t_proc); //t_handle를 t_gen로수정
			pEvent->event_handler_addr = myaddr;
			calc_elapsed_time(pEvent, PC_freq);
			pEventProc[pThrdMon->totalEventProc] = *pEvent; 
			pThrdMon->eventsProc[myaddr]++;
			pThrdMon->totalEventProc++;
			pThrdMon->numEventProcs_priH++;
			free(pEvent);  // free the memory space for a Event 
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
			Sleep(300 + rand() % 500);
		} // end while 
		if ((pEvent= deDLL_EvQ(pPriL_LLQ)) != NULL)
		{ 
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);
			QueryPerformanceCounter(&pEvent->t_proc); 
			pEvent->event_handler_addr = myaddr;
			calc_elapsed_time(pEvent, PC_freq);
			pEventProc[pThrdMon->totalEventProc] = *pEvent;
			pThrdMon->eventsProc[myaddr]++;//처리한 프로세스 주소의 eventproc를 증감
			pThrdMon->totalEventProc++;
			pThrdMon->numEventProcs_priL++;
			free(pEvent);
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		} // end if 
		Sleep(100 + rand() % 300); 
	}  // end for
	_endthreadex(EXIT_CODE); 
	return 0;
}