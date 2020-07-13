#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "Multi_Thread.h"

using namespace std;
#define MAX_ROUND 100
unsigned _stdcall Simple_Thread(LPVOID pParam);

void main()
{
	FILE* fout;
	HANDLE hThread_A, hThread_B;
	DWORD ExitCode_A = NULL;
	DWORD ExitCode_B = NULL;
	ThreadParam thrdParam_A, thrdParam_B;
	unsigned int thread_id_A, thread_id_B;

	char flag_thread_terminate_control = 0;
	fout = fopen("Thread_Test_Output.txt", "w");

	if (fout == NULL)
	{
		printf("Error in file ");
		exit(-1);
	}

	thrdParam_A.fout = fout;
	thrdParam_A.myMark = 'A';
	thrdParam_A.pFlag_Terminate = &flag_thread_terminate_control;
	thrdParam_A.name = string("Thread_A");
	hThread_A = (HANDLE)_beginthreadex(NULL, 0, Simple_Thread, &thrdParam_A, 0, &thread_id_A);

	printf("main() : Thread_A (id:%d) is successfully created\n", thread_id_A);

	thrdParam_B.fout = fout;
	thrdParam_B.myMark = 'B';
	thrdParam_B.pFlag_Terminate = &flag_thread_terminate_control;
	thrdParam_B.name = string("Thread_B");
	hThread_B = (HANDLE)_beginthreadex(NULL, 0, Simple_Thread, &thrdParam_B, 0, &thread_id_B);

	printf("main () : Thread_B (id :%d) is successfully created !\n", thread_id_B);


	GetExitCodeThread(hThread_A, &ExitCode_A);
	printf("main() Current exit code of Thread_B (%d) is %d", thread_id_A, ExitCode_A);

	if (ExitCode_A == STILL_ACTIVE)
		printf("that means this Thread_B is STILLL_ACTIVE.\n");
	else
		printf("\n");

	GetExitCodeThread(hThread_B,& ExitCode_B);
	printf("main() Current exit code of Thread_B (%d) is %d", thread_id_B, ExitCode_B);

	if (ExitCode_B == STILL_ACTIVE)
		printf("that means this Thread_B is STILLL_ACTIVE.\n");
	else
		printf("\n");

	char myMark = 'M';//mÃâ·Â
	for (int round = 0; round < MAX_ROUND; round++)
	{
		for (int j = 0; j < 100; j++)
		{
			printf("%c", myMark);
		}
		printf("\n");
		Sleep(1);
	}

	flag_thread_terminate_control = 1;

	printf("main() wating the Thread_A (%d) to terminate by itself ..\n", thread_id_A);

	WaitForSingleObject(hThread_A, INFINITE);
	GetExitCodeThread(hThread_A, &ExitCode_A);
	printf("main() : Thread_A (%d) is terminate now with ExitCode (%d) \n", thread_id_A, ExitCode_A);
	CloseHandle(hThread_A);

	WaitForSingleObject(hThread_A, INFINITE);
	GetExitCodeThread(hThread_A, &ExitCode_A);
	printf("main() : Thread_A (%d) is terminate now with ExitCode (%d) \n", thread_id_B, ExitCode_B);
	CloseHandle(hThread_B);

	

	

}
