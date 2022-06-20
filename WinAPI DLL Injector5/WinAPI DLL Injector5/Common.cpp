#include "Common.h"

extern HWND activitylog;
extern HANDLE phandle;


char filename[10][MAX_PATH];

void FilePathDirectory(int counter, HWND hWnd, char* file)
{
	//char filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename[counter], sizeof(filename[counter]));
	ZeroMemory(&ofn,      sizeof(ofn));
	ofn.lStructSize  = sizeof(ofn);
	ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter  = _T("Any File\0*.*\0DLL Files\0*.dll\0SVG XML Files\0*.svg\0EXE Files\0*.exe\0Text Files\0*.txt\0");
	ofn.lpstrFile    = filename[counter];
	ofn.nMaxFile     = MAX_PATH;
	ofn.lpstrTitle   = _T("Select a File!");
	ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn))
	{
		//std::cout << "You chose the file \"" << filename[counter] << "\"\n";
		//MessageBox(NULL, filename[counter], "Note", MB_OK);
		
		strcpy(file, filename[counter]);
		//SendMessage(hWnd, LB_ADDSTRING, NULL, (LPARAM)filename[counter]);
		
		//if(counter == 1)SendMessage(hWnd, LB_ADDSTRING, NULL, (LPARAM)filename[counter]);
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above.
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default                    : std::cout << "You cancelled.\n";
		}
	}
}

BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam)
{
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowText(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	//printf("TITLEBUFFER: %s\n", buffer);
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)buffer);

	DWORD dwPID;
	GetWindowThreadProcessId(hWnd, &dwPID);
	
	//List visible windows with a non-empty title
	if(IsWindowVisible(hWnd) && length != 0)
	{
		//std::cout << hWnd << ":  " << windowTitle << std::endl;
		//printf("dwPID: %d TESTPARAM: %d\n", dwPID, lparam);
		

		if(dwPID == lparam)
		{
			/*
			//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"GOGOGO");
			
			//unsigned int pidTitle = dwPID;
			//char bff[255];
			//sprintf(bff, "%u", pidTitle);
			//SetWindowText(hWnd, bff);


			//char bff[256];
			//GetWindowText(hWnd, bff, sizeof(bff));
			//printf("WINDOWTEXT: %s\n", bff);
			//MessageBox(hWnd, bff, "TESTICLES", MB_OK);

			
			char titlebuffer[256] = "WoW_";
			strcat(titlebuffer, strp);

			int counter = atoi(strp);
			//MessageBox(NULL, titlebuffer, "TESTICLES", MB_OK);

			//SetWindowText(hWnd, "Nutsack");
			SetWindowText(hWnd, titlebuffer);
			GetWindowText(hWnd,bff,sizeof(bff));
			//printf("WINDOWTEXT: %s\n", bff);



			RECT windowRect;
			if(GetWindowRect(hWnd, &windowRect))
			{
				width = windowRect.right - windowRect.left;
				height = windowRect.bottom - windowRect.top;
				//printf("WSIZE: W: %d H: %d\n", width, height);
			}

			RECT clientRect;
			if(GetClientRect(hWnd, &clientRect))
			{
				cwidth = clientRect.right - clientRect.left;
				cheight = clientRect.bottom - clientRect.top;
				//printf("CWSIZE: W: %d H: %d\n", cwidth, cheight);
			}

			borderWidth = ((windowRect.right - windowRect.left) - (clientRect.right -clientRect.left))/2;
			//printf("bWidth: %d\n", borderWidth);

			borderHeight = ((windowRect.bottom - windowRect.top) - (clientRect.bottom -clientRect.top))/2;
			//printf("bHeight: %d\n", borderHeight);

			externHWND[counter] = hWnd;
			*/
		}
	}
	
	
	//char bff[256];
	//int b;
	//GetWindowModuleFileName(hWnd, bff, b); //HWND hwnd, LPTSTR lpszFileName, UINT cchFileNameMax); //UINT
	//printf("svgChar: %s - %d\n", bff, b);
	return TRUE;
}


