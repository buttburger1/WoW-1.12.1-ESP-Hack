//WORLDTOSCREEN REF
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/287222-direct3d-world-screen.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/805882-classic-1-13-2-32089-spellbook-cooldowns-worldtoscreen.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/599004-world-screen.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-bots-questions-requests/734496-world-2-screen-bfa.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/535748-world-screen.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/328263-wow-1-12-1-5875-info-dump-thread-40.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/805418-classic-1-13-2-32089-worldtoscreen.html
//https://www.drunkenhyena.com/cgi-bin/view_cpp_article.pl?chapter=2;article=27
//https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function

//MATH REF
//https://github.com/BigMo/ExternalUtilsCSharp/blob/master/ExternalUtilsCSharp/MathUtils.cs

//OFFSETS & LUA REF
//https://github.com/Zz9uk3/ZzukBot_V3/blob/86acf787fbeee9da1c71fd303c1a6183b3b734c7/ZzukBot_WPF/Constants/Offsets.cs
//https://github.com/Zz9uk3/CorthezzWoWBot/blob/master/BotTemplate/Objects/GameObject.cs
//https://github.com/CreativeMind1001/zebra/blob/master/PrivateServerUnlocker/Unlocker.cs
//https://ownedcore1.rssing.com/chan-52602013/all_p2179.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/199853-calling-lua-functions.html?__cf_chl_jschl_tk__=pmd_ETsYitkibatWOiFVfaNL8frKlrO9f3j6FNSnI8k4tYM-1631027226-0-gqNtZGzNAmWjcnBszQg9

//STRINGS REF
//https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c
//TIME REF
//https://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c?noredirect=1&lq=1


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma warning(disable:4996 4244)
#pragma warning(disable:4700)
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <fstream>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
bool hooked = false;
//--------------------------------define HOOK & UNHOOK--------------------------------------------------------------------------------------------------
#define HOOK(func,addy) o##func = (t##func)CreateDetour((DWORD)hk##func,(DWORD)addy,Detour_Type_0xB8,7)
#define UNHOOK(func,addy) o##func = (t##func)CreateDetour((DWORD)o##func,(DWORD)addy,Detour_Type_0xB8,7)
#define ES 0
#define DIP 1
#define DrawIndex 0x002B
#define EndS 0x0023
#define PI 3.141592653589793
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
unsigned int isingame, currentobjtype, autoloot1, autoloot2 = 1,
	myhp, mymana,
	targethp, targetmana;
unsigned long long baseaddr, firstobj, nextobj, localguid, targetguid, currentguid, test;
float myx, myy, myz, myfacing, myspeed, myspeedrunmodifier,
	targetx, targety, targetz, targetfacing, targetspeed, targetspeedrunmodifier;

float newvalue = 14;

float camPosX, camPosY, camPosZ,
	cam01, cam02, cam03,
	cam11, cam12, cam13,
	cam31, cam32, cam33,
	camFOV, camZnearPlane, camZfarPlane, camAspectRatio;

char charname[1000][13];
float scanX, scanY, scanZ;

float booltest;
float booltest1;

//BUGTEST
int numscans;
int RUNONCE;
float scanXarray[1000], scanYarray[1000], scanZarray[1000];

