#include "Common.h"

extern HWND hwnd;

char filename[MAX_PATH];
void FilePathDirectory(char* file)
{
	//char filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn,      sizeof(ofn));
	ofn.lStructSize  = sizeof(ofn);
	ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter  = _T("Any File\0*.*\0DLL Files\0*.dll\0SVG XML Files\0*.svg\0EXE Files\0*.exe\0Text Files\0*.txt\0");
	ofn.lpstrFile    = filename;
	ofn.nMaxFile     = MAX_PATH;
	ofn.lpstrTitle   = _T("Select a File!");
	ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn))
	{
		//std::cout << "You chose the file \"" << filename[counter] << "\"\n";
		//MessageBox(NULL, filename[counter], "Note", MB_OK);
		
		strcpy(file, filename);
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
	return;
}

scanValues scans;
flowScript ourScript;

char aaa[1000][255];
char pch3[255];
//extern char pch3;
char hello123[255];

//float ctmPathX[100], ctmPathY[100], ctmPathZ[100];
void cReadTextFile(char*filepathdestination)
{
	//APPEND PLAYER NAME
	char yourCharNameBuffer[255] = {0};
	strcpy(yourCharNameBuffer, filepathdestination);
	char strC[255] = {0};
	strcpy(strC, yourCharNameBuffer);//MUST STRCPY TO AVOID WIERD SYMBOLS
	
	//strcat(strC, ".txt");
	//SendMessage(activitylog, LB_ADDSTRING, NULL, (LPARAM)strC);
	char str[255], str3[1000][255], str4[1000][255], str5[1000][255];//str2[1000][255];
	int i = 0, j = 0, k = 0;//value1[1000], value2[1000], value3[1000];

	FILE *fp = fopen(strC, "r");
	if(fp == NULL)
	{
		//printf("Could not open file %s\n",filename);
		//return 1;
	}
	//MessageBox(hwnd, strC, "TEST", MB_OK);
	while (fgets(str, 255, fp))
	{
		//i++;
		//printf("%3d: %s\n", i, str);
		//printf("%d: %s\n", i, str);
		
		//if you want to split value and string
		//sscanf(str,"%s %d",&str2[j],&value[j]);
		//sscanf(str,"%s %d %d %d", &str2[j], &value[j], &value1[j], &value2[j]);
		
		//sscanf(str, "%s %f %f %f", &str2[j], &value1f[j], &value2f[j], &value3f[j]);
		//sscanf(str, "%s %f", &str2[j], &value1f); //&value2f, &value3f);
		
		//sscanf(str,"%s %f %f %f",&str2[j], &ctmPathX[j], &ctmPathY[j], &ctmPathZ[j]);
		//sscanf(str, "%s %s", &str2[j], &str3[j]);

		sscanf(str, "%s", &str3[j]);
		if(strcmp(str3[j], "start") == 0){
			//loopscript = 1;
			ourScript.loopingFirst = j;
		}
		else if(strcmp(str3[j], "end") == 0){
			//loopscript = 0;
			ourScript.loopingEnd = j;
		}
		else if(strcmp(str3[j], "melee") == 0){
			sscanf(str, "%s %d", &str3[j], &scans.melee);
		}
		else if(strcmp(str3[j], "attackrange") == 0){
			sscanf(str, "%s %d", &str3[j], &scans.attackrange);
		}
		else if(strcmp(str3[j], "attackname") == 0){
			sscanf(str, "%s %[^_]_%s", &str3[j], str4, str5);

			//char atkName[1000][255];
			strcpy(scans.atkName[k], *str4);
			strcat(scans.atkName[k], " ");
			strcat(scans.atkName[k], *str5);
			//printf("NEWSTR: %s\n", scans.atkName[k]);
			k++;
			ourScript.totaltargets = k;
		}
		//else if(strcmp(str3[j], "wait") == 0){}
		else if(strcmp(str3[j], "playerHP") == 0){
			sscanf(str, "%s %c %d", &str3[j], &scans.singleChar[i], &scans.myhptxt[i]);
			scans.statsType[i] = 1;
			scans.lineIndex[i] = j;
			i++;
		}
		else if(strcmp(str3[j], "playerMana") == 0){
			sscanf(str, "%s %c %d", &str3[j], &scans.singleChar[i], &scans.mymanatxt[i]);
			scans.statsType[i] = 2;
			scans.lineIndex[i] = j;
			i++;
		}

		else if(strcmp(str3[j], "playerRage") == 0){
			sscanf(str, "%s %c %d", &str3[j], &scans.singleChar[i], &scans.myragetxt[i]);
			scans.statsType[i] = 3;
			scans.lineIndex[i] = j;
			i++;
		}

		else if(strcmp(str3[j], "playerEnergy") == 0){
			sscanf(str, "%s %c %d", &str3[j], &scans.singleChar[i], &scans.myenergytxt[i]);
			scans.statsType[i] = 4;
			scans.lineIndex[i] = j;
			i++;
		}

		else if(strcmp(str3[j], "targetHP") == 0){
			sscanf(str, "%s %c %d", &str3[j], &scans.singleChar[i], &scans.targethptxt[i]);
			scans.statsType[i] = 5;
			scans.lineIndex[i] = j;
			i++;
		}
		else if(strcmp(str3[j], "targetMana") == 0){
			sscanf(str, "%s %c %d", &str3[j], &scans.singleChar[i], &scans.targetmanatxt[i]);
			scans.statsType[i] = 6;
			scans.lineIndex[i] = j;
			i++;
		}
		else if(strcmp(str3[j], "DoString") == 0)
		{
			char*bbb = str + 9;
			//strcpy(bbb, str + 9);//bbb = str3[j] + 9;
			strcpy(aaa[j], bbb);
			//MessageBox(hwnd, bbb, "TESTbbb", MB_OK);

			j++;
			ourScript.totalpaths = j;
		}
		
		//printf("%d %s\n",value[j],str2[j]);
		//printf("%s %d %d %d\n",str2[j], value[j], value1[j], value2[j]);
		//printf("%s %f %f %f\n",str2[j], value1, value2, value3);

		//strcpy(hello123, aaa[j]);
		//_getch();

		//j++;
		//totalpaths = j;
	}

	strcpy(pch3, str);
	//strcpy(pch3, str2[0]);

	//strcpy(hello123, str3[0]);
	//strcpy(hello123, str);
	//strcpy(hello123, aaa);
	//strcpy(hello123, bbb);
		
	//MessageBox(hwnd, "NO CRASH", "TEST", MB_OK);
	fclose(fp);
}

/*
//distance(x1, y1, z1, x2, y2, z2);
void distanceR(float x1, float y1, float z1, float x2, float y2, float z2, float distanceResult)
{
	//float d = sqrt(pow(x2 - x1, 2) +
	distanceResult = sqrt(pow(x2 - x1, 2) +
					pow(y2 - y1, 2) +
					pow(z2 - z1, 2) * 1.0);
	//std::cout << std::fixed;
	//std::cout << std::setprecision(2);
	//cout << " Distance is " << d;

	return;
}
*/

float distanceR(float targetX, float myX, float targetY, float myY, float targetZ, float myZ)
{
	float deltaX = myX - targetX;
	float deltaY = myY - targetY;
	float deltaZ = myZ - targetZ;
	float dResult = (float)sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));
	return dResult;
}