int LoadPrivilege()
{
	HANDLE hToken;
	LUID Value;
	TOKEN_PRIVILEGES tp;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))return(GetLastError());
	if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Value))return(GetLastError());
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = Value;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if(!AdjustTokenPrivileges(hToken, FALSE,&tp, sizeof(tp), NULL, NULL))return(GetLastError());
	CloseHandle(hToken);
	return 1;
}


extern HWND activitylog;
extern char DLLpath[1000];
extern char EXEpath[1000];
DWORD pID;

void launchEXE()
{
	LoadPrivilege();
	phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);

	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"BEGIN");

	HANDLE htest;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//Start the child process.
	if(CreateProcess(NULL,     // No module name (use command line)
		//"directxtutorial1.exe", // Command line
		//"WoW.exe",
		EXEpath,
		NULL,                   // Process handle not inheritable
		NULL,                   // Thread handle not inheritable
		FALSE,                  // Set handle inheritance to FALSE
		0,                      // No creation flags
		NULL,                   // Use parent's environment block
		NULL,                   // Use parent's starting directory 
		&si,                    // Pointer to STARTUPINFO structure
		&pi))                   // Pointer to PROCESS_INFORMATION structure
	{
		//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"ENUM");

		htest = pi.hProcess;

		WaitForInputIdle(htest, 10000);
		EnumWindows(enumWindowCallback, pi.dwProcessId);
		
		if(*DLLpath == '\0')
		{
			//MessageBox(NULL, "EMPTY", "DLL Injector", MB_OK);
			SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"EMPTY");
		}
		else
		{
			//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"INJECTING");
			//MessageBox(NULL, "GOT SOMETHING", "DLL Injector", MB_OK);
			//INJECT DLL HERE
			//DWORD pID = pi.dwProcessId;//list[index+1]; //= GetTargetThreadIDFromProcName("directxtutorial1.exe"); //Retrieve process ID
			pID = pi.dwProcessId;//list[index+1]; //= GetTargetThreadIDFromProcName("directxtutorial1.exe"); //Retrieve process ID
			//Get the dll's full path name
			char buf[MAX_PATH] = {0};
			//GetFullPathName("test.dll", MAX_PATH, buf, NULL);
			GetFullPathName(DLLpath, MAX_PATH, buf, NULL);
			//printf(buf);
			//printf("\n");
			//Inject our main dll
			if(!Inject(pID, buf))
			{
				//printf("DLL Not Loaded!");
				//MessageBox(NULL, "DLL Not Loaded!", "DLL Injector", MB_OK);
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"DLL NOT LOADED");
			}
			else
			{
				//printf("DLL Loaded!");
				//MessageBox(NULL, "DLL Loaded!", "DLL Injector", MB_OK);
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"DLL LOADED");
			}
		}

		//EnumWindows(enumWindowCallback, pi.dwProcessId);

	}
}


BOOL Inject(DWORD pID, const char*DLL_NAME)
{
	HANDLE Proc;
	HMODULE hLib;
	char buf[50] = {0};
	LPVOID RemoteString, LoadLibAddy;
	if(!pID)return false;
	
	Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if(!Proc)
	{
		//sprintf(buf, "OpenProcess() failed: %d", GetLastError());
		//MessageBox(NULL, buf, "OpenProcess error", MB_OK);
		//printf(buf);
		return false;
	}
	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	//Allocate space in the process for our DLL
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	// Write the string name of our DLL in the memory allocated
	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);
	//Load our DLL
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);
	CloseHandle(Proc);
	return true;
}


/*
//void cReadTextFile(char*filepathdestination)
void cReadTextFile(char*filepathdestination)
{
	//APPEND PLAYER NAME
	char yourCharNameBuffer[50] = {0};
	strcpy(yourCharNameBuffer, filepathdestination);
	char strC[50] = {0};
	strcpy(strC, yourCharNameBuffer);//MUST STRCPY TO AVOID WIERD SYMBOLS
	strcat(strC, ".txt");
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)strC);

	FILE *fp = fopen(strC, "r");
	if(fp == NULL)
	{
		//printf("Could not open file %s\n",filename);
		//return 1;
	}

	fclose(fp);
}
*/



extern char myCtmGuid[255];
//char ctmGuidChar[255];
char str3[255][255];

