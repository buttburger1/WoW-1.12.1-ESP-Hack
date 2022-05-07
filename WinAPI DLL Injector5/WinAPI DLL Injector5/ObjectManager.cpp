#include "Common.h"

/*
internal enum Console : uint
{
	ConsoleWrite = 0x63CD00,
	ConsoleRegisterCommand = 0x63F9E0,
	ConsoleUnregisterCommand = 0x63FB40,
	EnableConsole = 0xC4EC20,
	InvalidfunctionPtrStart = 0x884800, //1
	InvalidfunctionPtrEnd = 0x884C00,  //7FFFFFFF
}

internal enum CharacterScreen : uint
{
	Pointer = 0xB42144,
	Size = 0x120,
	NumCharacters = Pointer - 0x4,
	LoginState = 0xB41478,
}

internal enum Spells : uint
{
	SpellCooldownPtr = 0xCECAEC,
	SpellCooldownOffset = 0xCECAF4,
	SpellMaxIndex = 0xC0D78C,
	SpellBookKnownSpellsPlayer = 0xB700F0,
	SpellBookKnownSpellsPet = 0xB6F098,
	SpellIsTargeting = 0xCECAC0,
}
*/

extern bool startbot;
extern bool stopbot;
extern bool appendPos;
extern bool reversePlay;
extern bool enableLoop;

extern int LoadPrivilege();
extern DWORD pID;

extern HWND hTrack;
extern HWND hTrack1;

extern HWND activitylog;
extern HWND hwndTab;

extern HWND hWndList5;

//extern HWND hWndList12;
extern HWND hWndList13;
extern HWND hWndList14;
extern HWND hWndList15;

//extern HWND hWndList17;
extern HWND hWndList18;
extern HWND hWndList19;
extern HWND hWndList20;

//extern HWND hWndList21;
//extern HWND hWndList22;
extern HWND hWndList23;
extern HWND hWndList24;
extern HWND hWndList25;

extern HWND hWndList26;
extern HWND hWndList27;
extern HWND hWndList28;


extern char DLLpath[1000];
extern char EXEpath[1000];
extern char SCRIPTpath[1000];

extern float ctmPathX[1000], ctmPathY[1000], ctmPathZ[1000];

//HWND hwnd;
HANDLE phandle;

//ANTIAFK
clock_t firstTick;
clock_t nextTick;
unsigned long int diffTick;
//Memory scan values
unsigned long int initialTick;
unsigned long int currTick;
unsigned long int newTick;

//BOT
clock_t uptime;
clock_t curtime;
float deltatime;


float ctmMoveValues1 = 0.5f, ctmMoveValues2 = 13.96263409f, ctmMoveValues3 = 0.25f;
float ctmObjValues1 = 4.5f, ctmObjValues2 = 3.141592741f, ctmObjValues3 = 20.25f;
float ctmNPCValues1 = 2.777777672f, ctmNPCValues2 = 13.96263409f, ctmNPCValues3 = 7.716048717f;
int ctmFlag = 4;
bool ctmFlag7;


int currentpath;
extern int totalpaths;

extern unsigned long long ctmGuidArr[1000];
extern char str3[255][255];


int camfov;

unsigned int isingame, currentobjtype, autoloot, autoloot_off = 0, autoloot_on = 1,
	myhp, mymana,
	targethp, targetmana;


//unsigned long long
unsigned long long baseaddr, firstobj, nextobj, localguid, targetguid, currentguid, test;

float myx, myy, myz, myfacing, myspeed, myspeedrunmodifier,
	//mycamxpos, mycamypos, mycamzpos, mycamxrot, mycamzrot,
	targetx, targety, targetz, targetfacing, targetspeed, targetspeedrunmodifier;
float speedup = 14;
float scanX, scanY, scanZ;

unsigned int testname;
//NPC
char mycrapchar[255];
//GAMEOBJ
char mycrapchar1[255];
//GAMEOBJ
unsigned int mystuff1, mystuff2, mystuff3;
//tests
float ftest1, ftest2, ftest3;
//NPC
unsigned int mytest1, mytest2, mytest3;


float myPosX, myPosY, myPosZ;
char myPosXchar[255], myPosYchar[255], myPosZchar[255];

float myCtmX, myCtmY, myCtmZ;
char myCtmGuid[255];
char myCtmXchar[255], myCtmYchar[255], myCtmZchar[255];
float ctmGetValue1, ctmGetValue2, ctmGetValue3;
int ctmType;

