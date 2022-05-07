#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Shlwapi.lib")
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

#define WIN32_LEAN_AND_MEAN
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ)

#define IDC_MAIN_BUTTON 101 //Button identifier
#define TIMER1 1001
#define TIMER2 1002

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <conio.h>
#include <string.h>
#include <commctrl.h>


#pragma comment(lib,"comctl32.lib")

#include <string>
#include <vector>
#include <iostream>
using namespace std;


void FilePathDirectory(int counter, HWND hWnd, char* file);
BOOL Inject(DWORD pID, const char*DLL_NAME);

void updateList();
void launchEXE();
void objmanager();


void cReadTextFile(char*filepathdestination);
void cAppendTextFile(char*yourCharPos);

