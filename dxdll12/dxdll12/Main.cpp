#include "Common.h"

bool hooked = false;
//--------------------------------define HOOK & UNHOOK--------------------------------------------------------------------------------------------------
#define HOOK(func,addy) o##func = (t##func)CreateDetour((DWORD)hk##func,(DWORD)addy,Detour_Type_0xB8,7)
#define UNHOOK(func,addy) o##func = (t##func)CreateDetour((DWORD)o##func,(DWORD)addy,Detour_Type_0xB8,7)
#define ES 0
#define DIP 1
#define DrawIndex 0x002B
#define EndS 0x0023
#define PI 3.141592653589793
//#define PI 3.14159265358979323846
using namespace std;
ofstream infile;
ofstream myfile;
ID3DXLine*g_pLine;
LPD3DXFONT g_pFont = NULL;
LPD3DXFONT g_pFont2 = NULL;
D3DVIEWPORT9 g_ViewPort;
LPDIRECT3DDEVICE9 npDevice;
D3DXVECTOR3 pHeader;
HMODULE dwD3D9 = GetModuleHandle("d3d9.dll");
DWORD BaseD3D = NULL;
//-----------------------------------Colors-----------------------------------------------------------------------------------------------
#define GREY	D3DCOLOR_ARGB(255, 128, 128, 128)
#define WHITE	D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED		D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN	D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE    D3DCOLOR_ARGB(255, 000, 000, 255)
#define YELLOW	D3DCOLOR_ARGB(255, 255, 255, 000)
//LPDIRECT3DTEXTURE9 White, Red, Green, Yellow;
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
UINT texnum = 0;
//----------------------------------------------------------------------------------------------------------------------------------
RECT rect;
RECT rect2;
RECT rect3;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD pid;
HWND hwnd;
HANDLE phandle;
int screenwidth, screenheight,
	CameraBaseAddr, CameraPointer;

unsigned int isingame, currentobjtype, isCasting,
	autoloot, autoloot_off = 0, autoloot_on = 1;

unsigned long long baseaddr, firstobj, nextobj, localguid, targetguid, currentguid, test;

float newvalue = 14;

float booltest, booltest1;

char myCharName[255], myCharNameStore[255];
char charname[1000][255];

int numscans;
int RUNONCE;
float scanXarray[1000], scanYarray[1000], scanZarray[1000];

clock_t uptime;
clock_t curtime;
float deltatime;

int modeselect = 1;

LPVOID AllocatedMemoryCodeCave;
LPVOID AllocatedMemory;
LPVOID CustomMemory;

DWORD mycodecave;

int tempbreak = 0;
time_t start_t, end_t;
double diff_t;

char selectedFileDirectory[255];
char fDirectory[255];

extern char pch3[255];

extern float distance;
extern float ctmPathX[10000], ctmPathY[10000], ctmPathZ[10000];
int ctmFlag = 4;

unsigned long long aloot;


extern char aaa[1000][255];
extern char hello123[255];

extern struct scanValues scans;
extern struct flowScript ourScript;

int iii = 0, jjj = 0;

float pathuptime;
float pathcurtime;
float pathdeltatime;

int adjustedBreak = 0;

float adjustedPathTime, adjustedDeltaTime, adjustedUptime, adjustedCTM, adjustedCTMdelta,
	adjustedNewPosDelta, adjustedNewPosTime;

int startPath = 0, numTargets = 0, totalTargets = 0, nextTarget = 0, currentTarget = 0;

int tempStop = 0;
unsigned long long firstTemp;


struct npcStruct{
	//string title;
	int totalUnits;
	unsigned long long objAddr[10000];
	unsigned long long npcGuid[10000];
	float npcDistance[10000];
	float npcX[10000], npcY[10000], npcZ[10000];
	float angle[10000];
} npc;


DWORD GetPID(char* procName)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if( hProcessSnap == INVALID_HANDLE_VALUE )	
		return 0;
	
	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	if(!Process32First(hProcessSnap, &pe32))
		return 0;
	
	do
	{
		if(strcmp(pe32.szExeFile, procName) == 0)
		{
			DWORD pid = pe32.th32ProcessID;
			CloseHandle(hProcessSnap);
			return pid;
		}
	} while(Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 0;
}

DWORD GetBaseAddress(DWORD pid)
{
	HANDLE phandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	MODULEENTRY32 module; 
	module.dwSize = sizeof(MODULEENTRY32);
	Module32First(phandle, &module);
	CloseHandle(phandle);
	return reinterpret_cast<unsigned int>(module.modBaseAddr);
}

typedef void (__fastcall * function_t)(int buffer, int key);

unsigned char shellcode[] =
	"\x53\x65\x6E\x64\x43\x68\x61\x74\x4D\x65\x73\x73\x61\x67\x65\x28\x22\x48\x65\x6C\x6C\x6F\x20\x57\x6F\x72\x6C\x64\x22\x29\x0";

unsigned char hello[] = "DEFAULT_CHAT_FRAME:AddMessage(\"Testing123\",'1.0','0.0','0.0');";

void __declspec(naked) __start()
{
	__asm
	{
		//FRAMESCRIPT EXECUTE
		mov edx, 0
		mov ecx, AllocatedMemoryCodeCave

		mov eax, 0x00704CD0
		call eax

		retn
	}
}
void __end() {}

int utf8_strlen(const string& str)
{
	int c,i,ix,q;
	for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
	{
		c = (unsigned char) str[i];
		if      (c>=0   && c<=127) i+=0;
		else if ((c & 0xE0) == 0xC0) i+=1;
		else if ((c & 0xF0) == 0xE0) i+=2;
		else if ((c & 0xF8) == 0xF0) i+=3;
		//else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
		//else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
		else return 0;//invalid utf8
	}
	return q;
}

