//REFERENCES
//https://bytes.com/topic/c/answers/678749-tab-control-win32-api
//https://www.technical-recipes.com/2015/creating-a-tabbed-dialog-using-the-windows-api/
//https://www.codeproject.com/Articles/14712/Win32-SDK-C-Tab-Control-Made-Easy

//OTHERS
//https://stackoverflow.com/questions/36795092/c-winapi-window-does-not-refresh
//https://www.cplusplus.com/reference/cwchar/wcstol/
//https://stackoverflow.com/questions/14568249/finding-the-distance-between-2-3d-points

#include "Common.h"

HWND hwndMain;
HWND hwndTab;

//TRACKBAR
HWND hTrack;
HWND hTrack1;
HWND hlbl;
HWND hlbl1;
void CreateControls(HWND hwnd);
void UpdateLabel(void);


HINSTANCE hinst;
int oldTabPage;


extern int LoadPrivilege();
extern HANDLE phandle;
extern DWORD pID;

extern char myCharName[255];

extern int ctmType;

extern int currentpath;
extern int totalpaths;

extern bool stillExists;
extern int interactAgain;


//NumToPower(10,iPage+3);
int NumToPower(int num, int power)
{
	if(power==1)
		return num;
	return num*NumToPower(num, power-1);
}

int getlines(int Tab)
{
	HWND hwndEdit;
	int Res=NumToPower(10, Tab+3);
	int lines=-1;
	do
	{
		hwndEdit=GetDlgItem(hwndMain, (Res+lines+1));
		lines++;
	}while(hwndEdit!=0);
	return lines;
}


int iItemCount;

int holder = 0;
HWND activitylog;

HWND hWndList1;
HWND hWndList2;
HWND hWndList3;
HWND hWndList4;
HWND hWndList5;
HWND hWndList6;

/*
HWND hWndList7;
HWND hWndList8;
HWND hWndList9;
*/

HWND hWndList10;
HWND hWndList11;
HWND hWndList12;
HWND hWndList13;
HWND hWndList14;
HWND hWndList15;
HWND hWndList16;

HWND hWndList17;
HWND hWndList18;
HWND hWndList19;
HWND hWndList20;

HWND hWndList21;
HWND hWndList22;
HWND hWndList23;
HWND hWndList24;

HWND hWndList25;

HWND hWndList26;
HWND hWndList27;
HWND hWndList28;

HWND hWndList29;


bool startup;
bool startbot;
bool stopbot;
bool appendPos;
bool reversePlay;
bool enableLoop = 1;

char DLLpath[1000];
char EXEpath[1000];
char SCRIPTpath[1000];
char testpath[] = "Our first test bot!";
char testpath1[] = "aaa";
char testpath2[] = "bbb";
char testpath3[] = "ccc";


void HideWindowsOfTab(int Tab)
{
	HWND hwndEdit;
	int Res=NumToPower(10, Tab+3);
	int lines=getlines(Tab);
	for(int i=0; i<lines; i++){
		hwndEdit=GetDlgItem(hwndMain, (Res+i));
		ShowWindow(hwndEdit,SW_HIDE);
	}
}

void MakeVisibleWindows(int Tab)
{
	HWND hwndEdit;
	int Res=NumToPower(10, Tab+3);
	int lines=getlines(Tab);
	for(int i=0; i<lines; i++)
	{
		hwndEdit=GetDlgItem(hwndMain, (Res+i));
		ShowWindow(hwndEdit,SW_SHOW);
	}
}

void AddRow()
{
	int iPage = TabCtrl_GetCurSel(hwndTab);
	int lines = getlines(iPage);
	int Res=NumToPower(10,iPage+3);

	HWND a=CreateWindow(
		"EDIT",
		"Just1",
		WS_CHILD | WS_TABSTOP | WS_BORDER |WS_VISIBLE,
		15, 100+lines*25, 100, 25,
		hwndMain,
		(HMENU)(Res+lines),
		hinst,
		NULL);
	SetWindowPos(a, HWND_TOP, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);


	//if(holder==0)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath);
	//if(holder==1)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath1);
	//if(holder==2)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath2);
	//if(holder==3)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath3);

	//holder++;
	//if(holder==4)holder=0;
}