unsigned long long ctmGuid;

char myCharName[255], myCharNameStore[255];//myCharName

unsigned int isCasting;

bool stillExists = 0;
int interactAgain;


enum Choice
{
	NONE = 0,
	ITEM = 1,
	CONTAINER = 2,
	UNIT = 3,
	PLAYER = 4,
	GAMEOBJECT = 5,
	DYNAMICOBJECT = 6,
	CORPSE = 7
};

void objmanager()
{
	LoadPrivilege();
	//GetWindowThreadProcessId(hwnd, &pID);
	phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);

	//ReadProcessMemory(hProcess, (LPVOID)Point, value, 128, 0);
	ReadProcessMemory(phandle, (void*)0x00C27D88, &myCharName, sizeof(myCharName), 0);//00C27D88
	if(strcmp(myCharName, myCharNameStore) != 0)
	{
		strcpy(myCharNameStore, myCharName);
		//RENAME TAB
		TCITEM ltag;
		ltag.mask = TCIF_TEXT;
		//ltag.pszText = "View Records";//make your own string
		ltag.pszText = myCharName;//make your own string
		TabCtrl_SetItem(hwndTab, 0, &ltag);
		SetWindowPos(hwndTab, HWND_BOTTOM, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}

	ReadProcessMemory(phandle, (void*)0xB4B424, &isingame, sizeof(isingame), 0);
	ReadProcessMemory(phandle, (void*)(0xB41414), &baseaddr, sizeof(baseaddr), 0);
	ReadProcessMemory(phandle, (void*)(0xB4E2D8), &targetguid, sizeof(targetguid), 0);
	//if(targetguid == localguid)printf("TARGETGUID: %llu\n", targetguid);
	ReadProcessMemory(phandle, (void*)0xCECA88, &isCasting, sizeof(isCasting), 0);//0xCECA88 isCasting

	//float f = 1.123456789;
	//char c[50]; //size of the number
	//sprintf(c, "%g", f);

	ReadProcessMemory(phandle, (void*)0x00C7B544, &myPosX, sizeof(myPosX), 0);//0x00C7B544 (float) Player X
	ReadProcessMemory(phandle, (void*)0x00C7B548, &myPosY, sizeof(myPosY), 0);//0x00C7B548 (float) Player Y
	ReadProcessMemory(phandle, (void*)0x00C7B54C, &myPosZ, sizeof(myPosZ), 0);//0x00C7B54C (float) Player Z
	sprintf(myPosXchar, "%f", myPosX);
	sprintf(myPosYchar, "%f", myPosY);
	sprintf(myPosZchar, "%f", myPosZ);
	
	SendMessage(hWndList13, LB_DELETESTRING, 0, NULL);
	SendMessage(hWndList13, LB_ADDSTRING, NULL, (LPARAM)myPosXchar);
	UpdateWindow(hWndList13);
	SendMessage(hWndList14, LB_DELETESTRING, 0, NULL);
	SendMessage(hWndList14, LB_ADDSTRING, NULL, (LPARAM)myPosYchar);
	UpdateWindow(hWndList14);
	SendMessage(hWndList15, LB_DELETESTRING, 0, NULL);
	SendMessage(hWndList15, LB_ADDSTRING, NULL, (LPARAM)myPosZchar);
	UpdateWindow(hWndList15);

	ReadProcessMemory(phandle, (void*)0x00C4D980, &ctmGuid, sizeof(ctmGuid), 0);//ctmGuid
	if(ctmGuid != 0){
		sprintf(myCtmGuid, "%llu", ctmGuid);//myCtmGuid
		SendMessage(hWndList18, LB_DELETESTRING, 0, NULL);
		SendMessage(hWndList18, LB_ADDSTRING, NULL, (LPARAM)myCtmGuid);
		UpdateWindow(hWndList18);
	}


	//0.5(move), 4.5(obj), 2.777777672(npc)
	ReadProcessMemory(phandle, (LPVOID)(0x00C4D910), &ctmGetValue1, sizeof(ctmGetValue1), 0);
	//13.96263409(move/npc), 3.141592741(obj/attack)
	ReadProcessMemory(phandle, (LPVOID)(0x00C4D93C), &ctmGetValue2, sizeof(ctmGetValue2), 0);
	//0.25(move), 20.25(obj), 7.716048717(npc), 3.666666508(attack)
	ReadProcessMemory(phandle, (LPVOID)(0x00C4D9C0), &ctmGetValue3, sizeof(ctmGetValue3), 0);

	if(ctmGetValue1 == 0.5f || ctmGetValue3 == 0.25f)ctmType = 1;
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"MOVE");
	else if(ctmGetValue1 == 4.5f || ctmGetValue3 == 20.25f)ctmType = 2;
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"OBJ");
	else if(ctmGetValue1 == 2.777777672f || ctmGetValue3 == 7.716048717f)ctmType = 3;
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"NPC");


	ReadProcessMemory(phandle, (void*)0x00C4D890, &myCtmX, sizeof(myCtmX), 0);
	ReadProcessMemory(phandle, (void*)0x00C4D894, &myCtmY, sizeof(myCtmY), 0);
	ReadProcessMemory(phandle, (void*)0x00C4D898, &myCtmZ, sizeof(myCtmZ), 0);
	sprintf(myCtmXchar, "%f", myCtmX);
	sprintf(myCtmYchar, "%f", myCtmY);
	sprintf(myCtmZchar, "%f", myCtmZ);
	
	SendMessage(hWndList26, LB_DELETESTRING, 0, NULL);
	SendMessage(hWndList26, LB_ADDSTRING, NULL, (LPARAM)myCtmXchar);
	UpdateWindow(hWndList26);
	SendMessage(hWndList27, LB_DELETESTRING, 0, NULL);
	SendMessage(hWndList27, LB_ADDSTRING, NULL, (LPARAM)myCtmYchar);
	UpdateWindow(hWndList27);
	SendMessage(hWndList28, LB_DELETESTRING, 0, NULL);
	SendMessage(hWndList28, LB_ADDSTRING, NULL, (LPARAM)myCtmZchar);
	UpdateWindow(hWndList28);

	
	//RECORDS MY POS(MOVE ONLY)
	if(appendPos == 1)
	{
		appendPos = 0;
		cAppendTextFile(SCRIPTpath, 1);
	}
	
	if(startbot==1)
	{
		ReadProcessMemory(phandle, (void*)(baseaddr + 0xAC), &firstobj, sizeof(firstobj), 0);
		ReadProcessMemory(phandle, (void*)(baseaddr + 0xC0), &localguid, sizeof(localguid), 0);
		//printf("LOCALGUID: %llu\n", localguid);
		nextobj = firstobj;
		while(firstobj != 0 && (firstobj & 1) == 0)
		{
			ReadProcessMemory(phandle, (void*)(firstobj + 0x14), &currentobjtype, sizeof(currentobjtype), 0);
			//printf("currentobjtypenumber: %u\n", currentobjtype);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x30), &currentguid, sizeof(currentguid), 0);
			switch(currentobjtype)//cin >> i;
			{
			case ITEM:
				//printf("ITEM: 0x%.8X\n", firstobj);
				break;
			case CONTAINER:
				//printf("CONTAINER: 0x%.8X\n", firstobj);
			case UNIT:
				/*
				printf("UNIT: 0x%.8X ", firstobj);
				ReadProcessMemory(phandle, (void*)(firstobj + 0xB30), &mytest1, sizeof(mytest1), 0);
				//printf("AAA: %u, ", mytest1);
				ReadProcessMemory(phandle, (void*)(mytest1 + 0x0), &mytest2, sizeof(mytest2), 0);
				//printf("BBB: %u, ", mytest2);
				ReadProcessMemory(phandle, (void*)(mytest2), &mycrapchar, sizeof(mycrapchar), 0);
				printf("CCC: %s\n", mycrapchar);
				*/
				break;
			case PLAYER:
				/*
				printf("PLAYER: 0x%.8X\n", firstobj);
				if(currentobjtype == 4)
				{
				char targetNameToChar[50] = "";
				int targetname = 0;
				int namebase = 0xC0E230;
				unsigned long long tempguid = 0;
				while(true)
				{
				ReadProcessMemory(phandle, (void*)(namebase), &targetname, sizeof(targetname), 0);
				ReadProcessMemory(phandle, (void*)(targetname + 0xC), &tempguid, sizeof(tempguid), 0);//targetname + 0xC;
				if(tempguid == 0)
				{
				printf("EMPTY!\n");
				}
				if(tempguid != currentguid)
				{
				ReadProcessMemory(phandle, (void*)(targetname), &namebase, sizeof(namebase), 0);
				targetname = namebase;
				//printf("Loop: %d!\n", namebase);
				}
				else
				{
				break;
				}
				}
				ReadProcessMemory(phandle, (void*)(targetname + 0x14), &targetNameToChar, sizeof(targetNameToChar), 0);
				printf("PLAYERNAME: %s\n", targetNameToChar);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &scanX, sizeof(scanX), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &scanY, sizeof(scanY), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &scanZ, sizeof(scanZ), 0);
				printf("X: %f Y: %f Z: %f\n", scanX, scanY, scanZ);
				}
				*/

				break;
			case GAMEOBJECT:

				//printf("GAMEOBJECT: 0x%.8X ", firstobj);
				/*
				if (baseaddr == 0 || currentguid == 0)
				{
				printf("NOTHING!\n");
				}
				else
				{
				//return BmWrapper.memory.ReadASCIIString((BmWrapper.memory.ReadUInt((BmWrapper.memory.ReadUInt(baseAdd + 0x214) + 0x8))), 40);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x214), &mystuff1, sizeof(mystuff1), 0);
				//printf("AAA: %u, ", mystuff1);
				ReadProcessMemory(phandle, (void*)(mystuff1 + 0x8), &mystuff2, sizeof(mystuff2), 0);
				//printf("BBB: %u, ", mystuff2);
				ReadProcessMemory(phandle, (void*)(mystuff2), &mycrapchar1, sizeof(mycrapchar1), 0);
				printf("CCC: %s\n", mycrapchar1);
				}
				*/
				break;
			case DYNAMICOBJECT:
				//printf("DYNAMICOBJECT: 0x%.8X\n", firstobj);
				break;
			case CORPSE:
				//printf("CORPSE: 0x%.8X\n", firstobj);
				break;
			default:
				//printf("Invalid choice!\n");
				break;

				break;
			}
			

			//TEST
			//for(int i = 0; i < totalpaths; i++){
			if(currentguid == ctmGuidArr[currentpath] && stillExists == 0){
			//if(currentguid == ctmGuidArr[currentpath] && stillExists == 0 && interactAgain == 0){
				stillExists = 1;
				//interactAgain = 0;
				interactAgain = 1;
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"SIMILAR GUIDS!");
				updateList();
			}
			
			/*
			else if(currentguid == ctmGuidArr[currentpath] && interactAgain == 1)
			{
				stillExists = 0;
				SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"STOP!");
				updateList();
			}
			*/
			

			if(currentguid == localguid)
			{
				//printf("MY GUID: %llu\n", currentguid);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &myx, sizeof(myx), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &myy, sizeof(myy), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &myz, sizeof(myz), 0);
				//printf("MY LOCATION: X: %f, Y: %f, Z: %f\n", myx, myy, myz);
				
				/*
				sprintf(myPosXfloat, "%f", myx);
				sprintf(myPosYfloat, "%f", myy);
				sprintf(myPosZfloat, "%f", myz);
				SendMessage(hWndList13, LB_DELETESTRING, 0, NULL);
				SendMessage(hWndList13, LB_ADDSTRING, NULL, (LPARAM)myPosXfloat);
				UpdateWindow(hWndList13);
				SendMessage(hWndList14, LB_DELETESTRING, 0, NULL);
				SendMessage(hWndList14, LB_ADDSTRING, NULL, (LPARAM)myPosYfloat);
				UpdateWindow(hWndList14);
				SendMessage(hWndList15, LB_DELETESTRING, 0, NULL);
				SendMessage(hWndList15, LB_ADDSTRING, NULL, (LPARAM)myPosZfloat);
				UpdateWindow(hWndList15);
				*/
				
				ReadProcessMemory(phandle, (void*)(firstobj + 0x1DC8), &myhp, sizeof(myhp), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x1DCC), &mymana, sizeof(mymana), 0);

				ReadProcessMemory(phandle, (void*)(firstobj + 0xA2C), &myspeed, sizeof(myspeed), 0);
				//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0xA34), &speedup, sizeof(speedup), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0xA34), &myspeedrunmodifier, sizeof(myspeedrunmodifier), 0);
				//printf("RUNSPEED: %f RUNSPEEDMODIFIER: %f\n", myspeed, myspeedrunmodifier);
				
				//WriteProcessMemory(phandle, (LPVOID)(0xC4DA9C), &autoloot_on, sizeof(autoloot_on), 0);
				//WriteProcessMemory(phandle, (LPVOID)(0xC4DA9C), &autoloot_off, sizeof(autoloot_off), 0);

				//MODIFY THIS TO ACTIVATE BOT
				//NEED TO REWRITE
				ReadProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot, sizeof(autoloot), 0);
				if(autoloot == 0)
				{
					SendMessage(hWndList5, WM_SETTEXT, 0, (LPARAM)"Stop Bot");
					WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_on, sizeof(autoloot_on), 0);//TURN ON BOT
					//startbot = 0;
					//stopbot = 1;
					
					//PRELOAD CTM MOVE
					WriteProcessMemory(phandle, (LPVOID)(0x00C4D910), &ctmMoveValues1, sizeof(ctmMoveValues1), 0);
					WriteProcessMemory(phandle, (LPVOID)(0x00C4D93C), &ctmMoveValues2, sizeof(ctmMoveValues2), 0);
					WriteProcessMemory(phandle, (LPVOID)(0x00C4D9C0), &ctmMoveValues3, sizeof(ctmMoveValues3), 0);
				}
				else if(autoloot == 1 && stopbot == 1)
				{
					SendMessage(hWndList5, WM_SETTEXT, 0, (LPARAM) _T("Start Bot"));
					WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_off, sizeof(autoloot_off), 0);//TURN OFF BOT
					startbot = 0;
					stopbot = 0;
				}

				//if(startbot == 1){
				//DELTA TIME
				curtime = clock() / (CLOCKS_PER_SEC / 1000);
				deltatime = curtime - uptime;

				//GET VALUE OF TRACKBAR1
				LRESULT pos = SendMessageW(hTrack, TBM_GETPOS, 0, 0);
				wchar_t buf[4];
				wsprintfW(buf, L"%ld", pos);
				//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)buf);

				//GET VALUE OF TRACKBAR1
				LRESULT pos1 = SendMessageW(hTrack1, TBM_GETPOS, 0, 0);
				wchar_t buf1[4];
				wsprintfW(buf1, L"%ld", pos1);
				//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)buf1);
				
				//TRACKBAR VALUES
				int freq;
				wchar_t * pEnd;
				freq = wcstol(buf, &pEnd, 10);
				freq *= 10;

				//int extraTime;
				int freq1;
				wchar_t * pEnd1;
				freq1 = wcstol(buf1, &pEnd1, 10);
				freq1 *= 1000;

				/*
				if(ctmFlag == 7){
					freq = freq + freq1;//extraTime = 10000;
				}
				*/

				if(ctmFlag == 7){
					if(ctmFlag7 == 0)
					{
						ctmFlag7 = 1;
					}
					else if(ctmFlag7 == 1)
					{
						freq = freq + freq1;//extraTime = 10000;
					}
				}

				if(deltatime > freq && isCasting == 0)//5000ms
				{
					long double myCtmDistance=sqrt(pow(ctmPathX[currentpath]-myPosX,2.0)
						+pow(ctmPathY[currentpath]-myPosY,2.0)
						+pow(ctmPathZ[currentpath]-myPosZ,2.0));

					//if(myCtmDistance < 1.0f)
					if(myCtmDistance < 1.0f && ctmFlag != 7)
						//if(myCtmDistance < 1.0f || ctmFlag == 7)
					{
						if(reversePlay == 0)currentpath += 1;
						else if(reversePlay == 1)currentpath -= 1;
						SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"CTM distance");
						updateList();
					}

					if(strcmp(str3[currentpath], "move") == 0)//ctmGuidArr
					{
						//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"AAA MOVING!");
						//updateList();
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D910), &ctmMoveValues1, sizeof(ctmMoveValues1), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D93C), &ctmMoveValues2, sizeof(ctmMoveValues2), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D9C0), &ctmMoveValues3, sizeof(ctmMoveValues3), 0);
						ctmFlag = 4;
					}
					else if(strcmp(str3[currentpath], "interactObj") == 0)
					{
						//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"BBB INTERACT OBJ!");
						//updateList();
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D910), &ctmObjValues1, sizeof(ctmObjValues1), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D93C), &ctmObjValues2, sizeof(ctmObjValues2), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D9C0), &ctmObjValues3, sizeof(ctmObjValues3), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D980), &ctmGuidArr[currentpath], sizeof(ctmGuidArr[currentpath]), 0);
						ctmFlag = 7;
					}
					else if(strcmp(str3[currentpath], "interactNpc") == 0)
					{
						//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"CCC INTERACT NPC!");
						//updateList();
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D910), &ctmNPCValues1, sizeof(ctmNPCValues1), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D93C), &ctmNPCValues2, sizeof(ctmNPCValues2), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D9C0), &ctmNPCValues3, sizeof(ctmNPCValues3), 0);
						WriteProcessMemory(phandle, (LPVOID)(0x00C4D980), &ctmGuidArr[currentpath], sizeof(ctmGuidArr[currentpath]), 0);
						ctmFlag = 5;
					}

					if(currentpath < totalpaths && reversePlay == 0)
					{
						WriteProcessMemory(phandle, (LPVOID)0x00C4D890, &ctmPathX[currentpath], sizeof(ctmPathX[currentpath]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D894, &ctmPathY[currentpath], sizeof(ctmPathY[currentpath]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D898, &ctmPathZ[currentpath], sizeof(ctmPathZ[currentpath]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D888, &ctmFlag, sizeof(ctmFlag), 0);
						uptime = clock() / (CLOCKS_PER_SEC / 1000);
						
						/*
						if(ctmFlag == 7 && stillExists == 0){
						//if(ctmFlag == 7 && stillExists == 0 && interactAgain != 0){
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH UP NEWPATH!");
							updateList();
							//currentpath += 1;
							//interactAgain = 1;
							interactAgain = 1;
						}
						if(ctmFlag == 7 && stillExists == 1){
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH UP!");
							updateList();
							//extraTime = 10000;
							//currentpath += 1;
							//stillExists = 0;
							interactAgain = 0;

							ctmObjValues1 -= 0.25f;
							ctmObjValues3 -= 0.25f;
						}
						*/
						
						if(ctmFlag == 7 && stillExists == 0){
						//if(ctmFlag == 7 && stillExists == 0 && interactAgain == 0){
						//if(ctmFlag == 7 && stillExists == 0 && interactAgain == 1){
						//if(ctmFlag == 7 && stillExists == 0 && interactAgain == 1){
							//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH UP NEWPATH!");
							//updateList();
							//currentpath += 1;
							//interactAgain = 1;
							
							ctmObjValues1 -= 0.25f;
							ctmObjValues3 -= 0.25f;

							if(ctmObjValues1 == 3.0f)
							{
								ctmObjValues1 = 4.5f;
								ctmObjValues3 = 20.25f;
							}
														
							interactAgain = 1;
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH UP interactAgain0");
							updateList();
							
							/*
							else if(interactAgain == 1)
							{
								//FINISHED MOVE TO NEXT PATH
								//currentpath += 1;
								//REFRESH ctmObj values
								//RESET VALUES
								stillExists = 0;
								interactAgain = 0;
								SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH UP NEWPATH2!");
								updateList();
							}
							*/
						}
						else if(ctmFlag == 7 && stillExists == 1){
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH UP!");
							updateList();
							//extraTime = 10000;
							//currentpath += 1;
							stillExists = 0;
							//interactAgain = 0;
							interactAgain = 0;
							
							ctmObjValues1 -= 0.25f;
							ctmObjValues3 -= 0.25f;
						}
						
					}
					else if(currentpath >= 0 && reversePlay == 1)
					{
						WriteProcessMemory(phandle, (LPVOID)0x00C4D890, &ctmPathX[currentpath], sizeof(ctmPathX[currentpath]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D894, &ctmPathY[currentpath], sizeof(ctmPathY[currentpath]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D898, &ctmPathZ[currentpath], sizeof(ctmPathZ[currentpath]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D888, &ctmFlag, sizeof(ctmFlag), 0);
						uptime = clock() / (CLOCKS_PER_SEC / 1000);
						
						/*
						//if(ctmFlag == 7 && stillExists == 0){
						if(ctmFlag == 7 && stillExists == 1){
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH DOWN!");
							updateList();
							//extraTime = 10000;
							//currentpath -= 1;
							//stillExists = 0;
							//interactAgain = 1;
						}
						*/

						if(ctmFlag == 7 && stillExists == 0){
							ctmObjValues1 -= 0.25f;
							ctmObjValues3 -= 0.25f;
							if(ctmObjValues1 == 3.0f)
							{
								ctmObjValues1 = 4.5f;
								ctmObjValues3 = 20.25f;
							}
							interactAgain = 1;
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH DOWN interactAgain0");
							updateList();
						}
						else if(ctmFlag == 7 && stillExists == 1){
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"PATH DOWN!");
							updateList();
							stillExists = 0;
							interactAgain = 0;
							ctmObjValues1 -= 0.25f;
							ctmObjValues3 -= 0.25f;
						}
					}
					else
					{
						//CHECK IF LOOP ENABLED
						if(enableLoop == 1 && reversePlay == 0){
							currentpath = 0;
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"CTM Looping!");
							updateList();
						}
						else if(enableLoop == 1 && reversePlay == 1){
							currentpath = totalpaths - 1;
							SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"CTM Looping Backwards!");
							updateList();
						}
					}
				}
			}

			if(currentguid == targetguid)
			{
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &targetx, sizeof(targetx), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &targety, sizeof(targety), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &targetz, sizeof(targetz), 0);
				//printf("MY LOCATION: X: %f, Y: %f, Z: %f\n", myx, myy, myz);

				ReadProcessMemory(phandle, (void*)(firstobj + 0x1DC8), &targethp, sizeof(targethp), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x1DCC), &targetmana, sizeof(targetmana), 0);
				//if(GetAsyncKeyState(VK_INSERT))
				//{
				//targetz -= 2;
				//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x9C0), &targetz, sizeof(targetz), 0);
				//}
			}

			ReadProcessMemory(phandle, (void*)(firstobj + 0x3C), &nextobj, sizeof(nextobj), 0);
			if(nextobj == firstobj)
			{
				//printf("BREAK!\n");
				break;
			}
			else
			{
				firstobj = nextobj;
			}
		}
	}
		
	//TEST PATH UPDATE HERE
	if(interactAgain == 1 && stillExists == 0){
		if(reversePlay == 0)currentpath += 1;
		else if(reversePlay == 1)currentpath -= 1;
		//stillExists = 0;
		interactAgain = 0;
		SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)"NEXT PATH!");
		updateList();
	}
	
	//else if(interactAgain == 1)stillExists = 0;
	//else if(interactAgain == -1)stillExists = 0;


	//ANTIAFK TICK UPDATE
	firstTick = clock() / (CLOCKS_PER_SEC / 1000);
	ReadProcessMemory(phandle, (void*)(0x00CF0BC8), &initialTick, sizeof(initialTick), 0);
	if(currTick != initialTick)
	{
		currTick = initialTick;
		nextTick = clock() / (CLOCKS_PER_SEC / 1000);
	}
	else if(currTick == initialTick)
	{
		newTick = initialTick;
		diffTick = firstTick - nextTick;//diffTick = nextTick - firstTick;
		diffTick += initialTick;//newTick += 1;
		WriteProcessMemory(phandle, (void*)(0x00CF0BC8), &diffTick, sizeof(diffTick), 0);
	}
}

