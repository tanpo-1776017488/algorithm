#include <stdio.h>
#include <stdlib.h> 
#include <Windows.h>
#include <time.h> 
#include "Thread.h"
#include "LinkedList_Queue.h" 
#include "Event.h" 
#include "ConsoleDisplay.h" 

void main() 
{
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL;
	Event *pEvent; 
	int myAddr = 0; 
	int event_handler_addr, eventPriority; 
	LARGE_INTEGER pc_freq;//64비트 정수형 변수

	initDLL_EvQ(&dll_EvQ_PriH, 0); //우선순위0으로 초기화
	initDLL_EvQ(&dll_EvQ_PriL, 1); //우선순위1로 초기화
	srand(time(NULL)); 
	ThreadParam_Event thrdParam_EventGen[NUM_EVENT_GENERATORS], thrdParam_EventHndlr[NUM_EVENT_HANDLERS];
	HANDLE hThrd_EventGen[NUM_EVENT_GENERATORS], hThrd_EventHandler[NUM_EVENT_HANDLERS];
	CRITICAL_SECTION cs_main; 
	CRITICAL_SECTION cs_thrd_mon; 
	ThreadStatusMonitor thrdMon; 
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN; 
	int count, numEventProcessed;
	Event eventProcessed[TOTAL_NUM_EVENTS];

	InitializeCriticalSection(&cs_main); 
	InitializeCriticalSection(&cs_thrd_mon); 
	consHndlr = initConsoleHandler(); 
	QueryPerformanceFrequency(&pc_freq);

	thrdMon.pFlagThreadTerminate = &eventThreadFlag; 
	thrdMon.totalEventGen = 0;
	thrdMon.totalEventProc = 0;
	thrdMon.numEventProcs_priH = 0;
	thrdMon.numEventProcs_priL = 0; 
	
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].event_no = -1; // mark as not-processed  
		thrdMon.eventProcessed[ev].event_pri = -1; 
	}   

		/* Create and Activate Thread_EventHandler */  
	for (int proc = 0; proc < NUM_EVENT_HANDLERS; proc++) 
	{
			thrdMon.eventsProc[proc] = 0;  
			thrdParam_EventHndlr[proc].role = EVENT_HANDLER;  
			thrdParam_EventHndlr[proc].myAddr = proc; // Event handler address  
			thrdParam_EventHndlr[proc].pCS_main = &cs_main; 
			thrdParam_EventHndlr[proc].pCS_thrd_mon = &cs_thrd_mon; 
			thrdParam_EventHndlr[proc].EvQ_PriH = &dll_EvQ_PriH;  
			thrdParam_EventHndlr[proc].EvQ_PriL = &dll_EvQ_PriL;  
			thrdParam_EventHndlr[proc].maxRound = MAX_ROUND;  
			thrdParam_EventHndlr[proc].pThrdMon = &thrdMon;
			thrdParam_EventHndlr[proc].PC_freq = pc_freq; 

			hThrd_EventHandler[proc] = (HANDLE)_beginthreadex(NULL, 0, Thread_EventHandler, &thrdParam_EventHndlr[proc], 0, NULL);  
			EnterCriticalSection(&cs_main); 
			printf("Thread_EventHandler(%d) is created and activated ...\n", proc);  
			LeaveCriticalSection(&cs_main);
		}

		/* Create and Activate Thread_EventGenerators */  
	for (int gen = 0; gen < NUM_EVENT_GENERATORS; gen++)
	{
			thrdMon.eventsGen[gen] = 0;   
			thrdParam_EventGen[gen].role = EVENT_GENERATOR;
			thrdParam_EventGen[gen].myAddr = gen; // my Address of event generator 
			thrdParam_EventGen[gen].pCS_main = &cs_main; 
			thrdParam_EventGen[gen].pCS_thrd_mon = &cs_thrd_mon; 
			thrdParam_EventGen[gen].EvQ_PriH = &dll_EvQ_PriH;  
			thrdParam_EventGen[gen].EvQ_PriL = &dll_EvQ_PriL; 
			thrdParam_EventGen[gen].targetEventGen = NUM_EVENTS_PER_GEN; 
			thrdParam_EventGen[gen].maxRound = MAX_ROUND; 
			thrdParam_EventGen[gen].pThrdMon = &thrdMon;  
			thrdParam_EventGen[gen].PC_freq = pc_freq; 

			hThrd_EventGen[gen] = (HANDLE)_beginthreadex(NULL, 0, Thread_EventGenerator, &thrdParam_EventGen[gen], 0, NULL);   
			EnterCriticalSection(&cs_main); 
			printf("Thread_EventGen(%d) is created and activated ...\n", gen); 
			LeaveCriticalSection(&cs_main);
		}

		for (int round = 0; round < MAX_ROUND; round++)
		{
			EnterCriticalSection(&cs_main); 
			system("cls"); 
			gotoxy(consHndlr, 0, 0); 
			printf("Thread monitoring by main() :: round(%2d): \n", round); 
			printf("Event_Generators have generated total %2d events\n", thrdMon.totalEventGen); 
			
			for (int i = 0; i < NUM_EVENT_GENERATORS; i++) 
			{ 
				printf("  Event_Gen[%d] generated %2d events.\n", i, thrdMon.eventsGen[i]);
			}  
			printf("Event_Handlers   have processed total %2d events ", thrdMon.totalEventProc);
			printf("(event__PriH (%2d), event_PriL (%2d))\n", thrdMon.numEventProcs_priH, thrdMon.numEventProcs_priL);  
			
			for (int i = 0; i < NUM_EVENT_HANDLERS; i++) 
			{ 
				printf("  Event_Handler[%d] processed %2d events.\n", i, thrdMon.eventsProc[i]);
			}      
			printf("\n");   printf("DLL_EvQ_PriH (%3d events):\n   ", dll_EvQ_PriH.num_event);  
			printDLL_EvQ(&dll_EvQ_PriH);   printf("\n");  
			printf("DLL_EvQ_PriL (%3d events):\n   ", dll_EvQ_PriL.num_event); 
			printDLL_EvQ(&dll_EvQ_PriL);   printf("\n");  
			printf("Events processed:\n   ");
			
			count = 0;  
			numEventProcessed = thrdMon.totalEventProc;  
			
			for (int ev = 0; ev < numEventProcessed; ev++)
			{ 
				pEvent = &thrdMon.eventProcessed[ev];
				if (pEvent != NULL)
				{
					printEvent(pEvent);  
					if (((ev + 1) % EVENT_PER_LINE) == 0)   
						printf("\n   "); 
				}
			}  
			printf("\n");

			if (numEventProcessed >= TOTAL_NUM_EVENTS) 
			{
				eventThreadFlag = TERMINATE; // set 1 to terminate threads 
				LeaveCriticalSection(&cs_main);  
				break; 
			}   
			
			LeaveCriticalSection(&cs_main);  
			Sleep(100); 
		} // end for (int round .....) 

				DWORD nExitCode = NULL; 
				for (int i = 0; i < NUM_EVENT_GENERATORS; i++) 
				{ 
					WaitForSingleObject(hThrd_EventGen[i], INFINITE);
					EnterCriticalSection(&cs_main);
					printf("Thread_EventGenerator[%d] is terminated !!\n", i); 
					LeaveCriticalSection(&cs_main); 
					GetExitCodeThread(hThrd_EventGen[i], &nExitCode);
					CloseHandle(hThrd_EventGen[i]);
				}

				for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
				{ 
					WaitForSingleObject(hThrd_EventHandler[i], INFINITE);
					EnterCriticalSection(&cs_main); 
					printf("Thread_EventHandler[%d] is terminated !!\n", i);
					LeaveCriticalSection(&cs_main);  
					GetExitCodeThread(hThrd_EventHandler[i], &nExitCode); 
					CloseHandle(hThrd_EventHandler[i]); 
				}

				//calc_elapsed_time(thrdMon.eventProcessed, thrdMon.numPktProcs, freq); 
				double min, max, avg, sum; 
				int min_event, max_event; 
				min = max = sum = thrdMon.eventProcessed[0].t_elapsed; 
				min_event = max_event = 0;
				
				for (int i = 1; i < TOTAL_NUM_EVENTS; i++)
				{ 
					sum += thrdMon.eventProcessed[i].t_elapsed; 
					if (min > thrdMon.eventProcessed[i].t_elapsed)
					{ 
						min = thrdMon.eventProcessed[i].t_elapsed;  
						min_event = i;
					}   
					if (max < thrdMon.eventProcessed[i].t_elapsed)
					{ 
						max = thrdMon.eventProcessed[i].t_elapsed;  
						max_event = i;
					} 
				}  
				avg = sum / (double)TOTAL_NUM_EVENTS;
				printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
				printEvent_withTime(&thrdMon.eventProcessed[min_event]);
				printf("\n"); 
				printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000); 
				printEvent_withTime(&thrdMon.eventProcessed[max_event]); printf("\n");
				printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000, TOTAL_NUM_EVENTS);
				printf("\n");
 }