void MakeNewTab()
{
	int maxx=TabCtrl_GetItemCount(hwndTab);
	TCITEM tie;
	tie.mask = TCIF_TEXT;
	tie.pszText = "Hi";
	TabCtrl_InsertItem(hwndTab, maxx+1, &tie);
}

void updateList()
{
	iItemCount = SendMessage(activitylog, LB_GETCOUNT, 0, 0);
	if (iItemCount == 28)SendMessage(activitylog, LB_DELETESTRING, 0, NULL);

	//SendMessage(hWndList1, LB_DELETESTRING, NULL, NULL);
	//SendMessage(hWndList1, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));
	//SendMessage(activitylog, LB_GETTEXT, NULL, (LPARAM)DLLpath);
	//MessageBox(NULL, DLLpath, "TEST DLL", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CREATE:
		CreateControls(hwnd);
		//SetTimer(hwnd, 1, 20, NULL);//REFRESH
		SetTimer(hwnd, 1, 100, NULL);//REFRESH
		break;
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_HSCROLL:
		UpdateLabel();
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if(LOWORD(wParam)==1)
		{
			FilePathDirectory(wParam, activitylog, DLLpath);
			SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)DLLpath);
			updateList();
		}
		if(LOWORD(wParam)==2)
		{
			FilePathDirectory(wParam, activitylog, EXEpath);
			SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)EXEpath);
			updateList();
		}
		if(LOWORD(wParam)==3)
		{
			launchEXE();
		}
		if(LOWORD(wParam)==4)
		{
			FilePathDirectory(wParam, activitylog, SCRIPTpath);
			SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)SCRIPTpath);
			updateList();
			//cReadTextFile(myCharName);
			//cAppendTextFile(SCRIPTpath);
		}
		if(LOWORD(wParam)==5)
		{
			//NEED TO REWRITE
			if(startbot==0){
				cReadTextFile(SCRIPTpath);
				//cAppendTextFile(SCRIPTpath);
				startbot = 1;

				if(reversePlay == 0){
					currentpath = 0;//PLAY NORMALLY & RESET PREVIOUS VALUES
					
					//RESET VALUES
					stillExists = 0;
					interactAgain = 0;

					SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Resetting values!");
					updateList();
				}
				if(reversePlay == 1){
					currentpath = totalpaths - 1;//PLAY BACKWARDS
					SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Resetting values backwards!");
					updateList();
				}
			}
			else if(startbot==1){
				stopbot = 1;
			}
		}
		if(LOWORD(wParam)==11)
		{
			if(reversePlay == 0)
			{
				reversePlay = 1;//PLAY IN REVERSE
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Playing in reverse!");
				updateList();
			}
			else if(reversePlay == 1)
			{
				reversePlay = 0;//STOP
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Playing normally!");
				updateList();
			}
		}

		if(LOWORD(wParam)==12)
		{
			if(enableLoop == 0)
			{
				enableLoop = 1;
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Looping enabled!");
			}
			else if(enableLoop == 1)
			{
				enableLoop = 0;
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Looping disabled!");
			}
		}
		
		if(LOWORD(wParam)==16)appendPos = 1;
		if(LOWORD(wParam)==17)
		{
			cAppendTextFile(SCRIPTpath, ctmType);
		}

		if(LOWORD(wParam)==24)
		{
			//REVERT
			currentpath--;
			SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Going back a path!");
			updateList();
		}
		if(LOWORD(wParam)==25)
		{
			//FORWARD
			currentpath++;
			SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"Going up a path!");
			updateList();
		}
		if(LOWORD(wParam)==29)
		{
			cAppendTextFile(SCRIPTpath, 4);
		}


		if(LOWORD(wParam)==47)
			AddRow();
		if(LOWORD(wParam)==48)
			MakeNewTab();
		if(LOWORD(wParam)==49)
		{
			if(holder==0)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath);
			if(holder==1)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath1);
			if(holder==2)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath2);
			if(holder==3)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath3);



			iItemCount = SendMessage(activitylog, LB_GETCOUNT, 0, 0);
			if (iItemCount == 28)SendMessage(activitylog, LB_DELETESTRING, 0, NULL);


			/*
			//RENAME TAB
			TCITEM ltag;
			ltag.mask = TCIF_TEXT;
			ltag.pszText = "View Records";//make your own string
			TabCtrl_SetItem(hwndTab, 0, &ltag);
			SetWindowPos(hwndTab, HWND_BOTTOM, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			*/


			holder+=1;
			if(holder==4)holder=0;
		}
		if(LOWORD(wParam)==50)
		{
			iItemCount = SendMessage(activitylog, LB_GETCOUNT, 0, 0);
			if (iItemCount == 28)SendMessage(activitylog, LB_DELETESTRING, 0, NULL);

			//if(holder==0)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath);
			//if(holder==1)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath1);
			//if(holder==2)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath2);
			//if(holder==3)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath3);

			//SendMessage(activitylog, LB_DELETESTRING, NULL, NULL);
			//SendMessage(activitylog, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));



			//SendMessage(activitylog, LB_DELETESTRING, 0, NULL);
			//SendMessage(activitylog, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));
			//SendMessage(activitylog, LB_DELETESTRING, 25, NULL);
			//SendMessage(activitylog, CB_SETEDITSEL, 0, MAKELPARAM(-1,0));
		}
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code)
		{
		case TCN_SELCHANGE:
			{
				HideWindowsOfTab(oldTabPage);
				int iPage = TabCtrl_GetCurSel(hwndTab);
				MakeVisibleWindows(iPage);
				oldTabPage=iPage;
			}
			break;
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


void CreateControls(HWND hwnd)
{
	//slider bar 1
	HWND hLeftLabel = CreateWindowW(L"Static", L"1",//0
		WS_CHILD | WS_VISIBLE, 15, 75, 10, 30, hwnd, (HMENU)7, NULL, NULL);//275,110

	HWND hRightLabel = CreateWindowW(L"Static", L"500",
		WS_CHILD | WS_VISIBLE, 15, 75, 35, 30, hwnd, (HMENU)8, NULL, NULL);//275,110

	hlbl = CreateWindowW(L"Static", L"5", WS_CHILD | WS_VISIBLE,
		125, 65, 35, 30, hwnd, (HMENU)9, NULL, NULL);//350,150

	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex); 

	hTrack = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
		30, 85, 210, 30, hwnd, (HMENU) 10, NULL, NULL);//275,110,170

	SendMessageW(hTrack, TBM_SETRANGE,  TRUE, MAKELONG(1, 500));//0,100
	SendMessageW(hTrack, TBM_SETPAGESIZE, 0,  30);//0,10
	SendMessageW(hTrack, TBM_SETTICFREQ, 30, 0);//10,0
	SendMessageW(hTrack, TBM_SETPOS, FALSE, 5);//0
	SendMessageW(hTrack, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel);
	SendMessageW(hTrack, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel);

	//slider bar 2
	HWND hLeftLabel1 = CreateWindowW(L"Static", L"0",//0
		WS_CHILD | WS_VISIBLE, 15, 195, 10, 30, hwnd, (HMENU)20, NULL, NULL);//275,110

	HWND hRightLabel1 = CreateWindowW(L"Static", L"70",
		WS_CHILD | WS_VISIBLE, 15, 195, 35, 30, hwnd, (HMENU)21, NULL, NULL);//275,110

	hlbl1 = CreateWindowW(L"Static", L"10", WS_CHILD | WS_VISIBLE,
		125, 185, 35, 30, hwnd, (HMENU)22, NULL, NULL);//350,150

	INITCOMMONCONTROLSEX icex1;

	icex1.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex1.dwICC  = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex1); 

	hTrack1 = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
		30, 205, 210, 30, hwnd, (HMENU) 23, NULL, NULL);//275,110,170

	SendMessageW(hTrack1, TBM_SETRANGE,  TRUE, MAKELONG(0, 70));//0,100
	SendMessageW(hTrack1, TBM_SETPAGESIZE, 0,  10);//0,10
	SendMessageW(hTrack1, TBM_SETTICFREQ, 10, 0);//10,0
	SendMessageW(hTrack1, TBM_SETPOS, FALSE, 10);//0
	SendMessageW(hTrack1, TBM_SETBUDDY, TRUE, (LPARAM) hLeftLabel1);
	SendMessageW(hTrack1, TBM_SETBUDDY, FALSE, (LPARAM) hRightLabel1);
}

