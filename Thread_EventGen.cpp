#include <Windows.h>
#include <time.h>
#include <thread>
#include "Thread.h" 
#include "LinkedList_Queue.h"
#include "Event.h" 

unsigned __stdcall Thread_EventGenerator(LPVOID pParam)
{ 
	ThreadParam_Event*pThrdParam;
	DLL_EvQ *pPriH_LLQ, *pPriL_LLQ, *pEvQ;
	int myRole;
	THREAD_FLAG *pFlagThreadTerminate; 
	int maxRound;
	Event *pEvent; 
	int event_id= 0, event_pri= 0, event_gen_count= 0;
	int targetEventGen, myAddr= -1, event_handlerAddr;
	ThreadStatusMonitor*pThrdMon;
	pThrdParam= (ThreadParam_Event*)pParam;
	myRole= pThrdParam->role;
	myAddr= pThrdParam->myAddr;
	pPriH_LLQ= pThrdParam->EvQ_PriH;
	pPriL_LLQ= pThrdParam->EvQ_PriL;
	pThrdMon= pThrdParam->pThrdMon;
	maxRound= pThrdParam->maxRound; 
	targetEventGen= pThrdParam->targetEventGen;
	
	srand(time(NULL));
	for (int round = 0; round < maxRound; round++) 
	{
		if (event_gen_count >= targetEventGen) 
		{ 
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break; 
			else
			{ 
				Sleep(500);
				continue; 
			} 
		} 
		
		pEvent = (Event *)calloc(1, sizeof(Event));
		pEvent->event_gen_addr = myAddr;
		pEvent->event_handler_addr = event_handlerAddr = -1;//not define NUM_ROUTERS에서 NUM_EVENTS_PER_GEN로수정
		pEvent->event_no = myAddr*50+event_gen_count;
		pEvent->event_pri = event_pri = rand() % NUM_PRIORITY;
		
		
		pEvQ = (event_pri <= PRIORITY_THRESHOLD) ? pPriH_LLQ : pPriL_LLQ; 
		
		while (enDLL_EvQ(pEvQ, pEvent) == NULL)
		{
			Sleep(100);
		}  // end while 
		QueryPerformanceCounter(&pEvent->t_gen);
		EnterCriticalSection(pThrdParam->pCS_thrd_mon); 
		
		pThrdMon->eventsGen[myAddr]++;//기존 numEventGens에서totalEventGen로 수정함,각각의 스레드가 몇개를 생성했는지 주소로 연결
		pThrdMon->totalEventGen++;//totalgen++
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		event_gen_count++;//event_no로 연결 
		Sleep(100 + rand() % 300);
	}  // end for
	
	_endthreadex(EXIT_CODE);
	return 0;
}