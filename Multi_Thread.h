#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <process.h>
#include <string.h>

using namespace std;
typedef struct
{
	//CRITICAL_SECTION *pCs_file;//�Ӱ豸���߰�
	FILE *fout;
	string name;
	char*pFlag_Terminate;
	char myMark;
}ThreadParam;
#endif