void UpdateLabel(void)
{
	LRESULT pos = SendMessageW(hTrack, TBM_GETPOS, 0, 0);
	wchar_t buf[4];
	wsprintfW(buf, L"%ld", pos);

	SetWindowTextW(hlbl, buf);

	LRESULT pos1 = SendMessageW(hTrack1, TBM_GETPOS, 0, 0);
	wchar_t buf1[4];
	wsprintfW(buf1, L"%ld", pos1);

	SetWindowTextW(hlbl1, buf1);
}



void StartCommonControls(DWORD flags)
{
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC=flags;
	InitCommonControlsEx(&iccx);
}

int desktopwidth=GetSystemMetrics(SM_CXSCREEN);
int desktopheight=GetSystemMetrics(SM_CYSCREEN);

void init()
{
	StartCommonControls(ICC_TAB_CLASSES);

	InitCommonControls();
	hwndTab=CreateWindowEx(0,
		//"SysTabControl32",
		WC_TABCONTROL,
		"",
		//WS_CHILD|WS_CLIPSIBLINGS,
		WS_CHILD | WS_VISIBLE,
		//0, 50,300, 250,
		0,0,
		desktopwidth,desktopheight,
		hwndMain,
		NULL,
		hinst,
		NULL);
	SetWindowPos(hwndTab, HWND_BOTTOM, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	TCITEM tie;
	tie.mask = TCIF_TEXT;
	tie.pszText = "Blank";
	TabCtrl_InsertItem(hwndTab, 0, &tie);

	//OUR DLL BUTTON
	hWndList1 = CreateWindow(
		"BUTTON",
		"DLL",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		15, 40, 75, 25,
		hwndMain,
		(HMENU)1,
		hinst,
		NULL);

	//OUR DLL BUTTON
	hWndList2 = CreateWindow(
		"BUTTON",
		"Target EXE",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		105, 40, 75, 25,
		hwndMain,
		(HMENU)2,
		hinst,
		NULL);

	/*
	//ROWS
	//This should be changed
	CreateWindow(
	"EDIT",
	"",
	WS_CHILD,
	10, 100, 100, 25,
	hwndMain,
	(HMENU)2,//open buffer
	hinst,
	NULL);
	*/

	hWndList3 = CreateWindow(
		"BUTTON",
		"Start EXE",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		195, 40, 75, 25,
		hwndMain,
		(HMENU)3,
		hinst,
		NULL);

	hWndList4 = CreateWindow(
		"BUTTON",
		"Load Script",
		WS_CHILD | WS_VISIBLE,
		//WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		285, 40, 75, 25,
		hwndMain,
		(HMENU)4,
		hinst,
		NULL);

	/*
	hWndList5 = CreateWindow(
	"BUTTON",
	"Char Script",
	WS_CHILD | WS_TABSTOP | WS_VISIBLE,
	375, 40, 75, 25,
	hwndMain,
	(HMENU)5,
	hinst,
	NULL);
	*/

	hWndList5 = CreateWindow(
		"BUTTON",
		"Start Bot",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		375, 40, 75, 25,
		//195, 80, 75, 25,
		hwndMain,
		(HMENU)5,
		hinst,
		NULL);

	hWndList6 = CreateWindow(
		"STATIC",
		"CTM(ms x10)",
		WS_CHILD | WS_VISIBLE,
		15, 65, 135, 15,
		hwndMain,
		(HMENU)6,
		hinst,
		NULL);


	hWndList11 = CreateWindow(
		"BUTTON",
		"Reverse",
		WS_CHILD | WS_VISIBLE,
		285, 80, 75, 25,
		hwndMain,
		(HMENU)11,
		hinst,
		NULL);

	hWndList12 = CreateWindow(
		"BUTTON",
		"Loop",
		WS_CHILD | WS_VISIBLE,
		375, 80, 75, 25,
		hwndMain,
		(HMENU)12,
		hinst,
		NULL);

	hWndList13 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_VISIBLE,
		15, 120, 135, 25,
		hwndMain,
		(HMENU)13,
		hinst,
		NULL);

	hWndList14 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_VISIBLE,
		165, 120, 135, 25,
		hwndMain,
		(HMENU)14,
		hinst,
		NULL);

	hWndList15 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_VISIBLE,
		315, 120, 135, 25,
		hwndMain,
		(HMENU)15,
		hinst,
		NULL);

	hWndList16 = CreateWindow(
		"BUTTON",
		"Rec Pos",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		15, 160, 75, 25,
		//195, 80, 75, 25,
		hwndMain,
		(HMENU)16,
		hinst,
		NULL);

	hWndList17 = CreateWindow(
		"BUTTON",
		"Rec GUID",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		105, 160, 75, 25,
		//195, 80, 75, 25,
		hwndMain,
		(HMENU)17,
		hinst,
		NULL);

	//CTM GUID
	hWndList18 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		195, 160, 255, 25,
		hwndMain,
		(HMENU)18,
		hinst,
		NULL);

	hWndList19 = CreateWindow(
		"STATIC",
		"GUID(sec)",
		WS_CHILD | WS_VISIBLE,
		15, 185, 100, 15,
		hwndMain,
		(HMENU)19,
		hinst,
		NULL);

	hWndList24 = CreateWindow(
		"BUTTON",
		"Path Down",
		WS_CHILD | WS_VISIBLE,
		285, 200, 75, 25,
		hwndMain,
		(HMENU)24,
		hinst,
		NULL);

	hWndList25 = CreateWindow(
		"BUTTON",
		"Path Up",
		WS_CHILD | WS_VISIBLE,
		375, 200, 75, 25,
		hwndMain,
		(HMENU)25,
		hinst,
		NULL);

	//ctmX
	hWndList26 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_VISIBLE,
		15, 240, 135, 25,
		hwndMain,
		(HMENU)26,
		hinst,
		NULL);

	//ctmY
	hWndList27 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_VISIBLE,
		165, 240, 135, 25,
		hwndMain,
		(HMENU)27,
		hinst,
		NULL);

	//ctmZ
	hWndList28 = CreateWindow(
		"LISTBOX",
		"",
		WS_CHILD | WS_VISIBLE,
		315, 240, 135, 25,
		hwndMain,
		(HMENU)28,
		hinst,
		NULL);

	hWndList29 = CreateWindow(
		"BUTTON",
		"Rec CTM",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		15, 280, 75, 25,
		hwndMain,
		(HMENU)29,
		hinst,
		NULL);


	//EXTRAS
	HWND a=CreateWindow(
		"BUTTON",
		"Add Row",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		195, 440, 75, 25,
		hwndMain,
		(HMENU)47,
		hinst,
		NULL);
	//SetWindowPos(a, HWND_TOP, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	//This should be changed
	CreateWindow(
		"BUTTON",
		"Add Tab",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		285, 440, 75, 25,
		hwndMain,
		(HMENU)48,
		hinst,
		NULL);

	CreateWindow(
		"BUTTON",
		"Add String",
		WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		375, 440, 75, 25,
		hwndMain,
		(HMENU)49,
		hinst,
		NULL);

	//105,195,285,375,
	//40, 80, 120, 160,

	activitylog=CreateWindow(
		"LISTBOX",
		"Ass1",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL,
		//WS_CHILD | WS_TABSTOP | WS_BORDER | WS_VISIBLE,
		480, 40, 450, 450,
		hwndMain,
		(HMENU)50,
		hinst,
		NULL);
	SetWindowPos(activitylog, HWND_TOP, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	//SetWindowPos(activitylog, HWND_TOP, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	//SetWindowPos(activitylog, HWND_BOTTOM, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	//if(holder==0)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath);
	//if(holder==1)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath1);
	//if(holder==2)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath2);
	//if(holder==3)SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath3);

	SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath);
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath1);
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath2);
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)testpath3);


	TabCtrl_SetCurSel(hwndTab, 0);
	MakeVisibleWindows(0);
	oldTabPage=0;

	ShowWindow(hwndTab, SW_SHOW);
	UpdateWindow(hwndTab);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	hinst=hInstance;


	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "myWindowClass";
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	hwndMain = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"myWindowClass",
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		//CW_USEDEFAULT, CW_USEDEFAULT, 350, 400,
		desktopwidth / 4,          // position:left
		desktopheight / 4,         // position: top
		960,//desktopwidth / 2,          // width
		540,//desktopheight / 2,         // height
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwndMain, nCmdShow);
	UpdateWindow(hwndMain);

	init();

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		//LoadPrivilege();
		//phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);
		//if(startbot==1)objmanager();

		objmanager();

		//MessageBox(hwndMain, "THIS IS CONTINUOUS", "TEST", MB_OK);//WILL GET STUCK
		if (!IsDialogMessage(hwnd, &Msg)){
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return Msg.wParam;
}


