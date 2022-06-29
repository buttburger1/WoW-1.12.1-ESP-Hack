//D3D9 MENU
//https://www.mpgh.net/forum/387-project-blackout-hack-coding-source-code/677589-make-simple-d3d-menu-part-2-a.html

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
//https://www.geeksforgeeks.org/program-to-calculate-distance-between-two-points-in-3-d/
//https://math.stackexchange.com/questions/3372513/calculate-the-coordinates-of-points-on-a-circle-in-3d-space
//https://stackoverflow.com/questions/16448702/how-to-move-the-position-of-a-calculated-circle
//https://stackoverflow.com/questions/9455271/integer-division-always-zero

//OFFSETS & LUA REF
//https://github.com/Zz9uk3/ZzukBot_V3/blob/86acf787fbeee9da1c71fd303c1a6183b3b734c7/ZzukBot_WPF/Constants/Offsets.cs
//https://github.com/Zz9uk3/CorthezzWoWBot/blob/master/BotTemplate/Objects/GameObject.cs
//https://github.com/CreativeMind1001/zebra/blob/master/PrivateServerUnlocker/Unlocker.cs
//https://ownedcore1.rssing.com/chan-52602013/all_p2179.html
//https://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/199853-calling-lua-functions.html?__cf_chl_jschl_tk__=pmd_ETsYitkibatWOiFVfaNL8frKlrO9f3j6FNSnI8k4tYM-1631027226-0-gqNtZGzNAmWjcnBszQg9

//STRINGS REF
//https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c
//https://stackoverflow.com/questions/24119766/parsing-using-sscanf-not-working
//https://stackoverflow.com/questions/7969201/sscanf-format-c
//TIME REF
//https://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c?noredirect=1&lq=1
//STRUCT REF
//https://stackoverflow.com/questions/3266580/extern-struct-in-c


/*WOWAPI EXAMPLES
https://vanilla-wow-archive.fandom.com/wiki/World_of_Warcraft_API
https://wowwiki-archive.fandom.com/wiki/API_ScrollingMessageFrame_AddMessage
DEFAULT_CHAT_FRAME:AddMessage("Testing", 1.0, 0.0, 0.0);
DEFAULT_CHAT_GLOBAL:AddMessage("AddOn Loaded!", 0.0, 1.0, 0.0, nil, true);

CastSpellByName("Flash Heal(Rank 2)"); -- Cast Flash Heal (Rank 2) on target.
CastSpellByName("Flash Heal"); -- Cast Flash Heal (Highest rank) on target.
CastSpellByName("Flash Heal",1); -- Cast Flash Heal (Highest rank) on self.

//unsigned char hello[] = "SendChatMessage(\"Hello World\");";
//unsigned char hello[] = "CastSpellByName(\"Flash Heal(Rank 2)\");";
//unsigned char hello[] = "CastSpellByName(\"Heal(Rank 1)\");";
//unsigned char hello[] = "Jump();";
//unsigned char hello[] = "DEFAULT_CHAT_FRAME:AddMessage(\"Testing123\");";

//unsigned char hello[] = "DEFAULT_CHAT_FRAME:AddMessage(\"Testing123\");CastSpellByName(\"Heal(Rank 1)\");";
//unsigned char hello[] = "DEFAULT_CHAT_FRAME:AddMessage(\"Testing123\", '1.0', '0.0', '0.0');CastSpellByName(\"Heal(Rank 1)\");";
//unsigned char hello[] = "RegisterCVar("testABC","123"); DEFAULT_CHAT_FRAME:AddMessage("TestingABC", 1.0, 0.0, 0.0);

//unsigned char hello[] = "DefaultServerLogin('myaccountnamehere', 'password123')";
//unsigned char hello[] = "EnterWorld()";
*/


#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib, "User32.lib")

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
#include <Tlhelp32.h>
#include <conio.h>
#include <tchar.h>
#include <psapi.h>
#include <commctrl.h>


#include <fstream>
#include <string>
#include <iostream>
using namespace std;


void FilePathDirectory(char* file);
void cReadTextFile(char*filepathdestination);

//void distanceR(float x1, float y1, float z1, float x2, float y2, float z2, float distanceResult);
float distanceR(float targetX, float myX, float targetY, float myY, float targetZ, float myZ);


struct flowScript{
	bool loopscript;
	bool npcScanStopper;
	int loopingFirst;
	int loopingEnd;
	int totalpaths;
	int totaltargets;
};//}ourScript;

struct scanValues{
	char singleChar[1000];
	char atkName[1000][255];

	int myhp, mymana, myrage, myenergy, myhpmax, mymanamax, mycurrenthp, mycurrentmana, mycurrentrage,

		targethp, targetmana, targethpmax, targetmanamax, targetcurrenthp, targetcurrentmana,
		targetHPArray[1000], targetManaArray[1000],

		myhptxt[1000], mymanatxt[1000], myragetxt[1000], myenergytxt[1000], targethptxt[1000], targetmanatxt[1000],
		melee, attackrange, statsType[1000], lineIndex[1000];

	float myPosX, myPosY, myPosZ, myPrevX, myPrevY, myPrevZ,
	myx, myy, myz, myfacing, myAngle,
	myspeed, myspeedrunmodifier,
	targetx, targety, targetz, targetfacing, targetspeed, targetspeedrunmodifier,
	scanX, scanY, scanZ,
	prevPos, changedPos, deltaPos;

	float camPosX, camPosY, camPosZ,
	cam01, cam02, cam03,
	cam11, cam12, cam13,
	cam31, cam32, cam33,
	camFOV, camZnearPlane, camZfarPlane, camAspectRatio;
};