float ctmPathX[1000], ctmPathY[1000], ctmPathZ[1000];
unsigned long long ctmGuidArr[1000];
int totalpaths;


void cReadTextFile(char*filepathdestination)
{
	//APPEND PLAYER NAME
	char yourCharNameBuffer[255] = {0};
	strcpy(yourCharNameBuffer, filepathdestination);
	char strC[255] = {0};
	strcpy(strC, yourCharNameBuffer);//MUST STRCPY TO AVOID WIERD SYMBOLS
	
	//strcat(strC, ".txt");
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)strC);

	char str[255], str2[255][255];
	int i=0, j=0;//value[200], value1[200], value2[200];

	FILE *fp = fopen(strC, "r");
	if(fp == NULL)
	{
		//printf("Could not open file %s\n",filename);
		//return 1;
	}

	while (fgets(str, 255, fp))
	{
		//i++;
		//sscanf(str,"%s %f %f %f",&str2[j], &ctmPathX[j], &ctmPathY[j], &ctmPathZ[j]);
		sscanf(str,"%s",&str2[j]);
		//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)str2[j]);
		
		if(strcmp(str2[j], "move") == 0){
			sscanf(str,"%s %f %f %f",&str2[j], &ctmPathX[j], &ctmPathY[j], &ctmPathZ[j]);
			//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)str2[j]);
			//updateList();
		}
		else if(strcmp(str2[j], "interactObj") == 0){
			sscanf(str,"%s %llu %f %f %f",&str2[j], &ctmGuidArr[j], &ctmPathX[j], &ctmPathY[j], &ctmPathZ[j]);
			//sprintf(ctmGuidChar, "%lu", ctmGuidArr[j]);
			sprintf(myCtmGuid, "%llu", ctmGuidArr[j]);//myCtmGuid
			//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)str2[j]);
			//updateList();
		}
		else if(strcmp(str2[j], "interactNpc") == 0){
			sscanf(str,"%s %llu %f %f %f",&str2[j], &ctmGuidArr[j], &ctmPathX[j], &ctmPathY[j], &ctmPathZ[j]);
			//sprintf(ctmGuidChar, "%lu", ctmGuidArr[j]);
			sprintf(myCtmGuid, "%llu", ctmGuidArr[j]);//myCtmGuid
			//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)str2[j]);
			//updateList();
		}
		strcpy(str3[j], str2[j]);
		
		j++;
		totalpaths = j;
	}

	fclose(fp);
}


extern bool appendPos;

extern char myPosXchar[50];
extern char myPosYchar[50];
extern char myPosZchar[50];

extern char myCtmXchar[255];
extern char myCtmYchar[255];
extern char myCtmZchar[255];

//FOR PATHING SCRIPT
void cAppendTextFile(char*yourCharPos, int type)
{
	/*
	//APPEND PLAYER NAME
	char yourCharNameBuffer[50] = {0};
	strcpy(yourCharNameBuffer, yourCharName);
	char strC[50] = {0};
	strcpy(strC, yourCharNameBuffer);//MUST STRCPY TO AVOID WIERD SYMBOLS
	strcat(strC, ".txt");
	SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)strC);
	*/

	appendPos = 0;

	
	char appendCharPos[255];
	if(type == 1){
		strcpy(appendCharPos, "move ");
		strcat(appendCharPos, myPosXchar);
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myPosYchar);
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myPosZchar);
		strcat(appendCharPos, "\n");
	}
	if(type == 2){
		strcpy(appendCharPos, "interactObj ");//ctmGuidArr
		strcat(appendCharPos, myCtmGuid);
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmXchar);//myCtmXchar//myPosXchar
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmYchar);//myCtmYchar//myPosXchar
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmZchar);//myCtmZchar//myPosXchar
		strcat(appendCharPos, "\n");
	}
	if(type == 3){
		strcpy(appendCharPos, "interactNpc ");//ctmGuidArr
		strcat(appendCharPos, myCtmGuid);
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmXchar);//myCtmXchar//myPosXchar
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmYchar);//myCtmYchar//myPosXchar
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmZchar);//myCtmZchar//myPosXchar
		strcat(appendCharPos, "\n");
	}

	if(type == 4){
		strcpy(appendCharPos, "move ");
		strcat(appendCharPos, myCtmXchar);
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmYchar);
		strcat(appendCharPos, " ");
		strcat(appendCharPos, myCtmZchar);
		strcat(appendCharPos, "\n");
	}
	
	//fp = fopen ("myfile.txt","a");
	//FILE * fp = fopen ("myfile.txt","a+");
	FILE * fp = fopen (yourCharPos, "a+");
	if(fp == NULL)
	{
		//fputs("fopen example",fp);
		//fclose (fp);
	}
	//if( EOF == fputs("fopen example\n", fp) )// appends 'df' to end of file
	if( EOF == fputs(appendCharPos, fp) )// appends 'df' to end of file
	{
		//then fputs failed
		//perror( "fputs failed" );
		//exit( EXIT_FAILURE );
		SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"APPEND FAILURE");
		updateList();
	}
	SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)appendCharPos);
	updateList();

	fclose(fp);
}


