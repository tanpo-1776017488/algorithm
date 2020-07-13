#include <iostream>
#include "Multi_Thread.h"

unsigned _stdcall Simple_Thread(LPVOID pParam)
{
	ThreadParam *pThrdParam = (ThreadParam*)pParam;
	string myName = pThrdParam->name;

	FILE*fout = pThrdParam->fout;
	char myMark = pThrdParam->myMark;
	int counter;
	char *pFlag_Terminate = pThrdParam->pFlag_Terminate;

	while (*pFlag_Terminate == 0)
	{
		for (int j = 0; j < 100; j++)
		{
			printf("%c", myMark);
		}
		printf("\n");
		Sleep(1);
	}
	_endthreadex(myMark);
	return 0;
}