void convertintchar(char*ch, int i)
{
	sprintf(ch, "%d", i);
}

void convertfloatchar(char*ch, float fl)
{
	sprintf(ch, "%f", fl);
}


/*
int main()
{
//REMEMBER TO SET UAC EXECUTION LEVEL TO ADMIN
//printf("Loading process access grabbing handle!\n");
//LoadPrivilege();


SHELLEXECUTEINFO ShExecInfo = {0};
ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
ShExecInfo.hwnd = NULL;
ShExecInfo.lpVerb = NULL;
ShExecInfo.lpFile = "F:\\Program Files (x86)\\World of Warcraft 1.12\\WoW.exe";
ShExecInfo.lpParameters = "";   
ShExecInfo.lpDirectory = NULL;
ShExecInfo.nShow = SW_SHOW;
ShExecInfo.hInstApp = NULL; 
ShellExecuteEx(&ShExecInfo);
//WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
WaitForInputIdle( ShExecInfo.hProcess, INFINITE );
//CloseHandle(ShExecInfo.hProcess);


//hwnd = FindWindow(NULL,"World of Warcraft");
//GetWindowThreadProcessId(hwnd, &pid);
//phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

//DWORD processID = GetProcessId(ShExecInfo.hProcess);
//DWORD actualProcId = GetWindowThreadProcessId(hwnd, &processID);
//cout << "Process ID is: " << processID << endl; // If true, we cout the process id

if(actualProcId)
{ //We test the DWORD we declared.
cout << "Process ID is: " << processID << endl; // If true, we cout the process id
} else {
cout << "Unable to find the process id !" << endl;
}

//objmanager();
//_getch();

//return 0;
}
*/