/*
void cAppendTextFile(char*yourCharName)
{
	
	//APPEND PLAYER NAME
	char yourCharNameBuffer[50] = {0};
	strcpy(yourCharNameBuffer, yourCharName);
	char strC[50] = {0};
	strcpy(strC, yourCharNameBuffer);//MUST STRCPY TO AVOID WIERD SYMBOLS
	strcat(strC, ".txt");
	SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)strC);


	//FILE *fp = fopen("myfile.txt", "a+");
	FILE *fp = fopen("myfile.txt", "a+");
	//FILE *fp = fopen("C://Users//Billgates//Documents//Visual Studio 2012//Projects//WinAPI DLL Injector3//Release//test.txt", "a+");
	//FILE *fp = fopen(strC,"a+");
	//fp = fopen("Carepackage.txt","a+");

	if(fp == NULL)
	{
		if( EOF == fputs("fopen example\n", fp) )// appends 'df' to end of file
		{
			//then fputs failed
			//perror( "fputs failed" );
			exit( EXIT_FAILURE );
		}
		SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"APPENDED TO PATH");
	}
	else
	{
		SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"FILE PATH ERROR");
	}
	

	fclose(fp);
}
*/


/*
//char cTEXTprint[100][1000];
void cReadTextFile(char*filepathdestination)
{
	//int TEXTbuffertick = 0;
	//char*cTEXTbuffer[100][1000] = {0};
	//char TEXTstr[1000];
	//char* filename = filepathdestination;//"test.txt";//"c:\\temp\\test.txt";
	//MessageBox(NULL, filepathdestination, "LOGIN CREDENTIALS", MB_OK);
	//FILE *fp;
	
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		//printf("Could not open file %s\n",filename);
		//return 1;
	}
		
	FILE * fp = fopen ("myfile.txt","a+");
	//pFile = fopen ("myfile.txt","a");
	
	if(fp == NULL)
	{
		//fputs("fopen example",fp);
		//fputs("fopen example",fp);
		//fclose (fp);
	}

	//char line[4];
	//while(NULL != fgets(line,sizeof(line),fp) )
   // {
        if( EOF == fputs("fopen example\n",fp) )// appends 'df' to end of file
        { // then fputs failed
           // perror( "fputs failed" );
            exit( EXIT_FAILURE );
        }
	//}

	while(fgets(TEXTstr, 1000, fp) != NULL)//(fgets(str, MAXCHAR, fp) != NULL)
	{
		//printf("TXTSTRING: %s\n", TEXTstr);
		strncpy((char*)cTEXTbuffer[TEXTbuffertick], TEXTstr, strlen(TEXTstr));
		TEXTbuffertick++;
	}

	for(int a = 0; a < 10; a++)
	{
		strncpy(cTEXTprint[a*2+0], (char*)cTEXTbuffer[a*2+0], strlen((char*)cTEXTbuffer[a*2+0]));
		//printf("USERN: %d - %s\n", a, cTEXTprint[a*2+0]);
		strncpy(cTEXTprint[a*2+1], (char*)cTEXTbuffer[a*2+1], strlen((char*)cTEXTbuffer[a*2+1]));
		//printf("PASSW: %d - %s\n", a, cTEXTprint[a*2+1]);
	}
	
	fclose(fp);
}
*/