void InjectModule()
{
	try
	{	
		unsigned int luatestsize;
		string luatest = "SendChatMessage(\"Hello World\");";
		luatestsize = 1000;

		AllocatedMemoryCodeCave = VirtualAllocEx(phandle, nullptr, luatestsize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		AllocatedMemory = VirtualAllocEx(phandle, nullptr, (DWORD)__end - (DWORD)__start, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		
		char * cstr = new char [luatest.length()+1];
		std::strcpy (cstr, luatest.c_str());

		WriteProcessMemory(phandle, AllocatedMemoryCodeCave, hello123, luatestsize, nullptr);//(DWORD)__end - (DWORD)__start
		WriteProcessMemory(phandle, AllocatedMemory, &__start, (DWORD)__end - (DWORD)__start, nullptr);//(DWORD)__end - (DWORD)__start	
		CreateRemoteThread(phandle, nullptr, 0, (LPTHREAD_START_ROUTINE)AllocatedMemory, AllocatedMemoryCodeCave, 0, nullptr);

		CloseHandle(phandle);
		VirtualFreeEx(phandle, (LPVOID) AllocatedMemory, 0, MEM_RELEASE);
		VirtualFreeEx(phandle, (LPVOID) AllocatedMemoryCodeCave, 0, MEM_RELEASE);
	}

	catch(exception Exception)
	{
		puts(Exception.what());
	}

	return;
}


//-----------------------------------------------CreateDetour-----------------------------------------------------------------------------------
#define Detour_Type_0xE9 1
#define Detour_Type_0xB8 2
#define Detour_Type_0x68 3
DWORD CreateDetour(DWORD dwThread,DWORD dwAdress,DWORD dwType,DWORD dwSize)
{
	DWORD dwDetour,dwProtect,i;
	if (dwAdress&&dwThread&&dwSize>= dwSize)
	{
		dwDetour = (DWORD)VirtualAlloc(0,dwSize+dwSize,0x1000,0x40);
		if (dwDetour&&VirtualProtect((VOID*)dwAdress,dwSize,0x40,&dwProtect))
		{
			for (i=0;i<dwSize;i++) 
			{
				*(BYTE*)(dwDetour+i)=*(BYTE*)(dwAdress+i);
			  }
			       switch (dwType)
			     {
			         case Detour_Type_0xE9:
				     {
				        *(BYTE*)(dwDetour+dwSize+0)=0xE9;
				           *(DWORD*)(dwDetour+dwSize+1)=(dwAdress-dwDetour-dwSize);
	    		             *(BYTE*)(dwAdress+0)=0xE9;
				                *(DWORD*)(dwAdress+1)=(dwThread-dwAdress-dwSize);
				                     }
				break;
				   case Detour_Type_0xB8:
				      {
				        *(BYTE*)(dwDetour+dwSize+0)=0xB8;
				          *(DWORD*)(dwDetour+dwSize+1)=(dwAdress+dwSize);
				           *(WORD*)(dwDetour+dwSize+5)=0xE0FF; 
				             *(BYTE*)(dwAdress+0)=0xB8;            
				               *(DWORD*)(dwAdress+1)=(dwThread);
				                 *(WORD*)(dwAdress+5)=0xE0FF; 
				                  }
				break;
				   case Detour_Type_0x68:
				     {
				       *(BYTE*)(dwDetour+dwSize+0)=0x68;
				         *(DWORD*)(dwDetour+dwSize+1)=(dwAdress+dwSize);
				           *(WORD*)(dwDetour+dwSize+5)=0xC3; 
				             *(BYTE*)(dwAdress+0)=0x68;            
				               *(DWORD*)(dwAdress+1)=(dwThread);
				                 *(WORD*)(dwAdress+5)=0xC3; 
				                   }
				break;
			        }
			         VirtualProtect((VOID*)dwAdress,dwSize,dwProtect,&dwProtect);
			          VirtualProtect((VOID*)dwDetour,dwSize+dwSize,0x20,&dwProtect);
	    	           return dwDetour;
		                }
	                     }
	                      Sleep(10);
return (0);
}

//-----------------------------------------HRESULT-----------------------------------------------------------------------------------------
typedef HRESULT(WINAPI*tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;
typedef HRESULT(WINAPI*tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
typedef HRESULT(WINAPI* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;

void PrintText(char pString[], int x, int y, D3DCOLOR col, ID3DXFont*font)
{
	RECT FontRect = { x, y, x+500, y+30 };
	font->DrawText(NULL, pString, -1, &FontRect, DT_LEFT|DT_WORDBREAK, col);
}

void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

void DrawString(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 30, y + 20 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);
	
	g_pFont2->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void Time(int x,int y,D3DCOLOR color)
{
   static float TimeElapsed = 0;
   static char FinalString[MAX_PATH];
   static time_t TimeValue;
   static tm* timeinfo;

   RECT FontPos = { x, y, x + 200, y + 16 };

   time ( &TimeValue );
   timeinfo = localtime ( &TimeValue );
   if(timeinfo->tm_hour>12)
   sprintf(FinalString, " [Time : %02d:%02d:%02d PM] ",timeinfo->tm_hour - 12,timeinfo->tm_min,timeinfo->tm_sec);
   else
   sprintf(FinalString, " [Time : %02d:%02d:%02d AM] ",timeinfo->tm_hour, timeinfo->tm_min,timeinfo->tm_sec);
   g_pFont->DrawTextA(NULL, FinalString, -1, &FontPos, DT_NOCLIP, color); 
}

void currenttime(int x,int y,D3DCOLOR color)
{
	static char cdate[20] = "" ;
	struct tm * current_tm;

	RECT FontPos = { x, y, x + 200, y + 16 };

	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	sprintf( cdate, " [Date : %02d-%02d-%02d] ",current_tm->tm_mon+1,current_tm->tm_mday,current_tm->tm_year-100+2000);
	g_pFont->DrawTextA(NULL, cdate, -1, &FontPos, DT_NOCLIP, color); 
}

void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	float a;
	for(a = 0; a < PI*2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a+Step) + X;
		float Y2 = radius * sin(a+Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count+1].x = X2;
		Line[Count+1].y = Y2;
		Count += 2;
	}
	g_pLine->Begin();
	g_pLine->Draw(Line,Count,Color);
	g_pLine->End();
	char resultA[64];
	sprintf(resultA, "%f", a);
	DrawString(screenwidth/2, screenheight/2, GREEN, resultA);
}

 void DrawLine(float Xa, float Ya, float Xb, float Yb, float dwWidth, D3DCOLOR Color)
 {
	 //if (!g_pLine)
		//D3DXCreateLine(npDevice, &g_pLine);
	 
	 D3DXVECTOR2 vLine[2]; // Two points
	 //g_pLine->SetAntialias(0); // To smooth edges

	 g_pLine->SetWidth(dwWidth); // Width of the line
	 g_pLine->Begin();
	 
	 vLine[0][0] = Xa; // Set points into array
	 vLine[0][1] = Ya;
	 vLine[1][0] = Xb;
	 vLine[1][1] = Yb;
	 
	 g_pLine->Draw(vLine, 2, Color); // Draw with Line, number of lines, and color
	 g_pLine->End(); // finish
 }

struct vec4
{
	float values[4];
	vec4()
	{
		values[0] = values[1] = values[2] = values[3] = 0;
	}
	vec4( float x, float y, float z, float w )
	{
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = w;
	}
	// Provide array-like index operators for the components of the vector.
	const float& operator[] ( int index ) const
	{
		return values[index];
	}
	float& operator[] ( int index )
	{
		return values[index];
	}
};

struct mat3
{
    D3DXVECTOR3 columns[3];
	mat3()
	{
		columns[0] = D3DXVECTOR3( 1, 0, 0 );
		columns[1] = D3DXVECTOR3( 0, 1, 0 );
		columns[2] = D3DXVECTOR3( 0, 0, 1 );
		//columns[3] = vec4( 0, 0, 0, 1 );
	}
	mat3( D3DXVECTOR3 x, D3DXVECTOR3 y, D3DXVECTOR3 z )
	{
		columns[0] = x;
		columns[1] = y;
		columns[2] = z;
		//columns[3] = w;
	}
	// Provide array-like index operators for the columns of the matrix.
	const D3DXVECTOR3& operator[]( int index ) const
	{
		return columns[index];
	}
    D3DXVECTOR3& operator[]( int index )
    {
        return columns[index];
    }
};

struct mat4
{
    vec4 columns[4];
	mat4()
	{
		columns[0] = vec4( 1, 0, 0, 0 );
		columns[1] = vec4( 0, 1, 0, 0 );
		columns[2] = vec4( 0, 0, 1, 0 );
		columns[3] = vec4( 0, 0, 0, 1 );
	}
	mat4( vec4 x, vec4 y, vec4 z, vec4 w )
	{
		columns[0] = x;
		columns[1] = y;
		columns[2] = z;
		columns[3] = w;
	}
	// Provide array-like index operators for the columns of the matrix.
	const vec4& operator[]( int index ) const
	{
		return columns[index];
	}
    vec4& operator[]( int index )
    {
        return columns[index];
    }
};

struct view_matrix_t
{
	float* operator[](int index)
	{
		return matrix[index];
	}
	float matrix[3][3];
};

struct Vector3
{
	float x, y, z;
};

Vector3 vecResult;
//Vector3 WorldToScreen(const Vector3 pos, view_matrix_t matrix)
//bool WorldToScreen(D3DXVECTOR3 origin, D3DXVECTOR2 * out)
//bool WorldToScreen( float x, float y, float z, POINT *pt )
bool WorldToScreen( float x, float y, float z)
{
	//SCameraInfo cam = read<SCameraInfo>(read<int>(read<int>(WOW_CAMERA_PTR1)+WOW_CAMERA_OFFSET));
	D3DXVECTOR3 Out, In( x, y, z );
	D3DVIEWPORT9 Viewport;
	D3DXMATRIX Proj, View, World;

	//float fAspect = ((float)1280) / 720;
	float fAspect = ((float)screenwidth) / screenheight;
	//D3DXMatrixPerspectiveFovRH(&Proj, camFOV*0.6, fAspect, 0.1f, 177.0f);
	D3DXMatrixPerspectiveFovRH( &Proj, scans.camFOV*0.5, fAspect, scans.camZnearPlane, scans.camZfarPlane );

	D3DXVECTOR3 vEyePt( scans.camPosX, scans.camPosY, scans.camPosZ );
	D3DXVECTOR3 vLookatPt( scans.myx, scans.myy, scans.myz );
	//vLookatPt( Localplayer.X(), Localplayer.Y(), Localplayer.Z() );
	D3DXVECTOR3 vUpVec( 0.0f, 0.0f, 1.0f );
	D3DXMatrixLookAtRH( &View, &vEyePt, &vLookatPt, &vUpVec );

	npDevice->GetViewport(&Viewport);
	D3DXMatrixIdentity(&World);

	D3DXVec3Project( &Out, &In, &Viewport, &Proj, &View, &World );

	vecResult.x = Out.x;
	vecResult.y = Out.y;
	//vecResult.z = Out.z;

	return ( Out.z < 1.0f );
	//return ( Out.z < 1.f );
}


/*
PBYTE HookVTableFunction( PDWORD* dwVTable, PBYTE dwHook, INT Index )
{
    DWORD dwOld = 0;
    VirtualProtect((void*)((*dwVTable) + (Index) ), 0, PAGE_EXECUTE_READWRITE, &dwOld);
    PBYTE pOrig = ((PBYTE)(*dwVTable)[Index]);
    (*dwVTable)[Index] = (DWORD)dwHook;
    VirtualProtect((void*)((*dwVTable) + (Index)), 0, dwOld, &dwOld);
    return pOrig;
}
*/

PBYTE ProtectHook( PDWORD* dwVTable, PBYTE dwHook, INT Index )
{
    DWORD d = 0;
     DWORD ds = 0;
      VirtualProtect((PVOID*)((*dwVTable) + (Index*4)), 4, PAGE_EXECUTE_READWRITE, &d);
       Sleep(-0);
        PBYTE pOrig = ((PBYTE)(*dwVTable)[Index]);
         (*dwVTable)[Index] = (DWORD)dwHook;
           memcpy(pOrig, dwVTable, ds);
          Sleep(-0);
         VirtualProtect((PVOID*)((*dwVTable) + (Index*4)), 4, d, &ds);
        Sleep(-0);
       VirtualProtect((void*)(dwVTable), 4, PAGE_EXECUTE_READWRITE, &d);
      memcpy(pOrig,(void*)(pOrig), 4);
    VirtualProtect((void*)(dwHook), 4, d, &ds);
return pOrig;
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
	ReadProcessMemory(phandle, (void*)0x00C27D88, &myCharName, sizeof(myCharName), 0);//00C27D88
	ReadProcessMemory(phandle, (void*)0x00C7B544, &scans.myPosX, sizeof(scans.myPosX), 0);//0x00C7B544
	ReadProcessMemory(phandle, (void*)0x00C7B548, &scans.myPosY, sizeof(scans.myPosY), 0);//0x00C7B548
	ReadProcessMemory(phandle, (void*)0x00C7B54C, &scans.myPosZ, sizeof(scans.myPosZ), 0);//0x00C7B54C
	ReadProcessMemory(phandle, (void*)0x00CE9B90, &scans.myfacing, sizeof(scans.myfacing), 0);//0x00CE9B90
	//CAMERA
	ReadProcessMemory(phandle, (void*)0x00B4B2BC, &CameraBaseAddr, sizeof(CameraBaseAddr), 0);
	ReadProcessMemory(phandle, (void*)(CameraBaseAddr + 0x65b8), &CameraPointer, sizeof(CameraPointer), 0);
	//eyePos
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x8), &scans.camPosX, sizeof(scans.camPosX), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0xC), &scans.camPosY, sizeof(scans.camPosY), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x10), &scans.camPosZ, sizeof(scans.camPosZ), 0);
	//CamViewMatrix[0][3]
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x14), &scans.cam01, sizeof(scans.cam01), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x18), &scans.cam02, sizeof(scans.cam02), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x1C), &scans.cam03, sizeof(scans.cam03), 0);
	//CamViewMatrix[1][3]
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x20), &scans.cam11, sizeof(scans.cam11), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x24), &scans.cam12, sizeof(scans.cam12), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x28), &scans.cam13, sizeof(scans.cam13), 0);
	//CamViewMatrix[3][3]
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x2C), &scans.cam31, sizeof(scans.cam31), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x30), &scans.cam32, sizeof(scans.cam32), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x34), &scans.cam33, sizeof(scans.cam33), 0);
	//CamFOV
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x38), &scans.camZnearPlane, sizeof(scans.camZnearPlane), 0);
	//CamZNearPlane
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x3C), &scans.camZfarPlane, sizeof(scans.camZfarPlane), 0);
	//CamZFarPlane
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x40), &scans.camFOV, sizeof(scans.camFOV), 0);
	//CamAspectRatio
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x44), &scans.camAspectRatio, sizeof(scans.camAspectRatio), 0);
	//SCREEN POS
	ReadProcessMemory(phandle, (void*)0x00884E28, &screenwidth, sizeof(screenwidth), 0);
	ReadProcessMemory(phandle, (void*)0x00884E2C, &screenheight, sizeof(screenheight), 0);
	//OBJ MANAGER
	ReadProcessMemory(phandle, (void*)0xB4B424, &isingame, sizeof(isingame), 0);
	ReadProcessMemory(phandle, (void*)(0xB41414), &baseaddr, sizeof(baseaddr), 0);
	ReadProcessMemory(phandle, (void*)(baseaddr + 0xAC), &firstobj, sizeof(firstobj), 0);
	ReadProcessMemory(phandle, (void*)(baseaddr + 0xC0), &localguid, sizeof(localguid), 0);
	//printf("LOCALGUID: %llu\n", localguid);
	ReadProcessMemory(phandle, (void*)(0xB4E2D8), &targetguid, sizeof(targetguid), 0);
	//if(targetguid == localguid)printf("TARGETGUID: %llu\n", targetguid);
	ReadProcessMemory(phandle, (void*)0xCECA88, &isCasting, sizeof(isCasting), 0);//0xCECA88 isCasting
	nextobj = firstobj;
	while(firstobj != 0 && (firstobj & 1) == 0)
	{
		ReadProcessMemory(phandle, (void*)(firstobj + 0x14), &currentobjtype, sizeof(currentobjtype), 0);
		//printf("currentobjtypenumber: %u\n", currentobjtype);
		ReadProcessMemory(phandle, (void*)(firstobj + 0x30), &currentguid, sizeof(currentguid), 0);
		switch(currentobjtype)//cin >> i;
		{
		case ITEM:
			//printf("ITEM\n");
			break;
		case CONTAINER:
			//printf("CONTAINER\n");
		case UNIT:
			char myunitname[255];//= "";
			unsigned int unitname1, unitname2;
			ReadProcessMemory(phandle, (void*)(firstobj + 0xB30), &unitname1, sizeof(unitname1), 0);
			//printf("AAA: %u, ", mytest1);
			ReadProcessMemory(phandle, (void*)(unitname1 + 0x0), &unitname2, sizeof(unitname2), 0);
			//printf("BBB: %u, ", mytest2);
			ReadProcessMemory(phandle, (void*)(unitname2), &myunitname, sizeof(myunitname), 0);
			//printf("CCC: %s\n", myunitname);
			strcpy(charname[numscans], myunitname);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &scans.scanX, sizeof(scans.scanX), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &scans.scanY, sizeof(scans.scanY), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &scans.scanZ, sizeof(scans.scanZ), 0);
			//CHECK IF WITHIN RANGE OF PLAYER
			float distanceTemp;
			distanceTemp = distanceR(scans.scanX, scans.myx, scans.scanY, scans.myy, scans.scanZ, scans.myz);
			//ATTACK RANGE HERE
			if(distanceTemp <= scans.attackrange && tempbreak != 0 && ourScript.npcScanStopper == 0)
			{
				//numTargets = 0;//TEST
				for(int a = 0; a <= ourScript.totaltargets; a++)//HOW MANY NAMES YOU LISTED
				{
					if(strcmp(scans.atkName[a], myunitname) == 0)
					{
						//COPY THE FIRST TARGET
						if(numTargets == 0)
						{
							firstTemp = firstobj;
							tempStop = 1;
						}

						if(numTargets != 0 && firstTemp == firstobj && tempStop >= 2)
						{
							ourScript.npcScanStopper = 1;
							tempStop = 0;
							//break;
						}

						ReadProcessMemory(phandle, (void*)(firstobj + 0xEC0), &scans.targethp, sizeof(scans.targethp), 0);//0x1DC8
						ReadProcessMemory(phandle, (void*)(firstobj + 0xEC4), &scans.targetmana, sizeof(scans.targetmana), 0);//0x1DCC
						ReadProcessMemory(phandle, (void*)(firstobj + 0xED8), &scans.targethpmax, sizeof(scans.targethpmax), 0);//0x1DE0
						ReadProcessMemory(phandle, (void*)(firstobj + 0xEDC), &scans.targetmanamax, sizeof(scans.targetmanamax), 0);//0x1DE4

						if(scans.targethp != 0)
						{
							//COPY OVER NPC VALUES TO STRUCT
							npc.objAddr[numTargets] = firstobj;
							npc.npcGuid[numTargets] = currentguid;
							npc.npcDistance[numTargets] = distanceTemp;
							npc.npcX[numTargets] = scans.scanX, npc.npcY[numTargets] = scans.scanY, npc.npcZ[numTargets] = scans.scanZ;
							numTargets++;
							totalTargets = numTargets;
						}
						
						if(tempStop == 1)tempStop += 1;
					}
				}
				//if(numTargets != 0 && firstTemp == localguid) ourScript.npcScanStopper = 1;
				//currentTarget = nextTarget;
				//ourScript.npcScanStopper = 1;
			}

			//UPDATE NPC POS
			if(ourScript.npcScanStopper == 1)
			{
				for(int b = 0; b <= totalTargets; b++)
				{
					if(npc.objAddr[numTargets] == firstobj)
					{
						npc.npcX[b] = scans.scanX, npc.npcY[b] = scans.scanY, npc.npcZ[b] = scans.scanZ;
					}
				}
			}
			
			if(modeselect == 1)
			{
				//char myunitname[255] = "";
				//unsigned int unitname1, unitname2;
				strcpy(myunitname, "");
				//printf("UNIT: 0x%.8X ", firstobj);
				
				scanXarray[numscans] = scans.scanX;
				scanYarray[numscans] = scans.scanY;
				scanZarray[numscans] = scans.scanZ;
				//printf("X: %f Y: %f Z: %f\n", scanX, scanY, scanZ);
				numscans++;
			}

			break;

		case PLAYER:
			//printf("PLAYER: 0x%.8X\n", firstobj);
			if(modeselect == 2)
			{
				char targetNameToChar[255] = "";
				int targetname = 0;
				int namebase = 0xC0E230;
				unsigned long long tempguid = 0;
				//if(RUNONCE == 0)//BUGTEST
				uptime = clock() / (CLOCKS_PER_SEC / 1000);
				while(true)
				{
					ReadProcessMemory(phandle, (void*)(namebase), &targetname, sizeof(targetname), 0);
					ReadProcessMemory(phandle, (void*)(targetname + 0xC), &tempguid, sizeof(tempguid), 0);//targetname + 0xC;
					if(tempguid == 0)
					{
						//printf("EMPTY!\n");
					}
					if(tempguid != currentguid)
					{
						ReadProcessMemory(phandle, (void*)(targetname), &namebase, sizeof(namebase), 0);
						targetname = namebase;
						//printf("Loop: %d!\n", namebase);
						//DELTA TIME
						curtime = clock() / (CLOCKS_PER_SEC / 1000);
						deltatime = curtime - uptime;

						//PREVENT STUCK IN LOOP
						if(GetAsyncKeyState(VK_DELETE) || (deltatime > 0.066667))
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			//}
				ReadProcessMemory(phandle, (void*)(targetname + 0x14), &targetNameToChar, sizeof(targetNameToChar), 0);
				//printf("PLAYERNAME: %s\n", targetNameToChar);
				//char charname[100][13];
				//strcpy(charname[0], targetNameToChar);
				strcpy(charname[numscans], targetNameToChar);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &scans.scanX, sizeof(scans.scanX), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &scans.scanY, sizeof(scans.scanY), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &scans.scanZ, sizeof(scans.scanZ), 0);
				scanXarray[numscans] = scans.scanX;
				scanYarray[numscans] = scans.scanY;
				scanZarray[numscans] = scans.scanZ;
				//printf("X: %f Y: %f Z: %f\n", scanX, scanY, scanZ);
				numscans++;
			}

			break;

		case GAMEOBJECT:
			//printf("GAMEOBJECT: 0x%.8X ", firstobj);
			if (baseaddr == 0 || currentguid == 0)
			{
				//printf("NOTHING!\n");
			}
			else
			{
				char myGameObjName[255] = "";
				unsigned int gameObjName1, gameObjName2;
				//return BmWrapper.memory.ReadASCIIString((BmWrapper.memory.ReadUInt((BmWrapper.memory.ReadUInt(baseAdd + 0x214) + 0x8))), 40);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x214), &gameObjName1, sizeof(gameObjName1), 0);
				//printf("AAA: %u, ", mystuff1);
				ReadProcessMemory(phandle, (void*)(gameObjName1 + 0x8), &gameObjName2, sizeof(gameObjName2), 0);
				//printf("BBB: %u, ", mystuff2);
				ReadProcessMemory(phandle, (void*)(gameObjName2), &myGameObjName, sizeof(myGameObjName), 0);
				//printf("CCC: %s\n", myGameObjName);
				if(modeselect == 3)
				{
					strcpy(charname[numscans], myGameObjName);
					ReadProcessMemory(phandle, (void*)(firstobj + 0x248), &scans.scanX, sizeof(scans.scanX), 0);
					ReadProcessMemory(phandle, (void*)(firstobj + 0x24C), &scans.scanY, sizeof(scans.scanY), 0);
					ReadProcessMemory(phandle, (void*)(firstobj + 0x250), &scans.scanZ, sizeof(scans.scanZ), 0);
					scanXarray[numscans] = scans.scanX;
					scanYarray[numscans] = scans.scanY;
					scanZarray[numscans] = scans.scanZ;
					//printf("X: %f Y: %f Z: %f\n", scanX, scanY, scanZ);
					numscans++;
				}
			}

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

		if(tempbreak != 0)
		{
			WriteProcessMemory(phandle, (void*)(0x00B4E2D8), &npc.npcGuid[nextTarget], sizeof(npc.npcGuid[nextTarget]), 0);
		}

		if(currentguid == targetguid)
		{
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &scans.targetx, sizeof(scans.targetx), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &scans.targety, sizeof(scans.targety), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &scans.targetz, sizeof(scans.targetz), 0);
			//printf("MY LOCATION: X: %f, Y: %f, Z: %f\n", myx, myy, myz);
			ReadProcessMemory(phandle, (void*)(firstobj + 0xEC0), &scans.targethp, sizeof(scans.targethp), 0);//0x1DC8
			ReadProcessMemory(phandle, (void*)(firstobj + 0xEC4), &scans.targetmana, sizeof(scans.targetmana), 0);//0x1DCC
			ReadProcessMemory(phandle, (void*)(firstobj + 0xED8), &scans.targethpmax, sizeof(scans.targethpmax), 0);//0x1DE0
			ReadProcessMemory(phandle, (void*)(firstobj + 0xEDC), &scans.targetmanamax, sizeof(scans.targetmanamax), 0);//0x1DE4
			
			//if(scans.targethp == 0)nextTarget += 1;
			
			double targetHPTemp = (float)scans.targethp / (float)scans.targethpmax * 100.0f;
			scans.targetcurrenthp = (int)targetHPTemp;
			scans.targetHPArray[nextTarget] = scans.targethp;//nextTarget

			double targetManaTemp = (float)scans.targetmana / (float)scans.targetmanamax * 100.0f;
			scans.targetcurrentmana = (int)targetManaTemp;
			
			/*EXCLUDE FOR THE MOMENT
			if(GetAsyncKeyState(VK_INSERT)){
				targetz += 2;
				WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x9C0), &targetz, sizeof(targetz), 0);
			}
			*/
		}
		
		adjustedPathTime = clock() / (CLOCKS_PER_SEC / 1000);
		adjustedDeltaTime = adjustedPathTime - adjustedUptime;
		adjustedCTMdelta = adjustedPathTime - adjustedCTM;
		adjustedNewPosDelta = adjustedPathTime - adjustedNewPosTime;
		//adjustedNewPosDelta = adjustedNewPosTime - adjustedPathTime;
				
		if(currentguid == localguid)
		{
			//printf("MY GUID: %llu\n", currentguid);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &scans.myx, sizeof(scans.myx), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &scans.myy, sizeof(scans.myy), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &scans.myz, sizeof(scans.myz), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9C4), &scans.myAngle, sizeof(scans.myAngle), 0);
			//printf("MY LOCATION: X: %f, Y: %f, Z: %f\n", scans.myx, scans.myy, scans.myz);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DC8), &scans.myhp, sizeof(scans.myhp), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DCC), &scans.mymana, sizeof(scans.mymana), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DE0), &scans.myhpmax, sizeof(scans.myhpmax), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DE4), &scans.mymanamax, sizeof(scans.mymanamax), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DD0), &scans.myrage, sizeof(scans.myrage), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DD8), &scans.myenergy, sizeof(scans.myenergy), 0);
			
			double myHPTemp = (float)scans.myhp / (float)scans.myhpmax * 100.0f;
			scans.mycurrenthp = (int)myHPTemp;
			double myManaTemp = (float)scans.mymana / (float)scans.mymanamax * 100.0f;
			scans.mycurrentmana = (int)myManaTemp;//static_cast<int>(myManaTemp);
			double myRageTemp = (float)scans.myrage / 1000.0f * 100.0f;
			scans.mycurrentrage = (int)myRageTemp;

			ReadProcessMemory(phandle, (void*)(firstobj + 0xA2C), &scans.myspeed, sizeof(scans.myspeed), 0);
			//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0xA34), &newvalue, sizeof(newvalue), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0xA34), &scans.myspeedrunmodifier, sizeof(scans.myspeedrunmodifier), 0);
			//printf("RUNSPEED: %f RUNSPEEDMODIFIER: %f\n", myspeed, myspeedrunmodifier);
			
			aloot = firstobj + 0x1D30;
			//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot2, sizeof(autoloot2), 0);
			ReadProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot, sizeof(autoloot), 0);
			if(autoloot == 0 && tempbreak == 2)//RESET EVERYTHING HERE
			{
				jjj = 0;
				tempbreak = 0;//tempbreak = 1;
			}
			
			else if(autoloot == 1 && tempbreak == 2)
			{
				jjj = 0;
				tempbreak = 0;//tempbreak = 1;
				WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_off, sizeof(autoloot_off), 0);
			}
			
			//STARTS HERE
			else if(autoloot == 1 && tempbreak == 0)
			{
				startPath = 1;

				char path[MAX_PATH] = "";
				HMODULE hm = NULL;

				if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
					GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
					(LPCSTR) 0, &hm) == 0)
				{
					int ret = GetLastError();
					fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
					// Return or however you want to handle an error.
				}
				if (GetModuleFileName(hm, path, sizeof(path)) == 0)
				{
					int ret = GetLastError();
					fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
					// Return or however you want to handle an error.
				}

				//char str[] ="/path/to/file";
				char * pch;
				char * temp;
				pch = strtok(path, "/");//pch = strtok(str, "/");
				while((temp = strtok (NULL, "/")) != NULL)
				{
					pch = temp;
				}
				//printf("The file is: %s", pch);
				//MessageBox(hwnd, pch, "TEST1", MB_OK);

				//char * pch2;
				char pch2[255] = "";
				for(int i = strlen(pch); i >= 0; i--)
				{
					if(pch[i] == '\\')
					{
						strncpy(pch2, pch, i+1);
						//MessageBox(hwnd, pch2, "TEST2", MB_OK);
						break;
					}
				}

				strcat(pch2, "Scripts\\");//strcpy(pch2, "Scripts\\");
				//MessageBox(hwnd, pch2, "TEST3", MB_OK);
				strcat(pch2, myCharName);
				//MessageBox(hwnd, pch2, "TEST4", MB_OK);
				strcat(pch2, ".txt");
				//MessageBox(hwnd, pch2, "TEST5", MB_OK);
				strcpy(fDirectory, pch2);
				//MessageBox(hwnd, fDirectory, "TEST6", MB_OK);

				pathuptime = clock() / (CLOCKS_PER_SEC / 1000);

				//InjectModule();
				tempbreak = 1;
				//time(&start_t);

				cReadTextFile(fDirectory);
				//FilePathDirectory(selectedFileDirectory);
				//MessageBox(hwnd, selectedFileDirectory, "TEST", MB_OK);
				//cReadTextFile(selectedFileDirectory);
			}
			//else if(autoloot == 0 && tempbreak == 1)
			else if(autoloot == 0 && tempbreak == 1 && isCasting == 0 && adjustedDeltaTime >= 250)
			{
				adjustedUptime = clock() / (CLOCKS_PER_SEC / 1000);
				float param1, param2, adjustedPosX, adjustedPosY, atkrange, targetrange;
				
				//if(nextTarget > totalTargets)nextTarget = 0;
				if(numTargets != 0 && scans.targethp != 0)
				{
					//SET TARGET
					WriteProcessMemory(phandle, (void*)(0x00B4E2D8), &npc.npcGuid[nextTarget], sizeof(npc.npcGuid[nextTarget]), 0);
					//CALC ANGLE HERE
					float tempResult, tempOther, r, l, testFinal;//tempX, tempY
					tempResult = atan2(scans.targety - scans.myy, scans.targetx - scans.myx);
					tempOther = tempResult * 180 / PI;
					//printf("tempResult: %f tempOther: %f\n", tempResult, tempOther);
					if(scans.myfacing > tempResult)
					{
						l = ((2 * PI) - scans.myfacing) + tempResult;
						r = scans.myfacing - tempResult;
						//printf("AAA\n");
					}
					else
					{
						l = tempResult - scans.myfacing;
						r = scans.myfacing + ((2 * PI) - tempResult);
						//printf("BBB\n");
					}
					//printf("L: %f R: %f\n", l, r);
					float facingTest;
					if(l < r)
					{
						testFinal = scans.myfacing + l;
						facingTest = l;
					}
					else
					{
						testFinal = scans.myfacing - r;
						facingTest = r;
					}
					//printf("testFinal: %f\n", testFinal);
					//CALC NEW POSITION FOR CTM
					param1 = cos(tempOther * PI / 180.0);
					//printf("param1: %f\n", param1);
					param2 = sin(tempOther * PI / 180.0);
					//printf("param2: %f\n", param2);
					float dTemp;
					dTemp = distanceR(scans.targetx, scans.myx, scans.targety, scans.myy, scans.targetz, scans.myz);
					//FINAL RESULTS(0.1 for quick turn and cast, 0.8 or higher for melee)
					if(scans.melee == 0)
					{
						adjustedPosX = scans.myx + (param1 * dTemp * 0.1);//distanceTemp
						adjustedPosY = scans.myy + (param2 * dTemp * 0.1);//distanceTemp
					}
					else if(scans.melee == 1)
					{
						adjustedPosX = scans.myx + (param1 * dTemp * 0.8);
						adjustedPosY = scans.myy + (param2 * dTemp * 0.8);
					}
					//printf("newX: %f newY: %f\n", adjustedPosX, adjustedPosY);

					//CHECK IF WE REACHED ADJ POS
					//float distanceR(float targetX, float myX, float targetY, float myY, float targetZ, float myZ);
					//atkrange = distanceR(adjustedPosX, scans.myx, adjustedPosY, scans.myy, npc.npcZ[nextTarget], scans.myz);
					//targetrange = distanceR(npc.npcX[nextTarget], scans.myx, npc.npcY[nextTarget], scans.myy, npc.npcZ[nextTarget], scans.myz);
					atkrange = distanceR(adjustedPosX, scans.myx, adjustedPosY, scans.myy, scans.targetz, scans.myz);
					targetrange = distanceR(npc.npcX[nextTarget], scans.myx, npc.npcY[nextTarget], scans.myy, npc.npcZ[nextTarget], scans.myz);

					if(atkrange < 0.05f || facingTest < 0.05f)//l < 0.25f || r < 0.25f)
					{
						WriteProcessMemory(phandle, (void*)(firstobj + 0x9C4), &tempResult, sizeof(tempResult), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D890, &adjustedPosX, sizeof(adjustedPosX), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D894, &adjustedPosY, sizeof(adjustedPosY), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D898, &npc.npcZ[nextTarget], sizeof(npc.npcZ[nextTarget]), 0);
						
						//PostMessage(hwnd, WM_KEYDOWN, VK_UP, 0);
						////PostMessage(hwnd, WM_KEYUP, VK_UP, 0);
						
						//SendMessage(hwnd, WM_KEYDOWN, VK_UP, 0);
						//SendMessage(hwnd, WM_KEYUP, VK_UP, 0);
					}

					else if(adjustedCTMdelta >= 750)
					{
						adjustedCTM = clock() / (CLOCKS_PER_SEC / 1000);
						WriteProcessMemory(phandle, (void*)(firstobj + 0x9C4), &tempResult, sizeof(tempResult), 0);
						////PostMessage(hwnd, WM_KEYDOWN, VK_UP, 0);
						//PostMessage(hwnd, WM_KEYUP, VK_UP, 0);
						
						WriteProcessMemory(phandle, (LPVOID)0x00C4D890, &adjustedPosX, sizeof(adjustedPosX), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D894, &adjustedPosY, sizeof(adjustedPosY), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D898, &npc.npcZ[nextTarget], sizeof(npc.npcZ[nextTarget]), 0);
						WriteProcessMemory(phandle, (LPVOID)0x00C4D888, &ctmFlag, sizeof(ctmFlag), 0);
					}
				}
				if(scans.targetHPArray[nextTarget] == 0)
				{
					nextTarget += 1;
					//ourScript.npcScanStopper = 0;
				}
				if(nextTarget >= totalTargets)
				{
					WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_on, sizeof(autoloot_on), 0);
					tempbreak = 2;
					//RESET VALUES
					//breakloop = 0;
					iii = 0;
					jjj = 0;
					firstTemp = 0;
					nextTarget = 0;
					numTargets = 0;
					totalTargets = 0;
					ourScript.npcScanStopper = 0;
				}
				//if(scans.targethp == 0)nextTarget += 1;
				//else if(scans.targethp == 0)nextTarget += 1;
								
				
				//START LOOPING COMBAT SCRIPT HERE
				int breakloop = 0;
				//LOOPING FROM START TO END
				if(jjj == ourScript.loopingEnd)//&& breakloop == 0)
				{
					iii = 0;
					jjj = ourScript.loopingFirst;
				}
				if(scans.lineIndex[iii] == jjj)
				{
					if(scans.singleChar[iii] = '<')
					{
						switch (scans.statsType[iii])
						{
						case 1:
							if(scans.mycurrenthp <= scans.myhptxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 2:
							if(scans.mycurrentmana <= scans.mymanatxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 3:
							if(scans.mycurrentrage <= scans.myragetxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 4:if(scans.myenergy <= scans.myenergytxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 5:if(scans.targetcurrenthp <= (int)scans.targethptxt){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 6:if(scans.targetcurrentmana <= (int)scans.targetmanatxt){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						}
					}
					else if(scans.singleChar[iii] = '>')
					{
						switch (scans.statsType[iii])
						{
						case 1:
							if(scans.mycurrenthp >= scans.myhptxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 2:
							if(scans.mycurrentmana >= scans.mymanatxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 3:if(scans.mycurrentrage >= scans.myragetxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 4:if(scans.myenergy >= scans.myenergytxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 5:if(scans.targetcurrenthp >= (int)scans.targethptxt){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 6:if(scans.targetcurrentmana >= (int)scans.targetmanatxt){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						}
					}
					else if(scans.singleChar[iii] = '=')
					{
						switch (scans.statsType[iii])
						{
						case 1:
							if(scans.mycurrenthp == scans.myhptxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 2:
							if(scans.mycurrentmana == scans.mymanatxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 3:if(scans.mycurrentrage == scans.myragetxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 4:if(scans.myenergy == scans.myenergytxt[iii]){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 5:if(scans.targetcurrenthp == (int)scans.targethptxt){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						case 6:if(scans.targetcurrentmana == (int)scans.targetmanatxt){iii++;break;}
							else{iii++;jjj++;breakloop = 1;break;}
						}
					}
				}

				strcpy(hello123, aaa[jjj]);//LOAD UP DOSTRING HERE

				pathcurtime = clock() / (CLOCKS_PER_SEC / 1000);
				pathdeltatime = pathcurtime - pathuptime;
				if(jjj >= ourScript.totalpaths)//FINISH ALL DOSTRINGS
				{
					WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_on, sizeof(autoloot_on), 0);
					tempbreak = 2;
					//RESET VALUES
					//breakloop = 0;
					iii = 0;
					jjj = 0;
					firstTemp = 0;
					nextTarget = 0;
					numTargets = 0;
					totalTargets = 0;
					ourScript.npcScanStopper = 0;
				}
				else if(pathdeltatime >= 250)//500ms
				{
					pathuptime = clock() / (CLOCKS_PER_SEC / 1000);
					InjectModule();
					jjj++;
				}
			}
			else if(autoloot == 1 && tempbreak == 1)
			{
				WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_off, sizeof(autoloot_off), 0);
			}
			
			//if(startPath == 1 && totalTargets == 0 && tempbreak == 0 && adjustedBreak == 1 && adjustedNewPosDelta >= 2000)//totalTargets,tempbreak
			if(startPath == 1 && totalTargets == 0 && tempbreak == 0 && adjustedBreak == 1 && adjustedNewPosDelta >= 2000)//totalTargets,tempbreak
			{
				//adjustedNewPosTime = clock() / (CLOCKS_PER_SEC / 1000);
				WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_on, sizeof(autoloot_on), 0);
				adjustedBreak = 0;
			}
			else if(adjustedBreak == 0)
			{
				adjustedNewPosTime = clock() / (CLOCKS_PER_SEC / 1000);
				adjustedBreak = 1;
				//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_on, sizeof(autoloot_on), 0);
			}

			if(startPath == 1 && totalTargets != 0 && tempbreak != 0 && adjustedNewPosDelta >= 2000)//if(startPath == 0)
			{
				if(adjustedBreak == 0)
				{
					WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot_on, sizeof(autoloot_on), 0);
				}
			}
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

void convertLLUchar(char*ch, unsigned long long i)
{
	sprintf(ch, "%llX", i);
}

void convertintchar(char*ch, int i)
{
	sprintf(ch, "%d", i);
}

void convertfloatchar(char*ch, float fl)
{
	sprintf(ch, "%f", fl);
}

int circletest = 3;
float pitchtest, yawtest;

int breaker;

HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	myfile << "EndScene is Hook\n";
	__asm PUSHAD;
	while(!npDevice)npDevice = pDevice;
	//-----------------------------------------Sett your menu here-----------------------------------------------------------------------------------------
	if(g_pFont == NULL) D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont); //Create fonts
	if(g_pFont2 == NULL) D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont2); //Create fonts
	if(g_pLine == NULL) D3DXCreateLine(pDevice, &g_pLine);
	
	pDevice->GetViewport(&g_ViewPort);
	pDevice->GetViewport(&g_ViewPort);
	
	unsigned int pidTitle = pid;
	char bff[255];
	sprintf(bff, "%u", pidTitle);
	SetWindowText(hwnd, bff);

	//BEGIN DRAWING HERE!!
	currenttime(1,1,0xFFFF0000); // x,y = width and height
	Time(111, 1, 0xFFFF0000);      // x,y = width and height
	DrawString(1, 15, GREEN, "Our first D3D9 endscene hook!");

	/*
	//TEST CIRCLE!
	if(circletest == 24)circletest = 3;
	else
	{
		DrawCircle(screenwidth/2, screenheight/2, 50, circletest, WHITE); //This is a test
		circletest++;
	}
	*/

	//VK_PRIOR//PAGEUP//VK_NEXT//PAGEDOWN
	if(GetAsyncKeyState(VK_INSERT))RUNONCE = 0;//REFRESH MANUALLY
	if(GetAsyncKeyState(VK_DELETE))
	{
		modeselect = 0;
		breaker = 1;
	}
	if(GetAsyncKeyState(VK_NUMPAD1))//&& breaker != 1)
	{
		//InjectModule();
		breaker = 0;
	}

	//if(GetAsyncKeyState(VK_NUMPAD3))nextTarget += 1;//DEBUG
	if(GetAsyncKeyState(VK_NUMPAD7))modeselect = 1;
	if(GetAsyncKeyState(VK_NUMPAD8))modeselect = 2;
	if(GetAsyncKeyState(VK_NUMPAD9))modeselect = 3;
		
	objmanager();
	RUNONCE = 1;//PREVENT SCAN FREEZE
	
	float distance;
	distance = distanceR(scans.targetx, scans.myx, scans.targety, scans.myy, scans.targetz, scans.myz);

	if(isingame == 1)
	{
		DrawString(1, 29, GREEN, "You are logged in!");
		if(breaker == 0)
		{
			//SCREEN SIZE
			char screenW[255], screenH[255];
			convertintchar(screenW, screenwidth), convertintchar(screenH, screenheight);
			DrawString(270, 1, GREEN, screenW), DrawString(315, 1, GREEN, screenH);

			//MY POS
			char myxarray[255], myyarray[255], myzarray[255],
				targetxarray[255], targetyarray[255], targetzarray[255],
				distancearray[255];
			//camxarray[64], camyarray[64], camzarray[64],
			//xhudarray[64], yhudarray[64], pitchhud[64], yawhud[64];

			convertfloatchar(distancearray, distance),
				convertfloatchar(myxarray, scans.myx), convertfloatchar(myyarray, scans.myy), convertfloatchar(myzarray, scans.myz),
				convertfloatchar(targetxarray, scans.targetx), convertfloatchar(targetyarray, scans.targety), convertfloatchar(targetzarray, scans.targetz),

				//TARGET DISTANCE
				DrawString(1, 43, GREEN, distancearray),
				DrawString(1, 73, GREEN, myxarray), DrawString(1, 87, GREEN, myyarray), DrawString(1, 101, GREEN, myzarray),
				DrawString(120, 73, GREEN, targetxarray), DrawString(120, 87, GREEN, targetyarray), DrawString(120, 101, GREEN, targetzarray);

			char myhparray[255], mymanaarray[255], myragearray[255], myenergyarray[255];
			convertintchar(myhparray, scans.mycurrenthp), convertintchar(mymanaarray, scans.mycurrentmana),
				convertintchar(myragearray, scans.mycurrentrage), convertintchar(myenergyarray, scans.myenergy);
			DrawString(1, 129, GREEN, myhparray), DrawString(91, 129, GREEN, mymanaarray), DrawString(181, 129, GREEN, myragearray), DrawString(271, 129, GREEN, myenergyarray);

			//CAMPOS
			char camXarray[255], camYarray[255], camZarray[255];
			convertfloatchar(camXarray, scans.camPosX), convertfloatchar(camYarray, scans.camPosY), convertfloatchar(camZarray, scans.camPosZ);
			DrawString(1, 157, GREEN, camXarray), DrawString(90, 157, GREEN, camYarray), DrawString(180, 157, GREEN, camZarray);
			//CAMVIEW1
			char myCam01[255], myCam02[255], myCam03[255];
			convertfloatchar(myCam01, scans.cam01), convertfloatchar(myCam02, scans.cam02), convertfloatchar(myCam03, scans.cam03);
			DrawString(1, 171, GREEN, myCam01), DrawString(90, 171, GREEN, myCam02), DrawString(180, 171, GREEN, myCam03);
			//CAMVIEW2
			char myCam11[255], myCam12[255], myCam13[255];
			convertfloatchar(myCam11, scans.cam11), convertfloatchar(myCam12, scans.cam12), convertfloatchar(myCam13, scans.cam13);
			DrawString(1, 185, GREEN, myCam11), DrawString(90, 185, GREEN, myCam12), DrawString(180, 185, GREEN, myCam13);
			//CAMVIEW3
			char myCam31[255], myCam32[255], myCam33[255];
			convertfloatchar(myCam31, scans.cam31), convertfloatchar(myCam32, scans.cam32), convertfloatchar(myCam33, scans.cam33);
			DrawString(1, 199, GREEN, myCam31), DrawString(90, 199, GREEN, myCam32), DrawString(180, 199, GREEN, myCam33);
			//CAMVIEW4
			char myCamZnearPlane[255], myCamZfarPlane[255], myCamFOV[255], myCamAspectRatio[255];
			convertfloatchar(myCamZnearPlane, scans.camZnearPlane), convertfloatchar(myCamZfarPlane, scans.camZfarPlane),
				convertfloatchar(myCamFOV, scans.camFOV), convertfloatchar(myCamAspectRatio, scans.camAspectRatio);
			DrawString(1, 213, GREEN, myCamZnearPlane), DrawString(90, 213, GREEN, myCamZfarPlane), DrawString(180, 213, GREEN, myCamFOV), DrawString(270, 213, GREEN, myCamAspectRatio);

			//Vectors
			char myVecX[255], myVecY[255], myVecZ[255];
			convertfloatchar(myVecX, vecResult.x), convertfloatchar(myVecY, vecResult.y), convertfloatchar(myVecZ, vecResult.z);
			DrawString(1, 241, GREEN, myVecX), DrawString(1, 255, GREEN, myVecY), DrawString(1, 269, GREEN, myVecZ);

			//Bool
			booltest = WorldToScreen(scans.targetx, scans.targety, scans.targetz);
			char booltestchar[255];
			convertfloatchar(booltestchar, booltest);
			DrawString(1, 283, GREEN, booltestchar);

			//Player amount
			char myscancounter[255];
			convertintchar(myscancounter, numscans);
			DrawString(1, 297, GREEN, myscancounter);
			//TEST
			char curtime[255];
			convertfloatchar(curtime, uptime);
			DrawString(1, 325, GREEN, curtime);

			char fObjChar[255];
			convertLLUchar(fObjChar, aloot);
			DrawString(1, 339, GREEN, pch3);

			DrawString(1, 353, GREEN, hello123);//str3[0]

			//scans.targethp,targetcurrenthp;
			//scans.targetHPArray[nextTarget];
			char targetHPchar[255];
			convertintchar(targetHPchar, scans.targetHPArray[nextTarget]);
			//convertintchar(targetHPchar, scans.targetHPArray[0]);
			DrawString(1, 395, GREEN, targetHPchar);
			

			char nTargetChar[255], tTargetChar[255], fTempChar[255], cGUIDchar[255];
			convertintchar(nTargetChar, nextTarget);
			convertintchar(tTargetChar, totalTargets);
			convertintchar(fTempChar, firstTemp);
			convertLLUchar(cGUIDchar, tempStop);
			DrawString(1, 423, GREEN, nTargetChar);
			DrawString(1, 437, GREEN, tTargetChar);
			DrawString(1, 451, GREEN, fTempChar);
			DrawString(1, 465, GREEN, cGUIDchar);
			
			char tBreakChar[255];
			convertintchar(tBreakChar, tempbreak);
			DrawString(1, 493, GREEN, tBreakChar);
			
			char alootChar[255];
			convertintchar(alootChar, autoloot);
			DrawString(1, 507, GREEN, alootChar);

			//scans.deltaPos,scans.myPrevX
			char dPos[255];
			convertfloatchar(dPos, adjustedNewPosDelta);
			DrawString(1, 521, GREEN, dPos);
		}
		
		//EXCLUDE YOURSELF(DEFAULT 1)
		for(int i = 1; i < numscans; i++)
		{
			booltest1 = WorldToScreen(scanXarray[i], scanYarray[i], scanZarray[i]);
			if ( booltest1 == 0 )
			{
				//DrawLine(screenwidth/2, screenheight, vecResult.x, vecResult.y, 1, RED);
				//DrawString(vecResult.x, vecResult.y, GREEN, charname[i]);
			}
			else if ( booltest1 == 1 )
			{
				DrawLine(screenwidth/2, screenheight, vecResult.x, vecResult.y, 1, GREEN);
				DrawString(vecResult.x, vecResult.y, GREEN, charname[i]);
			}
		}
		numscans = 0;
	}

	if (booltest == 0)
	{
		DrawLine(screenwidth/2, screenheight, screenwidth/2, screenheight, 1, GREEN);
	}
	else if (booltest == 1)
	{
		DrawLine(screenwidth/2, screenheight, vecResult.x, vecResult.y, 1, GREEN);
	}

	__asm POPAD;
	return oEndScene(pDevice);
}

HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	myfile << "DIP is hooked\n";
	if(pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK)Stream_Data->Release();
	return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); // NO FOG 
}

//-----------------------------------------Reset is hooked-----------------------------------------------------------------------------------------
HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS*pPresentationParameters)
{
	myfile << "Reset is hooked\n";
	if(g_pFont)g_pFont->OnLostDevice();
    if(g_pLine)g_pLine->OnLostDevice();
	HRESULT iReturnValue = oReset(pDevice, pPresentationParameters);
	if(iReturnValue == D3D_OK)
	{
		if(g_pFont)g_pFont->OnResetDevice();
		if(g_pLine)g_pLine->OnResetDevice();
	}
	return iReturnValue;
}

LRESULT CALLBACK MsgProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){return DefWindowProc(hwnd, uMsg, wParam, lParam);}

void DX_Init(DWORD*table)
{
    WNDCLASSEX wc = {sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,GetModuleHandle(NULL),NULL,NULL,NULL,NULL,"DX",NULL};
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow("DX",NULL,WS_OVERLAPPEDWINDOW,10,10,300,300,GetDesktopWindow(),NULL,wc.hInstance,NULL);
    LPDIRECT3D9 pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    LPDIRECT3DDEVICE9 pd3dDevice;
    pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&pd3dDevice);
    DWORD* pVTable = (DWORD*)pd3dDevice;
    pVTable = (DWORD*)pVTable[0];
    table[ES]   = pVTable[42];   
    table[DIP]  = pVTable[82];
    DestroyWindow(hWnd);
}

DWORD WINAPI LoopFunction(LPVOID lpParam)
{
	if(hooked == false)
	{
		DWORD VTable[3] = {0};
		while(LoadLibraryA("d3d9.dll") == NULL)
		{
			Sleep(100);
		}
		DX_Init(VTable);
		HOOK(EndScene,VTable[ES]); //Hook EndScene as a device discovery hook
		while(!npDevice)
		{
			Sleep(50);
		}
		UNHOOK(EndScene, VTable[ES]);
		void*d3DIP = (void*)(dwD3D9 + (DWORD) + (DWORD) + (DWORD) + (PDWORD)BaseD3D + 1024); //[82]
		void*d3ES = (void*)(dwD3D9 + (DWORD) + (DWORD) + (DWORD) + (PDWORD)BaseD3D + 1036);  //[42]
		{
			int i;
			for(i = 0; i <= 0; i++)
			{
				DWORD d,ds;
				VirtualProtect((void*)(d3ES), 4, PAGE_EXECUTE_READWRITE, &d);
				memcpy(d3ES,(void*)(d3ES), 4);
				VirtualProtect((void*)(d3ES), 4, d, &ds);
			}
		}
		int C;
		for(C = 0; C <= 0; C++)
		{
			{
				DWORD d,ds;
				VirtualProtect((void*)(d3DIP), 4, PAGE_EXECUTE_READWRITE, &d);
				memcpy(d3DIP,(void*)(d3DIP), 4);
				VirtualProtect((void*)(d3DIP), 4, d, &ds);
			}
		}
		CreateDetour((DWORD)hkDrawIndexedPrimitive, (DWORD)d3DIP*C,Detour_Type_0xB8,7);
		CreateDetour((DWORD)hkEndScene, (DWORD)d3ES*C,Detour_Type_0xB8,7);
		*(PDWORD)&oDrawIndexedPrimitive = VTable[DIP];
		*(PDWORD)&oEndScene = VTable[ES];
		hooked = true;
	}
	Sleep(10);
	void*d3DIP = (void*)(dwD3D9 + (DWORD) + (DWORD) + (DWORD) + (PDWORD)BaseD3D + 1024); //[82]
	void*d3ES = (void*)(dwD3D9 + (DWORD) + (DWORD) + (DWORD) + (PDWORD)BaseD3D + 1036); //[42]
	{
		DWORD Dark, ds;
		VirtualProtect((void*)(d3ES), 4, PAGE_EXECUTE_READWRITE, &Dark);
		memcpy((void*)d3ES, (const void*)d3ES, 4);
		VirtualProtect((void*)(d3ES), 4, Dark, &ds);
	}
	int i;
	for(i = 0; i <= 15; i++)
	{
		{
			DWORD d, ds;
			VirtualProtect((void*)(d3DIP), 4, PAGE_EXECUTE_READWRITE, &d);
			memcpy((void*)d3DIP, (const void*)d3DIP, 4);
			VirtualProtect((void*)(d3DIP), 4, d, &ds);
		}
	}
	for(i = 0; i <= 15; i++)if(memcmp((void*)d3DIP, (void*)d3DIP, 82) == 0)ProtectHook((LPDWORD*)npDevice, (PBYTE)d3DIP, 82); //Protect Hook Draw Indexed Primitive
	for (i = 0; i <= 15; i++)if(memcmp((void*)d3ES, (void*)d3ES, 42) == 0)ProtectHook((LPDWORD*)npDevice, (PBYTE)d3ES, 42); // Protect Hook End Scene
	Sleep(100);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	numscans = 0;
	RUNONCE = 0;

	LoadPrivilege();

	hwnd = FindWindow(NULL,"World of Warcraft");
	GetWindowThreadProcessId(hwnd, &pid);
	phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	
	if(dwReason == DLL_PROCESS_ATTACH)CreateThread(0, 0,LoopFunction, 0, 0, 0);

	return TRUE;
}