clock_t uptime;
clock_t curtime;
float deltatime;


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
	D3DXMatrixPerspectiveFovRH( &Proj, camFOV*0.5, fAspect, camZnearPlane, camZfarPlane );

	D3DXVECTOR3 vEyePt( camPosX, camPosY, camPosZ );
	D3DXVECTOR3 vLookatPt( myx, myy, myz );
	//vLookatPt( Localplayer.X(), Localplayer.Y(), Localplayer.Z() );
	D3DXVECTOR3 vUpVec( 0.0f, 0.0f, 1.0f );
	D3DXMatrixLookAtRH( &View, &vEyePt, &vLookatPt, &vUpVec );

	npDevice->GetViewport(&Viewport);
	D3DXMatrixIdentity(&World);

	D3DXVec3Project( &Out, &In, &Viewport, &Proj, &View, &World );

	//pt->x = Out.x;
	//pt->y = Out.y;
	vecResult.x = Out.x;
	vecResult.y = Out.y;
	//vecResult.z = Out.z;

	return ( Out.z < 1.0f );
	//return ( Out.z < 1.f );



	//D3DXMATRIX proj_mat;
	//D3DXMATRIX view_mat;
	//D3DXMATRIX model_mat;
	//D3DXMATRIX MVP;
	//MVP = model_mat * view_mat * proj_mat;

	//D3DXMATRIX temp;
	//D3DXMatrixTranspose(&temp, &view_mat); //&viewMatrix);

	/*4x4 NOTFORUSE
	float _x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
	float _y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];
	float _w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];
	//if( _w < 0.01f )

	float _inv_w = 1.0f / _w;
	_x *= _inv_w;
	_y *= _inv_w;

	float wtsX = screenwidth * 0.5f;
	float wtsY = screenheight * 0.5f;
	wtsX += 0.5f * _x * screenwidth + 0.5f;
	wtsY += 0.5f * _x * screenheight + 0.5f;
	//return {wtsX, wtsY, _w;}
	*/
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
	//CAMERA
	ReadProcessMemory(phandle, (void*)0x00B4B2BC, &CameraBaseAddr, sizeof(CameraBaseAddr), 0);
	ReadProcessMemory(phandle, (void*)(CameraBaseAddr + 0x65b8), &CameraPointer, sizeof(CameraPointer), 0);
	//eyePos
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x8), &camPosX, sizeof(camPosX), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0xC), &camPosY, sizeof(camPosY), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x10), &camPosZ, sizeof(camPosZ), 0);
	//CamViewMatrix[0][3]
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x14), &cam01, sizeof(cam01), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x18), &cam02, sizeof(cam02), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x1C), &cam03, sizeof(cam03), 0);
	//CamViewMatrix[1][3]
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x20), &cam11, sizeof(cam11), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x24), &cam12, sizeof(cam12), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x28), &cam13, sizeof(cam13), 0);
	//CamViewMatrix[3][3]
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x2C), &cam31, sizeof(cam31), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x30), &cam32, sizeof(cam32), 0);
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x34), &cam33, sizeof(cam33), 0);
	//CamFOV
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x38), &camZnearPlane, sizeof(camZnearPlane), 0);
	//CamZNearPlane
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x3C), &camZfarPlane, sizeof(camZfarPlane), 0);
	//CamZFarPlane
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x40), &camFOV, sizeof(camFOV), 0);
	//CamAspectRatio
	ReadProcessMemory(phandle, (void*)(CameraPointer + 0x44), &camAspectRatio, sizeof(camAspectRatio), 0);
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
			//printf("PLAYER: 0x%.8X\n", firstobj);
			if(currentobjtype == 4)
			{
				char targetNameToChar[50] = "";
				int targetname = 0;
				int namebase = 0xC0E230;
				unsigned long long tempguid = 0;
				
				//BUGTEST
				//if(RUNONCE == 0)
				//{
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

				ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &scanX, sizeof(scanX), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &scanY, sizeof(scanY), 0);
				ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &scanZ, sizeof(scanZ), 0);
				scanXarray[numscans] = scanX;
				scanYarray[numscans] = scanY;
				scanZarray[numscans] = scanZ;
				//printf("X: %f Y: %f Z: %f\n", scanX, scanY, scanZ);
				numscans++;
			}

			break;
		case GAMEOBJECT:
			/*
			printf("GAMEOBJECT: 0x%.8X ", firstobj);
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
			break;
		case DYNAMICOBJECT:
			printf("DYNAMICOBJECT: 0x%.8X\n", firstobj);
			break;
		case CORPSE:
			printf("CORPSE: 0x%.8X\n", firstobj);
			break;
		default:
			//printf("Invalid choice!\n");
			break;
			*/
			break;
		}
		if(currentguid == localguid)
		{
			//printf("MY GUID: %llu\n", currentguid);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &myx, sizeof(myx), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &myy, sizeof(myy), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &myz, sizeof(myz), 0);
			//printf("MY LOCATION: X: %f, Y: %f, Z: %f\n", myx, myy, myz);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DC8), &myhp, sizeof(myhp), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DCC), &mymana, sizeof(mymana), 0);

			ReadProcessMemory(phandle, (void*)(firstobj + 0xA2C), &myspeed, sizeof(myspeed), 0);

			//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0xA34), &newvalue, sizeof(newvalue), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0xA34), &myspeedrunmodifier, sizeof(myspeedrunmodifier), 0);

			//WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x1D30), &autoloot2, sizeof(autoloot2), 0);
			//printf("RUNSPEED: %f RUNSPEEDMODIFIER: %f\n", myspeed, myspeedrunmodifier);
		}

		if(currentguid == targetguid)
		{
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9B8), &targetx, sizeof(targetx), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9BC), &targety, sizeof(targety), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x9C0), &targetz, sizeof(targetz), 0);
			//printf("MY LOCATION: X: %f, Y: %f, Z: %f\n", myx, myy, myz);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DC8), &targethp, sizeof(targethp), 0);
			ReadProcessMemory(phandle, (void*)(firstobj + 0x1DCC), &targetmana, sizeof(targetmana), 0);
			/*EXCLUDE FOR THE MOMENT
			if(GetAsyncKeyState(VK_INSERT))
			{
				targetz += 2;
				WriteProcessMemory(phandle, (LPVOID)(firstobj + 0x9C0), &targetz, sizeof(targetz), 0);
			}
			*/
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
	
	//BEGIN DRAWING HERE!!
	currenttime(1,1,0xFFFF0000); // x,y = width and height
	Time(111, 1, 0xFFFF0000);      // x,y = width and height
	DrawString(1, 15, GREEN, "Our first D3D9 endscene hook!");
	
	//TEST CIRCLE!
	/*
	if(circletest == 24)circletest = 3;
	else
	{
		DrawCircle(screenwidth/2, screenheight/2, 50, circletest, WHITE); //This is a test
		circletest++;
	}
	*/

	//REFRESH SCANS MANUALLY
	if(GetAsyncKeyState(VK_INSERT))
	{
		RUNONCE = 0;
	}
	//LOAD OBJMANAGER!
	objmanager();
	//PREVENT SCAN FREEZE
	RUNONCE = 1;


	//pitch = atan(coord.x - cam.x / coord.y - cam.y)
	//yaw   = atan(coord.z - cam.z / coord.y - cam.y)
	
	//RECT rect;
	//int width, height;
	//GetWindowRect, GetClientRect
	//if(GetClientRect(hwnd, &rect))
	//{
		//width = rect.right - rect.left;
		//height = rect.bottom - rect.top;
	//}

	float deltaX = myx - targetx;
	float deltaY = myy - targety;
	float deltaZ = myz - targetz;
	float distance = (float)sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));

	//pitchtest = atan((mycamzpos - targetz) / (mycamypos - targety));
	//yawtest = atan((targetx - mycamxpos) / (targety - mycamypos));
	
	//int xtest, ytest;
	//float fov = 3.1415926/2*0.9;
	//xtest = screenwidth / 2 + (yawtest*(screenwidth/1.508));
	//ytest = screenheight / 2 + (pitchtest*(screenheight/1.508));

	if(isingame == 1)
	{
		DrawString(1, 29, GREEN, "You are logged in!");

		//MY POS
		char myxarray[64], myyarray[64], myzarray[64],
			targetxarray[64], targetyarray[64], targetzarray[64],
			distancearray[64];
			//camxarray[64], camyarray[64], camzarray[64],
			//xhudarray[64], yhudarray[64], pitchhud[64], yawhud[64];

		convertfloatchar(distancearray, distance),
		convertfloatchar(myxarray, myx), convertfloatchar(myyarray, myy), convertfloatchar(myzarray, myz),
		convertfloatchar(targetxarray, targetx), convertfloatchar(targetyarray, targety), convertfloatchar(targetzarray, targetz),
			
		
		//TARGET DISTANCE
		DrawString(1, 43, GREEN, distancearray),
			DrawString(1, 57, GREEN, myxarray), DrawString(1, 73, GREEN, myyarray), DrawString(1, 87, GREEN, myzarray),
			DrawString(120, 57, GREEN, targetxarray), DrawString(120, 73, GREEN, targetyarray), DrawString(120, 87, GREEN, targetzarray);


		//DONOTUSE
		//convertfloatchar(xhudarray, xtest), convertfloatchar(yhudarray, ytest),
		//convertfloatchar(pitchhud, pitchtest), convertfloatchar(yawhud, yawtest);
		//
		//DrawString(1, 43, GREEN, myxarray), DrawString(1, 57, GREEN, myyarray), DrawString(1, 71, GREEN, myzarray);
		//DrawString(90, 43, GREEN, camxarray), DrawString(90, 57, GREEN, camyarray), DrawString(90, 71, GREEN, camzarray);
		//
		//DrawString(90, 85, GREEN, xhudarray), DrawString(90, 99, GREEN, yhudarray);
		//DrawString(180, 85, GREEN, yawhud), DrawString(180, 99, GREEN, pitchhud);
		

		//MY STATS
		char myhparray[64], mymanaarray[64];
		convertintchar(myhparray, myhp), convertintchar(mymanaarray, mymana);
		DrawString(1, 115, GREEN, myhparray), DrawString(60, 115, GREEN, mymanaarray);
		//SCREEN SIZE
		char screenW[64], screenH[64];
		convertintchar(screenW, screenwidth), convertintchar(screenH, screenheight);
		DrawString(270, 1, GREEN, screenW), DrawString(315, 1, GREEN, screenH);
		//CAMPOS
		char camXarray[64], camYarray[64], camZarray[64];
		convertfloatchar(camXarray, camPosX), convertfloatchar(camYarray, camPosY), convertfloatchar(camZarray, camPosZ);
		DrawString(1, 143, GREEN, camXarray), DrawString(90, 143, GREEN, camYarray), DrawString(180, 143, GREEN, camZarray);
		//CAMVIEW1
		char myCam01[64], myCam02[64], myCam03[64];
		convertfloatchar(myCam01, cam01), convertfloatchar(myCam02, cam02), convertfloatchar(myCam03, cam03);
		DrawString(1, 157, GREEN, myCam01), DrawString(90, 157, GREEN, myCam02), DrawString(180, 157, GREEN, myCam03);
		//CAMVIEW2
		char myCam11[64], myCam12[64], myCam13[64];
		convertfloatchar(myCam11, cam11), convertfloatchar(myCam12, cam12), convertfloatchar(myCam13, cam13);
		DrawString(1, 171, GREEN, myCam11), DrawString(90, 171, GREEN, myCam12), DrawString(180, 171, GREEN, myCam13);
		//CAMVIEW3
		char myCam31[64], myCam32[64], myCam33[64];
		convertfloatchar(myCam31, cam31), convertfloatchar(myCam32, cam32), convertfloatchar(myCam33, cam33);
		DrawString(1, 185, GREEN, myCam31), DrawString(90, 185, GREEN, myCam32), DrawString(180, 185, GREEN, myCam33);
		//CAMVIEW4
		char myCamZnearPlane[64], myCamZfarPlane[64], myCamFOV[64], myCamAspectRatio[64];
		convertfloatchar(myCamZnearPlane, camZnearPlane), convertfloatchar(myCamZfarPlane, camZfarPlane), convertfloatchar(myCamFOV, camFOV), convertfloatchar(myCamAspectRatio, camAspectRatio);
		DrawString(1, 199, GREEN, myCamZnearPlane), DrawString(90, 199, GREEN, myCamZfarPlane), DrawString(180, 199, GREEN, myCamFOV), DrawString(270, 199, GREEN, myCamAspectRatio);
		//Bool
		booltest = WorldToScreen(targetx, targety, targetz);
		char booltestchar[64];
		convertfloatchar(booltestchar, booltest);
		DrawString(1, 269, GREEN, booltestchar);
		//Vectors
		char myVecX[64], myVecY[64], myVecZ[64];
		convertfloatchar(myVecX, vecResult.x), convertfloatchar(myVecY, vecResult.y), convertfloatchar(myVecZ, vecResult.z);
		DrawString(1, 227, GREEN, myVecX), DrawString(1, 241, GREEN, myVecY), DrawString(1, 255, GREEN, myVecZ);
		//Player amount
		char myscancounter[64];
		convertintchar(myscancounter, numscans);
		DrawString(1, 283, GREEN, myscancounter);
		//TEST
		char curtime[64];
		convertfloatchar(curtime, uptime);
		DrawString(1, 311, GREEN, curtime);
		
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
	//TEST
	numscans = 0;
	RUNONCE = 0;

	LoadPrivilege();
	if(dwReason == DLL_PROCESS_ATTACH)CreateThread(0, 0,LoopFunction, 0, 0, 0);
	hwnd = FindWindow(NULL,"World of Warcraft");
	GetWindowThreadProcessId(hwnd, &pid);
	phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	return TRUE;
}
